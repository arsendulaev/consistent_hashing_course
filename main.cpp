#include <string>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>

int hsum(std::string& str) {
    return std::accumulate(str.begin(), str.end(), 0, [](int sum, char c) {
        return (sum + c) % 1000;
    });
}

int main() {
    std::set<int> positions;
    std::map<int, std::string> names;
    std::string command;
    while (std::cin >> command) {
        if (command == "ADD_NODE") {
            std::string name;
            std::cin >> name;
            positions.insert(hsum(name));
            names[hsum(name)] = name;
            std::cout << "OK" << " " << hsum(name) << std::endl;
        } else if (command == "REMOVE_NODE") {
            std::string name;
            std::cin >> name;
            positions.erase(hsum(name));
            names.erase(hsum(name));
            std::cout << "OK" << std::endl;
        } else if (command == "LOOKUP") {
            std::string key;
            std::cin >> key;
            if (positions.empty()) {
                std::cout << "NONE\n";
                continue;
            }
            auto it = positions.lower_bound(hsum(key));
            if (it == positions.end()) {
                it = positions.begin();
            }
            std::cout << names[*it] << "\n";
        } else if (command == "RING") {
            for (auto const& pair : names) {
                std::cout << pair.second << ":" << pair.first << "\n";
            }
        }
    }
}