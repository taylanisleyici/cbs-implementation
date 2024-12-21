#include "CBSPath.h"
#include <memory>

CBSPath::CBSPath()
{
    path = std::make_shared<std::vector<std::pair<int, int>>>();
}

CBSPath::CBSPath(std::shared_ptr<std::vector<std::pair<int, int>>> path)
{
    this->path = path;
}