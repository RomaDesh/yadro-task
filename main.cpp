#include "globals.h"
#include "time.h"
#include "desk.h"
#include "utils.h"
#include "events.h"

#include <iostream>
#include <fstream>

std::ostringstream _ossRes;
std::map<std::string, int> _clients;
std::vector<Desk> _desks;
std::queue<std::string> _queue;
int _n, _price, _occupiedDesks = 0;
bool _clubClosed = false;

int main(int argc, char* argv[]) {
	// Проверяем количество переданных аргументов командной строки
	if (argc != 2) {
		std::cout << "Invalid amount of arguments" << std::endl;
		return 0;
	}

	// Проверяем возможность открыть переданный файл
	std::ifstream fin(argv[1]);
	if (fin.is_open() == false) {
		std::cout << "File \"" << argv[1] << "\" can't be opened" << std::endl;
		return 0;
	}

	std::string str; // Строка для считывания из файла

	// Считываем количество столов
	getline(fin, str);
	try {
		_n = custom_stoi(str);
		if (_n <= 0)
			throw std::runtime_error("Wrong format");
	}
	catch (std::exception& ex) {
		std::cout << str << std::endl;
		return 0;
	}

	// Считываем время открытия и закрытия
	getline(fin, str);
	Time *opTime, *clTime;
	try {

		if (str.size() != 11)
			throw std::runtime_error("Wrong format");
		opTime = new Time(str.substr(0, 5));
		clTime = new Time(str.substr(6, 5));
		if (str.at(5) != ' ') 
			throw std::runtime_error("Wrong format");
		if (*opTime >= *clTime)
			throw std::runtime_error("Wrong format");
	}
	catch(std::exception& ex) {
		std::cout << str << std::endl;
		return 0;
	}

	// Считываем стоимость часа
	getline(fin, str);
	try {
		_price = custom_stoi(str);
		if (_price <= 0)
			throw std::runtime_error("Wrong format");
	}
	catch (std::exception& ex) {
		std::cout << str << std::endl;
		return 0;
	}

	// Инициализируем вектор столов
	for (int i = 1; i <= _n; i++)
		_desks.emplace_back(i);

	// Вывод времени открытия
	_ossRes << *opTime << std::endl;

	// Построчно считываем строки событий из файла
	Time prevTime(0, 0);
	while (getline(fin, str)) {
		try {
			prevTime = event(*opTime, *clTime, prevTime, str);
		}
		catch (std::exception& ex)
		{
			std::cout << str << std::endl;
			return 0;
		}
	}

	// Проверяем закрывался ли клуб во время обработки событий, если нет вызываем функцию закрытия
	if (!_clubClosed)
		closeClub(*clTime);

	// Выводим время закрытия
	_ossRes << *clTime << std::endl;

	// Выводим сводку за день по каждому столу
	for (int i = 0; i < _n; i++)
		_ossRes << _desks.at(i);

	// Выводим на экран получившийся поток с корректным выводом
	std::cout << _ossRes.str();
	_ossRes.str("");
	// Закрываем файловый поток
	fin.close();

	return 0;
}
