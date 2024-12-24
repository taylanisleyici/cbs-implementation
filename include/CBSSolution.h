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
    std::vector<std::shared_ptr<CBSPath>> paths; // paths[i] is the path of agent i
    inline long int getCost() const {
        return cost;
    };

    inline void setCost(long int cost) {
        this->cost = cost;
    };
  private:
    long int cost;
};

#endif
