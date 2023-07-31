Система хранения данных о пациенте с помощью базы данных MYSQL.

Система позволяет записывать в таблицу базы данных, хранить и получать информацию о пациентах, такую как ID пациента, имя, фамилия, дата рождения, возраст и контактные данные. Также есть возможность добавлять данные о пациентах. Помимо этого, реализован пользовательский интерфейс в командной строке.

При запуске приложения пользователь попадает в главное меню и может выбрать следующие команды: connect - Подключение к базе данных exit - Выход из приложения

При авторизации пользователь вводит следующие данные: хост, имя пользователя, пароль, порт и клиентский флаг. Также при необходимости следует ввести имя базы данных и имя таблицы.

Для хранения данных о пациенте используется класс DataExtraction. Этот класс получает текстовую строку, проверяет её корректность и преобразует элементы строки в данные таблицы. Также класс содержит конструктор по умолчанию и методы, возвращающие данные таблицы.

Для работы с базой данных и таблицами были написаны следующие функции:

1.void pull_data(std::list& a, const std::string& input)

Функция считывает данные из файла и добавляет в таблицу

\param a - Список данных о пациентах

\param input - Имя файла

2.void show_data_from_cont(std::list& a)

Функция выводит данные о пациентах в консоль

\param a - Список данных о пациентах

3.void newdb(MYSQL* mysql, const std::string& db)

Функция генерирует новую базу данных

\param mysql - Дескриптор БД

\param db - Имя БД

4.void dropdb(MYSQL* mysql, const std::string& db)

Функция удаляет базу данных

\param mysql - Дескриптор БД

\param db - Имя БД

5.MYSQL* conn(const std::string& host1, const std::string& user1, const std::string& passwd1, const std::string& db1, const unsigned int port1, const unsigned long clientflag1)

Функция осуществляет подключение к базе данных

\param host1 - Хост

\param user1 - Имя пользователя

\param passwd1 - Пароль

\param db1 - Имя БД

\param port1 - Порт

\param clientflag1 - Клиентский флаг

6.void add_table_to_db(MYSQL* mysql, const std::string& table_name)

Функция добавляет новую таблицу в базу данных

\param mysql - Дескриптор БД

\param table_name - Имя таблицы

7.void delete_table_from_db(MYSQL* mysql, const std::string& table_name)

Функция удаляет таблицу из базы данных

\param mysql - Дескриптор БД

\param table_name - Имя таблицы

8.void add_data_to_db(MYSQL* mysql, std::list& pull_d, const std::string& table_name)

Функция добавляет в таблицу данные о 2 или более пациентах

\param mysql - Дескриптор БД

\param pull_d - Добавляемые данные о пациентах

\param table_name - Имя таблицы

9.void add_data_to_db(MYSQL* mysql, DataExtraction pull_d, const std::string& table_name)

Функция добавляет в таблицу данные об 1 пациенте

\param mysql - Дескриптор БД

\param pull_d - Добавляемые данные о пациенте

\param table_name - Имя таблицы

10.std::list& pull_data_from_db(MYSQL* mysql)

\param mysql - Дескриптор БД

\return Контейнер данных о пациентах
