import pandas as pd
import clickhouse_connect
import recordlinkage


def main():
    # Подключение к базе данных ClickHouse
    client = clickhouse_connect.get_client(
        host='localhost',
        user='',
        password='',
        port=8123,
    )

    # SQL-запрос для получения данных
    query = "SELECT * FROM table_dataset1 LIMIT 100"
    data = client.query(query).result_rows

    print(*data, sep='\n')


main()
# # Преобразование данных в DataFrame
# columns = ['column1', 'column2', 'column3']  # Замените на названия ваших столбцов
# df = pd.DataFrame(data, columns=columns)
#
# # Использование Record Linkage Toolkit для объединения похожих строк
# # Инициализация индексера
# indexer = recordlinkage.Index()
# indexer.full()
#
# # Индексация (получение всех возможных пар строк для сравнения)
# pairs = indexer.index(df)
#
# # Создание объекта сравнения
# compare = recordlinkage.Compare()
#
# # Добавление правил для сравнения строк (например, по столбцам)
# compare.string('column1', 'column1', method='jarowinkler', threshold=0.85)  # Сравнение по первому столбцу
# compare.string('column2', 'column2', method='levenshtein', threshold=0.8)  # Сравнение по второму столбцу
# compare.numeric('column3', 'column3', threshold=0.9)  # Числовое сравнение третьего столбца
#
# # Получение результатов сравнения
# features = compare.compute(pairs, df)
#
# # Фильтрация совпадений
# matches = features[features.sum(axis=1) > 2]  # Выбираем строки, где сумма совпадений больше порогового значения
#
# # Вывод индексов совпадающих строк
# print(matches)
