#include "CBSNode.h"
#include <memory>

CBSNode::CBSNode()
{
    constraint = nullptr;
    solution = std::make_shared<CBSSolution>();
    cost = 0;
}

CBSNode::CBSNode(std::shared_ptr<CBSConstraint> constraint, std::shared_ptr<CBSSolution> solution, long int cost, std::shared_ptr<CBSNode> parent)
{
    this->constraint = constraint;
    this->solution = solution;
    this->cost = cost;
    this->parent = parent;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
}