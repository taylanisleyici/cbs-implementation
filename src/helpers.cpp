#include "helpers.h"

#include <fstream>
#include <iostream>
#include <vector>

std::shared_ptr<std::vector<std::vector<char>>> readmap(const std::string &filename)
{
    std::shared_ptr<std::vector<std::vector<char>>> grid = std::make_shared<std::vector<std::vector<char>>>();
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file " << filename << std::endl;
        exit(1);
    }

    std::string line;

    while (std::getline(file, line))
    {
        // Check if line starts with the word map
        if (line.find("map") == std::string::npos)
        {
            continue;
        } else {
            break;
        }
    }

    while (std::getline(file, line))
    {
        // Map starts after the line that starts with map
        grid->push_back(std::vector<char>(line.begin(), line.end()));
    }
    return grid;
}