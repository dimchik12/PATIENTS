#include <iostream>
#include "mysql.h"
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "DataExtraction.h"
#include "My_fun_for_MYSQL.h"

HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE); /// Получение информации о курсоре
CONSOLE_CURSOR_INFO CursorInfo;

#define BUTTON_ENTER 13 /// Определение макросов для клавиш
#define BUTTON_ESCAPE 27
#define BUTTON_UP 72
#define BUTTON_DOWN 80

void DrawMenu(int flag1);
void DrawEdit(int pos_s);
void DrawArrow(int pos, int pos_if);

int main()
{
    SetConsoleTitle(L"Connect to Host");

    GetConsoleCursorInfo(hstdout, &CursorInfo); /// Устранение мерцания курсора
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(hstdout, &CursorInfo);

    int flag1 = 0, flag2 = 0; 
    const int flag11 = 1, flag22 = 6; 

    DrawMenu(flag1);
    while (true)
        switch (_getch()) { 
        case BUTTON_ENTER:
            if (flag1 == 0) /// Подключение к БД
            {
                CursorInfo.bVisible = true;
                SetConsoleCursorInfo(hstdout, &CursorInfo);
                system("cls"); /// Очистка консоли
                MYSQL* mysql = mysql_init(NULL); /// Получаем дескриптор БД

                std::string A, B, C; unsigned int D, E;
                std::list<DataExtraction> pull_d;

                std::cout << "Enter the data:\n";
                std::cout << "Host: "; std::cin >> A; std::cout << "\n";
                std::cout << "User: "; std::cin >> B; std::cout << "\n";
                std::cout << "Password: "; std::cin >> C; std::cout << "\n";
                std::cout << "Port: "; std::cin >> D; std::cout << "\n";
                std::cout << "Client flag: "; std::cin >> E;
                A = "localhost", B = "root", C = "1234";
                D = 3306, E = 0;
                mysql = conn(A, B, C, "", D, E);

                system("cls");
                char ver;
                std::cout << "Create new database? Enter Y(y)/N(n): "; std::cin >> ver;
                if (ver == 'Y' || ver == 'y')
                {
                    system("cls");
                    std::string db_creation_name; ///< Имя созданной базы данных
                    db_creation_name = "patients"; //std::cout << "Database create name: "; std::cin >> db_creation_name;
                    newdb(mysql, db_creation_name);
                }

                system("cls");
                std::cout << "Enter the database name:\n";
                std::string db_name; ///< Имя базы данных
                db_name = "patients"; //std::cout << "Database name: "; std::cin >> db_name;
                mysql = conn(A, B, C, db_name, D, E);
                
                system("cls");
                
                std::cout << "Create new table? Enter Y(y)/N(n): "; std::cin >> ver;
                if (ver == 'Y' || ver == 'y')
                {

                    std::cout << "Enter the creation table name:\n";
                    std::string table_creation_name = "patientsdata";
                    std::cout << "Table creation name: "; std::cin >> table_creation_name;
                    add_table_to_db(mysql, table_creation_name);
                }
                
                system("cls");
                std::cout << "Enter the table name:\n";
                std::string table_name = "patientsdata";
                std::cout << "Table name: "; std::cin >> table_name;
                system("cls");

                DrawEdit(flag2);
                bool flag = false;
                flag2 = 0;
                while (true)
                {
                    if (flag == true)
                    {
                        DrawMenu(flag1 = 0);
                        break;
                    }
                    switch (_getch())
                    {
                    case BUTTON_ENTER: // enter
                        CursorInfo.bVisible = true;
                        SetConsoleCursorInfo(hstdout, &CursorInfo);
                        if (flag2 == 0) /// Ввод данных из файла
                        {
                            SetConsoleTitle(L"Add data from \"txt\" file");
                            system("cls");
                            std::string file_name = "patients.txt";
                            std::cout << "Enter the \"txt\" file:\n";
                            std::cout << "File: "; std::cin >> file_name; std::cout << "\n";
                            pull_data(pull_d, file_name);
                            add_data_to_db(mysql, pull_d, table_name);
                            pull_d.clear();
                        }
                        else if (flag2 == 1) /// Ввод данных из консоли
                        {
                            SetConsoleTitle(L"Add data from console");
                            system("cls");
                            std::string obj; ///< Строка для ввода данных
                            while (true)
                            {
                                std::cout << "Enter the information about patient(name, surname, birthdate, age, phonenumber) (press \"e\" to finish):\n";
                                obj = "e"; //std::cout << "Patient: "; std::cin >> obj;
                                if (obj == "e") break;
                                DataExtraction data{ obj };  
                                add_data_to_db(mysql, data, table_name);
                            }
                        }
                        else if (flag2 == 2) /// Вывод данных на экран
                        {
                            SetConsoleTitle(L"Show data from the database");
                            system("cls");
                            pull_d = pull_data_from_db(mysql);
                            show_data_from_cont(pull_d);
                            flag = true;
                        }
                        else if (flag2 == 3) /// Отключение от БД
                        {
                            SetConsoleTitle(L"Disconnect from the Database");
                            system("cls");
                            mysql_close(mysql);
                            std::cout << "Disconnected\n";
                            flag = true;
                            system("pause");
                        }
                        else if (flag2 == 4) /// Удаление таблицы
                        {
                            SetConsoleTitle(L"Delete the table from the Database");
                            system("cls");
                            std::string table_name;
                            std::cout << "Enter the table name:\n";
                            table_name = "patientsdata"; //std::cout << "Table name: "; std::cin >> table_name;
                            delete_table_from_db(mysql, table_name);
                            std::cout << "Table deleted:\n";
                            flag = true;
                            system("pause");
                        }
                        else if (flag2 == 5) /// Удаление БД
                        {
                            SetConsoleTitle(L"Delete the Database");
                            system("cls");
                            dropdb(mysql, db_name);
                            std::cout << "Database deleted:\n";
                            flag = true;
                            system("pause");
                        }
                        else if (flag2 == 6) /// Вернуться в меню
                        {
                            mysql_close(mysql);
                            flag = true;
                        }
                        flag2 = 0;
                        DrawEdit(flag2);
                        break;

                    case BUTTON_UP: // up
                        if (flag2 > 0)
                            DrawEdit(--flag2);
                        break;

                    case BUTTON_DOWN: // down
                        if (flag2 < flag22)
                            DrawEdit(++flag2);
                        break;
                    }
                }
            }
            else if (flag1 == 1) /// Выход
            {
                system("cls");
                return 0;
            }
        case BUTTON_UP: // up
            if (flag1 > 0)
                DrawMenu(--flag1);
            break;

        case BUTTON_DOWN: // down
            if (flag1 < flag11)
                DrawMenu(++flag1);
            break;
        }
}

void DrawMenu(int pos_f)
{
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(hstdout, &CursorInfo);
    SetConsoleTitle(L"Menu");
    system("cls");
    std::cout << " Connect";
    DrawArrow(pos_f, 0);
    std::cout << "\n" << " Diaconnect";
    DrawArrow(pos_f, 1);
}

void DrawEdit(int pos_s)
{
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(hstdout, &CursorInfo);
    SetConsoleTitle(L"Edit");
    system("cls");
    std::cout << " Add data from \"txt\" file";
    DrawArrow(pos_s, 0);
    std::cout << "\n" << " Add from console";
    DrawArrow(pos_s, 1);
    std::cout << "\n" << " Show from db";
    DrawArrow(pos_s, 2);
    std::cout << "\n" << " Disconnect db";
    DrawArrow(pos_s, 3);
    std::cout << "\n" << " Delete the table";
    DrawArrow(pos_s, 4);
    std::cout << "\n" << " Delete the db";
    DrawArrow(pos_s, 5);
    std::cout << "\n" << " Back";
    DrawArrow(pos_s, 6);
}

//выбор в меню
void DrawArrow(int pos, int pos_if)
{
    if (pos == pos_if)
        printf("*");
}