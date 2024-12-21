#pragma once

#ifndef TIME_H
#define TIME_H

#include <string>
#include <iostream>

class Time {
private:
    int h = 0; // Часы
    int m = 0; // Минуты
public:
    // Конструктор для инициализации времени из строки формата "XX:XX"
    Time(const std::string& timeStr);

    // Конструктор для инициализации времени из часов и минут
    Time(int hours, int minutes);

    // Операторы сравнения
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;

    // Операторы сложения и вычитания
    Time operator+(const Time& other) const;
    Time operator+=(const Time& other);
    Time operator-(const Time& other) const;

    // Подсчет выручки для столов
    friend int countPayment(const Time& time);

    // Вывод времени в поток в формате "XX:XX"
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
};

#endif