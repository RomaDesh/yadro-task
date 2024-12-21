#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <queue>

// ���������� ��� �������� stoi, ��� �������� ��� � ���������� ������ ��������� ������ ����� ����� ��� ������ ��������
int custom_stoi(const std::string& str);

// ������� �������� ����� ������� �� ������������ ������� ������� ������
bool goodName(const std::string& clientName);

// �������� ������� �� �������� �������
void removeClientFromQueue(std::queue<std::string>& q, const std::string& clientName);

#endif