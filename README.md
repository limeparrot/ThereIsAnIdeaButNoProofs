![image](https://github.com/user-attachments/assets/9d508785-752a-4949-9cea-522efb8db4a3)<h1 align="center">IT INNO HACK</h1>
<h3 align="center">«Есть идея, но нет пруфов»</h3>
<h2 align="center">Dynamic Record Linkage</h2>

<div align="center">
  
  <a href="">![Ubuntu](https://img.shields.io/badge/Ubuntu-FF5733?style=for-the-badge&logo=ubuntu&logoColor=ffdd54)</a>
  <a href="">![ClickHouse](https://img.shields.io/badge/ClickHouse-FFFAFA?style=for-the-badge&logo=ClickHouse&logoColor=yellow)</a>
  <a href="">![YandexCloud](https://img.shields.io/badge/C++-EAEEFF?style=for-the-badge&logo=cplusplus&logoColor=1945FF)</a>
  <a href="">![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)</a>
  
</div>


##     Диаграмма архитектуры
<h4>Архитектура решения выглядит следующим образом</h3><br>

<img src="https://github.com/user-attachments/assets/27b51906-c4a0-420a-84ca-36e68d2b0592" align="center" height="680" width="912"></img><br>

### Инструкция по сборке решения
Установка 
```bash
docker build -t solution .
```
Клонирование репозитория
```bash
git clone test
```
Запуск docker-compose
```bash
test
```

### Описание работы кода
Подключение к базе данных
 - Создание ClickHouse Client и подключение к БД
   
Параллельная обработка массивов данных
 - Получение одной партии данных
 - Исправление искаженных записей
 - Обработка пропущенных значений
 - Удаление явных дубликатов
 - Валидация и нормализация данных
 - Сбор чистых данных

Сопоставление данных
 - Анализ данных
 - Разрешение конфликтов
 
Визуализация результатов
 - Оценка результатов обработки данных
 - Построение диаграмм
 - Генерация отчёта в формате pdf
   
Оценка качества
 - .





### Потенциал масштабирования
Решение показывает высокую скорость независимо от объёмов данных, такой результат достигается засчёт последовательной подгрузки и обработки данных в оперативной памяти.
Независимо от порядка данных, программа самостоятельно определяет подходящий шаблон, нормализует и передаёт алгоритму 

### Насколько универсально решение
На основе статестического анализа подаваемых данных, программа выстраивает структуру данных, что позволяет обрабатывать данные не зависимо от их содержания 
