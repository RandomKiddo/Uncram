/**
 * This file is licensed under the MIT License (MIT).
 * Copyright (c) 2021 RandomKiddo
 **/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

void decompress(std::vector<int> code, std::string output);

int main(void) {
    std::string input;
    std::string output;
    std::cout << "Enter an input dir: ";
    std::cin >> input;
    std::cout << "\nEnter an output dir: ";
    std::cin >> output;
    std::ifstream fin;
    fin.open(input.c_str());
    std::ofstream trunc;
    trunc.open(output.c_str(), std::ios::trunc);
    trunc.close();
    std::string buffer;
    while (std::getline(fin, buffer)) {
        std::string str;
        std::vector<int> code;
        for (int i = 0; i < buffer.size(); ++i) {
            if (buffer.at(i) != ' ') {
                str += buffer.at(i);
            } else {
                code.push_back(stoi(str));
                str = "";
            }
        }
        decompress(code, output);
    }
    fin.close();
    return 0;
}

void decompress(std::vector<int> code, std::string output) {
    std::ofstream fout;
    fout.open(output.c_str(), std::ios::app);
    std::unordered_map<int, std::string> table;
    for (int i = 0; i < 256; ++i) {
        std::string s = "";
        s += char(i);
        table[i] = s;
    }
    int old = code[0], n;
    std::string s = table[old];
    std::string c = "";
    c += s[0];
    fout << s;
    int count = 256;
    for (int i = 0; i < code.size() - 1; ++i) {
        n = code[i+1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        } else {
            s = table[n];
        }
        fout << s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        ++count;
        old = n;
    }
    fout << "\n";
    fout.close();
}