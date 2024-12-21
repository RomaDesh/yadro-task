#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <queue>

// Надстройка над функцией stoi, для проверки что в переданной строке находится только целое число без лишних символов
int custom_stoi(const std::string& str);

// Функция проверки имени клиента на соответствие формату входных данных
bool goodName(const std::string& clientName);

// Удаление клиента из середины очереди
void removeClientFromQueue(std::queue<std::string>& q, const std::string& clientName);

#endif