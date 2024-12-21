#include "globals.h"
#include "desk.h"
#include "time.h"


Desk::Desk(const int& i) : id(i), state(false), clientName(""), currentClientTime(Time(0, 0)), occupiedTime(Time(0, 0)), sum(0) {}


void Desk::placeClient(const Time& curTime, const std::string& client_name) {
    if (state)
        _ossRes << curTime << " 13 PlaceIsBusy" << std::endl;
    else {
        clientName = client_name;
        currentClientTime = curTime;
        state = true;
        _occupiedDesks++;
        if (_clients[client_name] > 0)
            _desks.at(_clients[client_name] - 1).clientLeft(curTime, false);
        _clients[client_name] = id;
    }
}

void Desk::clientLeft(const Time& curTime, const bool& kicked) {
    _clients[clientName] = 0;
    if (kicked)
        _ossRes << curTime << " 11 " << clientName << std::endl;
    Time temp = curTime - currentClientTime;
    occupiedTime += temp;
    sum += countPayment(temp);
    while (!_queue.empty() && !_clients[_queue.front()]) 
        _queue.pop();
    if (_queue.empty()) {
        clientName = "";
        state = false;
        _occupiedDesks--;
    }
    else if (_clients[_queue.front()]) { 
        clientName = _queue.front();
        _queue.pop();
        _ossRes << curTime << " 12 " << clientName << " " << id << std::endl;
        currentClientTime = curTime;
        _clients[clientName] = id;
    }
}

std::ostream& operator<<(std::ostream& os, const Desk& desk) {
    os << desk.id << " " << desk.sum << " " << desk.occupiedTime << std::endl;
    return os;
}
