#include "events.h"
#include "globals.h"
#include "time.h"
#include "desk.h"
#include "utils.h"

#include <stdexcept>


Time event(const Time& opTime, const Time& clTime, const Time& prevTime, const std::string& str) {
    Time curTime(str.substr(0, 5));
    if (curTime < prevTime)
        throw std::runtime_error("Wrong format");
    if (str.at(5) != ' ' || str.at(7) != ' ')
        throw std::runtime_error("Wrong format");
    if (curTime > clTime && !_clubClosed) 
        closeClub(clTime);
    _ossRes << str << std::endl;
    switch (str.at(6)) {
    case '1':
        clientEnter(opTime, clTime, curTime, str.substr(8));
        break;
    case '2':
        clientSit(curTime, str.substr(8));
        break;
    case '3':
        clientWaiting(curTime, str.substr(8));
        break;
    case '4':
        clientLeft(curTime, str.substr(8));
        break;
    default:
        throw std::runtime_error("Wrong format");
        break;
    }
    return curTime;
}


void clientEnter(const Time& opTime, const Time& clTime, const Time& curTime, const std::string& clientName) {
    if (!goodName(clientName))
        throw std::runtime_error("Wrong format");
    if (curTime < opTime || curTime > clTime) 
        _ossRes << curTime << " 13 NotOpenYet" << std::endl;
    else if (_clients.count(clientName))
        if (_clients[clientName])
            _ossRes << curTime << " 13 YouShallNotPass" << std::endl;
        else
            _clients[clientName] = -1;
    else
        _clients[clientName] = -1;
}

void clientSit(const Time& curTime, const std::string& str) {
    size_t pos = str.find(' ');
    if (pos == std::string::npos)
        throw std::runtime_error("Wrong format");
    std::string clientName = str.substr(0, pos);
    if (!goodName(clientName))
        throw std::runtime_error("Wrong format");
    int deskId = custom_stoi(str.substr(pos + 1));
    if (deskId > _n || deskId <= 0)
        throw std::runtime_error("Wrong format");
    if (!_clients.count(clientName))
        _ossRes << curTime << " 13 ClientUnknown" << std::endl;
    else if (!_clients[clientName])
        _ossRes << curTime << " 13 ClientUnknown" << std::endl;
    else
        _desks.at(deskId - 1).placeClient(curTime, clientName);
}

void clientWaiting(const Time& curTime, const std::string& clientName) { 
    if (!goodName(clientName))
        throw std::runtime_error("Wrong format");
    if (!_clients.count(clientName))
        _ossRes << curTime << " 13 UndefinedErrorCode/ClientUnknown" << std::endl;
    else if (!_clients[clientName])
        _ossRes << curTime << " 13 UndefinedErrorCode/ClientUnknown" << std::endl;
    else if (_clients[clientName] > 0)
        // Клиент пытается встать в очередь, когда уже сидит за столом
        _ossRes << curTime << " 13 UndefinedErrorCode/IHaveAPlaceAlready" << std::endl;
    else if (_occupiedDesks < _n)
        _ossRes << curTime << " 13 ICanWaitNoLonger" << std::endl;
    else if (_clients[clientName] == -2)
        // Клиент пытается встать в очередь, когда уже находится в ожидании
        _ossRes << curTime << " 13 UndefinedErrorCode/IAmAlreadyInQueue" << std::endl;
    else if (_queue.size() < _n) {
        _queue.push(clientName);
        _clients[clientName] = -2;
    }
    else {
        _ossRes << curTime << " 11 " << clientName << std::endl;
        _clients[clientName] = 0;
    }
}

void clientLeft(const Time& curTime, const std::string& clientName) {
    if (!goodName(clientName))
        throw std::runtime_error("Wrong format");
    if (!_clients.count(clientName))
        _ossRes << curTime << " 13 ClientUnknown" << std::endl;
    else if (!_clients[clientName])
        _ossRes << curTime << " 13 ClientUnknown" << std::endl;
    else if (_clients[clientName] > 0)
        _desks.at(_clients[clientName] - 1).clientLeft(curTime, false);
    else if (_clients[clientName] == -1)
        _clients[clientName] = 0;
    else {
        removeClientFromQueue(_queue, clientName);
        _clients[clientName] = 0;
    }
}

void closeClub(const Time& clTime) {
    _clubClosed = true;
    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        if (it->second > 0)
            _desks.at(it->second - 1).clientLeft(clTime, true);
        else if (it->second < 0) {
            _ossRes << clTime << " 11 " << it->first << std::endl;
            it->second = 0;
        }
    }
}