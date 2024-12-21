#ifndef __CBS_SOLUTION_H__
#define __CBS_SOLUTION_H__

#include <memory>
#include <vector>
#include "CBSPath.h"

class CBSSolution
{
  public:
    CBSSolution();
    ~CBSSolution() = default;
  private:
    std::vector<std::shared_ptr<CBSPath>> paths; // paths[i] is the path of agent i
};

#endif
