#ifndef __CBS_NODE_H__
#define __CBS_NODE_H__

#include "CBSConstraint.h"
#include "CBSSolution.h"
#include <memory>
#include <vector>

class CBSNode : public std::enable_shared_from_this<CBSNode>
{
  public:
    CBSNode();
    CBSNode(std::shared_ptr<CBSConstraint> constraints, CBSSolution &solution, std::shared_ptr<CBSNode> parent, std::shared_ptr<std::vector<CBSAgent>> agents);
    std::shared_ptr<CBSSolution> solve();
    ~CBSNode() = default;
  private:
    std::shared_ptr<CBSConstraint> constraint;
    CBSSolution solution;
    long int cost;
    std::shared_ptr<CBSNode> parent;
    std::shared_ptr<CBSNode> leftChild;
    std::shared_ptr<CBSNode> rightChild;
    std::shared_ptr<std::vector<CBSAgent>> agents;
};

#endif