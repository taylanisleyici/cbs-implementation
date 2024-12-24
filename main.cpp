#include "CBSAgent.h"
#include "CBSNode.h"
#include "CBSSolution.h"
#include "helpers.h"
#include <cstddef>
#include <iostream>
#include <utility>

int main()
{
    auto result = readmap("../maps/deneme.map");
    for (auto row : *result)
    {
        for (auto cell : row)
        {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
    CBSAgent a1(0, std::make_pair(3, 3), std::make_pair(2, 2), result->size(), result->at(0).size(), result);
    CBSAgent a2(1, std::make_pair(2, 1), std::make_pair(0, 0), result->size(), result->at(0).size(), result);
    CBSSolution emptySolution;
    CBSNode parent(nullptr, emptySolution, nullptr, std::make_shared<std::vector<CBSAgent>>(std::vector<CBSAgent>{a1, a2}));
    auto solution = parent.solve();
    for (std::size_t i = 0; i < solution->paths.size(); i++)
    {
        std::cout << "Path" << i << std::endl;
        for (auto location : *solution->paths[i]->path)
        {
            std::cout << location.first << " " << location.second << std::endl;
        }
    }
    return 0;
}