#pragma once

#ifndef GLOBALS_H 
#define GLOBALS_H

#include <sstream>
#include <map>
#include <vector>
#include <queue>

class Desk;

// ����� � ������� �� ����� ������� ������ � ���������� �������.
extern std::ostringstream _ossRes;

// ����� ��������, ��� ������ �������� ��� �������, � �������� ����� �����, ���:
// -2 - ������ ��������� � �������;
// -1 - ������ ��������� � �����;
// 0 - ������ �� ��������� � �����;
// 1 ... n - ������ ����� �� ��������������� ������.
extern std::map<std::string, int> _clients;

// ������ �� ����� ������� � �����.
extern std::vector<Desk> _desks;

// ������� ��������
extern std::queue<std::string> _queue;

// ����� ������ � �����.
extern int _n;

// ��������� ����.
extern int _price;

// ���������� ������� ������
extern int _occupiedDesks;

// ������ � ����: false - ���� ���� ��� �� ����������, true - ���� ���� ��� ��������.
// �����: _clubClosed �� �������� ����������� ������ ���� ��� ������, �� ����� ������ ��� ����, ����� �����������
// ������������� �� ��������� ��������, ����� �� �������� ������� �������� ����� 1 ����
extern bool _clubClosed;


#endif