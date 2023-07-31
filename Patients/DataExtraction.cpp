#include "DataExtraction.h"

/**
 * Главный конструктор класса DataExtraction
 \param s Строка, содержащая данные
 */
DataExtraction::DataExtraction(const std::string& s)
{
    if (s != "")
    {
        std::istringstream input(s); /// Строковый поток ввода
        input >> nm;
        if (std::regex_search(nm, std::regex("[0-9]")) || nm.size() > 20) throw DataExtractionException();
        input >> surnm;
        if (std::regex_search(surnm, std::regex("[0-9]")) || surnm.size() > 20) throw DataExtractionException();
        input >> birth;
        if (!std::regex_match(birth, std::regex("[[:d:]]{4}[-|:|.][[:d:]]{2}[-|:|.][[:d:]]{2}"))) throw DataExtractionException();
        short y = std::stoi(birth.substr(0, 4));
        short m = std::stoi(birth.substr(6, 2));
        short d = std::stoi(birth.substr(8, 2));
        if (d == 0 || d > 31 || m == 0 || m > 12 || (m < 8 && m % 2 == 0 && d > 30) || (m > 7 && m % 2 == 1 && d > 30)) throw DataExtractionException();
        if (m == 2 && d > 29 || d == 29 && m == 2 && (y % 4 != 0 || y % 100 == 0 && y % 400 != 0)) throw DataExtractionException();
        input >> age;
        if (std::regex_search(age, std::regex("[^[:d:]]")) || stoi(age) > 125) throw DataExtractionException();
        input >> phonenum;
        if (!std::regex_match(phonenum, std::regex("(([+]?[7])|[7|8])[[:d:]]{10}"))) throw DataExtractionException();

        if (birth[4] != '-' || birth[7] != '-') birth[4] = birth[7] = '-';
        if (phonenum[0] == '8') phonenum = "+7" + phonenum.erase(0, 1);
        else if (phonenum[0] == '7') phonenum = '+' + phonenum;
    }
}

std::ostream& operator << (std::ostream& out, const DataExtraction& a)
{
	out << a.get_nm() << ' ' << a.get_surnm() << ' ' << a.get_birth() << ' ' << a.get_age() << ' ' << a.get_phonenum();
	return out;
}