#pragma once

#ifndef DESK_H
#define DESK_H

#include <string>
#include <iostream>

#include "time.h"

class Desk {
private:
    const int id; // ����� ����� 
    bool state = false; // ��������� ����� (true - �����, false - ��������) 
    std::string clientName = ""; // ��� �������, ������� �������� ������ ���� 
    Time currentClientTime; // �����, � ������� ��� ������, ���������� ������ ����
    Time occupiedTime; // �����, ������� ���� ��� ����� �� ������� ���� 
    int sum = 0; // ����� ������� �� ����� �� ����
public:
    // ����������� ��� ������������� ����� id
    Desk(const int& i);

    // ������ ����� ����
    void placeClient(const Time& curTime, const std::string& client_name);

    // ������ ���� ��-�� �����
    void clientLeft(const Time& curTime, const bool& kicked);

    // ����� ������ �� ����
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