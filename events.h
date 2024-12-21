#pragma once

#ifndef EVENTS_H
#define EVENTS_H

#include <string>

#include "time.h"

// Общая функция для обработки строк событий, возвращает время вызываемого события
Time event(const Time& opTime, const Time& clTime, const Time& prevTime, const std::string& str);

// Событие ID 1. Клиент пришел
void clientEnter(const Time& opTime, const Time& clTime, const Time& curTime, const std::string& clientName);

// Событие ID 2. Клиент сел за стол
void clientSit(const Time& curTime, const std::string& str);

// Событие ID 3. Клиент ожидает
void clientWaiting(const Time& curTime, const std::string& clientName);

// Событие ID 4. Клиент ушел
void clientLeft(const Time& curTime, const std::string& clientName);

// Функция закрытия клуба, выполняется единожды, если вызывается событие с временем >= времени закрытия,
// либо после обработки всех событий. Выгоняет всех клиентов оставшихся в клубе на момент закрытия.
void closeClub(const Time& clTime);

#endif