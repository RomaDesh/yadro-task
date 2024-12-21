#include "../globals.h"
#include "../time.h"
#include "../desk.h"
#include "../utils.h"
#include "../events.h"

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

std::ostringstream _ossRes;
std::map<std::string, int> _clients;
std::vector<Desk> _desks;
std::queue<std::string> _queue;
int _n, _price, _occupiedDesks = 0;
bool _clubClosed = false;

// Основная функция тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
