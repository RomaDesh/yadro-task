#pragma once

#ifndef EVENTS_H
#define EVENTS_H

#include <string>

#include "time.h"

// ����� ������� ��� ��������� ����� �������, ���������� ����� ����������� �������
Time event(const Time& opTime, const Time& clTime, const Time& prevTime, const std::string& str);

// ������� ID 1. ������ ������
void clientEnter(const Time& opTime, const Time& clTime, const Time& curTime, const std::string& clientName);

// ������� ID 2. ������ ��� �� ����
void clientSit(const Time& curTime, const std::string& str);

// ������� ID 3. ������ �������
void clientWaiting(const Time& curTime, const std::string& clientName);

// ������� ID 4. ������ ����
void clientLeft(const Time& curTime, const std::string& clientName);

// ������� �������� �����, ����������� ��������, ���� ���������� ������� � �������� >= ������� ��������,
// ���� ����� ��������� ���� �������. �������� ���� �������� ���������� � ����� �� ������ ��������.
void closeClub(const Time& clTime);

#endif