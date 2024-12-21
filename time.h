#pragma once

#ifndef TIME_H
#define TIME_H

#include <string>
#include <iostream>

class Time {
private:
    int h = 0; // ����
    int m = 0; // ������
public:
    // ����������� ��� ������������� ������� �� ������ ������� "XX:XX"
    Time(const std::string& timeStr);

    // ����������� ��� ������������� ������� �� ����� � �����
    Time(int hours, int minutes);

    // ��������� ���������
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;

    // ��������� �������� � ���������
    Time operator+(const Time& other) const;
    Time operator+=(const Time& other);
    Time operator-(const Time& other) const;

    // ������� ������� ��� ������
    friend int countPayment(const Time& time);

    // ����� ������� � ����� � ������� "XX:XX"
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
};

#endif