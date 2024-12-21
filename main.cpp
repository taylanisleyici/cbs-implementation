#include "CBSAgent.h"
#include "helpers.h"
#include <iostream>

int main()
{
    auto result = readmap("../maps/den520d.map");
    for (auto row : *result)
    {
        for (auto cell : row)
        {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
    CBSAgent deneme_agent(1, std::make_pair(105, 146), std::make_pair(158, 104), result->size(), result->at(0).size(), result);
    return 0;
}