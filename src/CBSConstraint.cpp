#include "CBSConstraint.h"
#include <memory>

CBSConstraint::CBSConstraint()
{
    this->agent = -1;
    this->location = std::make_pair(-1, -1);
    this->time = -1;
}

CBSConstraint::CBSConstraint(int agent, std::pair<int, int> location, int time)
{
    this->agent = agent;
    this->location = location;
    this->time = time;
}