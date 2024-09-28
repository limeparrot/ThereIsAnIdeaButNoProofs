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
    FROM table_dataset1
    LIMIT 5000000
    """

    dataset2 = """
    INSERT INTO table_clean_dataset2
    WITH TRUNCATE
    SELECT
        uid,
        concat(middle_name, ' ', first_name, ' ', last_name) as full_name,
        null as email,
        address,
        null as sex,
        birthdate,
        phone,
    FROM table_dataset2 
    LIMIT 5000000
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
    FROM table_dataset3
    LIMIT 5000000
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


def checker(client: clickhouse_connect.driver.Client):
    query = """
        SELECT 
            sum(tmp)
        FROM (
            SELECT 
                1 as tmp
            FROM
                (
                    SELECT * FROM table_clean_dataset1
                    UNION ALL  
                    SELECT * FROM table_clean_dataset2
                    UNION ALL                
                    SELECT * FROM table_clean_dataset3
                )
            GROUP BY full_name
        )
    """
    data = client.query(query)
    print("after group by", data.result_rows)
    query = """
        SELECT 
            count(*)
        FROM
            (
                SELECT * FROM table_clean_dataset1
                UNION ALL  
                SELECT * FROM table_clean_dataset2
                UNION ALL                
                SELECT * FROM table_clean_dataset3
            )
        """
    data = client.query(query)
    print("before group by", data.result_rows)


def insert_result(client: clickhouse_connect.driver.Client):
    create_table_result = """
        CREATE OR REPLACE TABLE table_results (
            id_is1 Array(UUID),
            id_is2 Array(UUID),
            id_is3 Array(UUID)
        ) ENGINE = MergeTree()
        ORDER BY id_is1;
    """

    client.command(create_table_result)

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
        GROUP BY full_name
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

    # print(pre_result)

    # client.command(result)
    client.query(result)

    # print(*client.query("""
    #     SELECT * FROM table_results LIMIT 100
    # """).result_rows, sep="\n")
    print(*client.query("""
        SELECT count(*) FROM table_results
    """).result_rows, sep='\n')


def main():
    start_time = time()
    client = clickhouse_connect.get_client(
        host='localhost',
        user='',
        password='',
        port=8123,
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
