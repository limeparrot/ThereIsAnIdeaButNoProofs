import clickhouse_connect
from time import time


def create_tables_for_clean_datasets(client):
    query = """
    CREATE OR REPLACE TABLE table_clean_dataset{number} (
        uid UUID,
        full_name String,
        email String,
        address String,
        sex String,
        birthdate String,
        phone String
    ) ENGINE = MergeTree()
    PARTITION BY murmurHash3_32(uid) % 8
    ORDER BY uid;
    """

    client.command(query.format(number=1))
    client.command(query.format(number=2))
    client.command(query.format(number=3))


def fill_data_in_clean_datasets(client):
    dataset1 = """
    INSERT INTO table_clean_dataset1
    WITH TRUNCATE
    SELECT 
        uid,
        full_name,
        email,
        address,
        sex,
        birthdate,
        phone,
    FROM clean_dataset1
    """

    dt2 = """
    SELECT
        uid,
        coalesce(if(first_name == 'Нет' or first_name == 'Отсутствует', Null, first_name), '') as first_name,
        coalesce(if(middle_name == 'Нет' or middle_name == 'Отсутствует', Null, middle_name), '') as middle_name,
        coalesce(if(last_name == 'Нет' or last_name == 'Отсутствует', Null, last_name), '') as last_name,
        null as email,
        address,
        null as sex,
        birthdate,
        phone,
    FROM clean_dataset2
    """

    dataset2 = f"""
    INSERT INTO table_clean_dataset2
    WITH TRUNCATE
    SELECT
        uid,
        trim(concat(middle_name, ' ', first_name, ' ', last_name)) as full_name,
        null as email,
        address,
        null as sex,
        birthdate,
        phone,
    FROM ({dt2})
    """

    dataset3 = """
    INSERT INTO table_clean_dataset3
    WITH TRUNCATE
    SELECT
        uid,
        name as full_name,
        email,
        null as address,
        sex,
        birthdate,
        null as phone
    FROM clean_dataset3
    """

    client.command(
        dataset1
    )

    client.command(
        dataset2
    )

    client.command(
        dataset3
    )


def insert_result(client: clickhouse_connect.driver.Client):
    select_base_data = """
        SELECT 
            uid,
            full_name,
            email,
            address,
            sex,
            birthdate,
            phone,
            1 as table_no,
            tuple(table_no, uid) as to_ids
        FROM table_clean_dataset1
        UNION ALL  
        SELECT 
            uid,
            full_name,
            email,
            address,
            sex,
            birthdate,
            phone,
            2 as table_no,
            tuple(table_no, uid) as to_ids
        FROM table_clean_dataset2
        UNION ALL                
        SELECT
            uid,
            full_name,
            email,
            address,
            sex,
            birthdate,
            phone,
            3 as table_no,
            tuple(table_no, uid) as to_ids
        FROM table_clean_dataset3
    """

    pre_result = f"""
        SELECT 
            groupArray(to_ids) as ids
        FROM (
            {select_base_data}
        )
        GROUP BY full_name, email, phone
    """

    result = f"""
        INSERT INTO table_results
        WITH TRUNCATE
        SELECT
            arrayMap(x -> (x.2), arrayFilter(x -> (x.1 == 1), ids)) as ids1,
            arrayMap(x -> (x.2), arrayFilter(x -> (x.1 == 2), ids)) as ids2,
            arrayMap(x -> (x.2), arrayFilter(x -> (x.1 == 3), ids)) as ids3
        FROM ({pre_result})
    """

    client.command(result)


def main():
    start_time = time()
    client = clickhouse_connect.get_client(
        host='127.0.0.1',
        user='',
        password='',
        port=9000,
    )

    print("Create tables")
    create_tables_for_clean_datasets(client)
    create_table_time = time()
    print("Create table time:", create_table_time - start_time)
    print("Fill data")
    fill_data_in_clean_datasets(client)
    fill_table_time = time()
    print("Fill data time:", fill_table_time - create_table_time)
    print("Count group by")
    insert_result(client)
    end_time = time()
    print("Count group by time:", end_time - fill_table_time)
    print()
    print("All time", end_time - start_time)


main()
