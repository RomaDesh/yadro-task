#pragma once

#ifndef DESK_H
#define DESK_H

#include <string>
#include <iostream>

#include "time.h"

class Desk {
private:
    const int id; // Номер стола 
    bool state = false; // Состояние стола (true - занят, false - свободен) 
    std::string clientName = ""; // Имя клиента, который занимает данный стол 
    Time currentClientTime; // Время, в которое сел клиент, занимающий данный стол
    Time occupiedTime; // Время, которое стол был занят за рабочий день 
    int sum = 0; // Сумма выручки со стола за день
public:
    // Конструктор для инициализации через id
    Desk(const int& i);

    // Клиент занял стол
    void placeClient(const Time& curTime, const std::string& client_name);

    // Клиент ушел из-за стола
    void clientLeft(const Time& curTime, const bool& kicked);

    // Вывод сводки за день
    friend std::ostream& operator<<(std::ostream& os, const Desk& desk);

#ifdef TESTRUN

    Desk(const int& i, const bool& s, const std::string& name, const Time& curClientTime, const Time& ocTime, const int& sum_) :
        id(i), state(s), clientName(name), currentClientTime(curClientTime), occupiedTime(ocTime), sum(sum_) {};

    bool getState() {
        return state;
    }

    std::string getClientName() {
        return clientName;
    }

    Time getCurrentClientTime() {
        return currentClientTime;
    }

    Time getOccupiedTime() {
        return occupiedTime;
    }

    int getSum() {
        return sum;
    }

#endif
};

#endif