#ifndef __CBS_NODE_H__
#define __CBS_NODE_H__

#include "CBSConstraint.h"
#include "CBSSolution.h"
#include <memory>

class CBSNode
{
  public:
    CBSNode();
    CBSNode(std::shared_ptr<CBSConstraint> constraints, std::shared_ptr<CBSSolution> solution, long int cost, std::shared_ptr<CBSNode> parent);
    ~CBSNode() = default;
  private:
    std::shared_ptr<CBSConstraint> constraint;
    std::shared_ptr<CBSSolution> solution;
    long int cost;
    std::shared_ptr<CBSNode> parent;
    std::shared_ptr<CBSNode> leftChild;
    std::shared_ptr<CBSNode> rightChild;
};

#endif