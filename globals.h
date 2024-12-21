#pragma once

#ifndef GLOBALS_H 
#define GLOBALS_H

#include <sstream>
#include <map>
#include <vector>
#include <queue>

class Desk;

// Поток в котором мы будем хранить строки с корректным выводом.
extern std::ostringstream _ossRes;

// Карта клиентов, где ключом является имя клиента, а значения целые числа, где:
// -2 - клиент находится в очереди;
// -1 - клиент находится в клубе;
// 0 - клиент не находится в клубе;
// 1 ... n - клиент сидит за соответствующим столом.
extern std::map<std::string, int> _clients;

// Вектор со всеми столами в клубе.
extern std::vector<Desk> _desks;

// Очередь клиентов
extern std::queue<std::string> _queue;

// Число столов в клубе.
extern int _n;

// Стоимость часа.
extern int _price;

// Количество занятых столов
extern int _occupiedDesks;

// Хранит в себе: false - если клуб ещё не закрывался, true - если клуб уже закрылся.
// ВАЖНО: _clubClosed не является индикатором открыт клуб или закрыт, он нужен только для того, чтобы отслеживать
// производилась ли процедура закрытия, чтобы не вызывать функцию закрытия более 1 раза
extern bool _clubClosed;


#endif