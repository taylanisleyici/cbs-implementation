#include "CBSSolution.h"
#include <cstddef>
#include <algorithm>

CBSSolution::CBSSolution()
{
    paths = std::vector<std::shared_ptr<CBSPath>>();
    cost = -1;
    for (std::size_t i = 0; i < paths.size(); i++)
    {
        if (paths[i] != nullptr)
        {
            cost = std::max(cost, static_cast<long>(paths[i]->path->size()));
        }
        else 
        {
            cost = -1;
            break;
        }
    }
}