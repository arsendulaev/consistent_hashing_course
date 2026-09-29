#include <string>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <sstream>
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
            if (names.count(name)) {
                for (int hash : names[name]) {
                    positions.erase({hash, name});
                }
                names.erase(name);
            }
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
            std::string line;
            std::getline(std::cin, line);
            std::istringstream iss(line);
            std::string key;
            std::map<std::string, int> counts;
            while (iss >> key) {
                if (positions.empty()) {
                    continue;
                }
                auto it = positions.lower_bound({hsum(key), ""});
                if (it == positions.end()) {
                    it = positions.begin();
                }
                counts[it->second]++;
            }
            for (const auto&[fst, snd] : counts) {
                std::cout << fst << ": " << snd << "\n";
            }
        }
    }
}