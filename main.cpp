#include <string>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

int hsum(const std::string& str) {
    return std::accumulate(str.begin(), str.end(), 0, [](int sum, char c) {
        return (sum + c) % 10000;
    });
}

int main() {
    std::set<std::pair<int, std::string>> positions;
    std::map<std::string, std::vector<int>> names;
    std::string command;
    while (std::cin >> command) {
        if (command == "ADD_NODE") {
            std::string name;
            std::cin >> name;
            std::vector<int> position;
            for (int i = 0; i < 5; i++) {
                int hash = hsum(name + "#" + std::to_string(i));
                positions.insert({hash, name});
                position.push_back(hash);
            }
            names[name] = position;
        } else if (command == "REMOVE_NODE") {
            std::string name;
            std::cin >> name;
            positions.erase({hsum(name), name});
            names.erase(name);
        } else if (command == "LOOKUP") {
            std::string key;
            std::cin >> key;
            if (positions.empty()) {
                std::cout << "NONE\n";
                continue;
            }
            auto it = positions.lower_bound({hsum(key), ""});
            if (it == positions.end()) {
                it = positions.begin();
            }
            std::cout << it->second << "\n";
        } else if (command == "STATS") {
            std::string name;
            while (std::cin >> name) {
                std::cout << name << ":" << names.count(name) << "\n";
            }
        }
    }
}