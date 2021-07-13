/**
 * This file is licensed under the MIT License (MIT).
 * Copyright (c) 2021 RandomKiddo
 **/

#include <iostream>
#include <fstream>
#include <string>

void decompress(std::string input, std::string output);
std::string runLine(std::string line);

int main(void) {
    std::string input;
    std::string output;
    std::cout << "Enter an input dir: ";
    std::cin >> input;
    std::cout << "\nEnter an output dir: ";
    std::cin >> output;
    decompress(input, output);
    return 0;
}

void decompress(std::string input, std::string output) {
    std::ifstream fin;
    fin.open(input.c_str());
    std::ofstream fout;
    fout.open(output.c_str());
    std::string buffer;
    while (std::getline(fin, buffer)) {
        std::string run = runLine(buffer);
        fout << run << "\n";
    }
    fin.close();
    fout.close();
}

std::string runLine(std::string line) {
    std::string str;
    for (int i = 0; i < line.size() - 1; i += 2) {
        char letter = line.at(i);
        int number = line.at(i+1) - '0';
        for (int j = 0; j < number; ++j) {
            str += letter;
        }
    }
    return str;
}