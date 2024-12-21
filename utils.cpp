#include "utils.h"

#include <stdexcept>

int custom_stoi(const std::string& str) {
    std::size_t pos{};
    int res = stoi(str, &pos);
    if (str.size() != pos)
        throw std::runtime_error("Way more characters");
    return res;
}

bool goodName(const std::string& clientName) {
    if (!clientName.size())
        return false;
    for (int i = 0; i < clientName.size(); i++) {
        if ((clientName.at(i) >= 'a' && clientName.at(i) <= 'z')
            || (clientName.at(i) >= '0' && clientName.at(i) <= '9')
            || clientName.at(i) == '-' || clientName.at(i) == '_')
            continue;
        else
            return false;
    }
    return true;
}

void removeClientFromQueue(std::queue<std::string>& q, const std::string& clientName) {
    if (clientName == q.front())
        q.pop();
    else {
        std::queue<std::string> temp;
        while (!q.empty()) {
            if (q.front() != clientName)
                temp.push(q.front());
            q.pop();
        }
        q = temp;
    }
}