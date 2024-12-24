#ifndef __CBS_CONSTRAINT_H__
#define __CBS_CONSTRAINT_H__

#include <memory>
#include <utility>
#include "CBSAgent.h"

class CBSConstraint
{
  public:
    CBSConstraint();
    CBSConstraint(int agent, std::pair<int, int> location, int time);
    inline int getTime() const{
        return time;
    };
    inline std::pair<int, int> getLocation() const{
        return location;
    };
    inline int getAgent() const{
        return agent;
    };
    ~CBSConstraint() = default;

  private:
    int agent;
    std::pair<int, int> location;
    int time;
};

#endif