#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "mysql.h"
#include <regex>

/**
	\brief Класс, содержащий данные о пациенте

	Данный класс имеет цель получить строку данных,
	разбить ее на части и присвоить значение каждому столбцу таблицы БД 
 */
class DataExtraction
{
	std::string nm, surnm, birth, age, phonenum;
public:
	DataExtraction(const std::string& s);
	DataExtraction(MYSQL_ROW arr) : nm{ arr[1] }, surnm{ arr[2] }, birth{ arr[3] }, age{ arr[4] }, phonenum{ arr[5] } {};
	DataExtraction();
	std::string get_nm() const { return nm; }
	std::string get_surnm() const { return surnm; }
	std::string get_birth() const { return birth; }
	std::string get_age() const { return age; }
	std::string get_phonenum() const { return phonenum; }
};

std::ostream& operator << (std::ostream& out, const DataExtraction& a);

/**
	\brief Простейший класс исключений

	При возникновении исключения любого типа
	будет брошено исключение этого класса
 */
class DataExtractionException{};