#include <string>
#include <iostream>
#include <numeric>
#include <map>

int hsum(std::string& str) {
    return std::accumulate(str.begin(), str.end(), 0, [](int sum, char c) {
        return sum + c;
    });
}

int main() {
    std::string line;
    std::cin >> line;
    std::map<std::string, int> words;
    if (line == "KEYS") {
        std::cin >> line;
        while (line != "BEFORE") {
            words.insert({line, hsum(line)});
            std::cin >> line;
        }
    }
    int n;
    std::cin >> n;
    for (const auto& word : words) {
        std::cout << word.first << ": " << word.second % n << std::endl;
    }
    std::cin >> line;
    if (line != "AFTER") {
        return 0;
    }
    int newn;
    std::cin >> newn;
    for (const auto& word : words) {
        std::cout << word.first << ": " << word.second % newn << std::endl;
    }
    auto counter = [n, newn, &words]() {
        int cnt = 0;
        for (const auto& word : words) {
            cnt += word.second % n != word.second % newn ? 1 : 0;
        }
        return cnt;
    };
    std::cout << "moved=" << counter() << std::endl;
}