#include "CBSNode.h"
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <functional>
#include <vector>

// Custom hash function for std::pair<int, int>
template <>
struct std::hash<std::pair<int, int>> {
    std::size_t operator()(const std::pair<int, int>& p) const {
        auto hash1 = std::hash<int>{}(p.first);
        auto hash2 = std::hash<int>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};


CBSNode::CBSNode()
{
    constraint = nullptr;
    solution =CBSSolution();
}

CBSNode::CBSNode(std::shared_ptr<CBSConstraint> constraint, CBSSolution  &solution, std::shared_ptr<CBSNode> parent, std::shared_ptr<std::vector<CBSAgent>> agents)
{
    this->constraint = constraint;
    this->solution = solution;
    this->parent = parent;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    this->agents = agents;
}

std::shared_ptr<CBSSolution> CBSNode::solve()
{
    if (parent == nullptr)
    {
        this->solution.paths.clear();
        this->solution.paths.reserve(agents->size());
        for (auto &agent : *agents)
        {
            this->solution.paths.emplace_back(agent.findPath({}));
        }
        if (solution.paths.back()->getLength() > solution.getCost())
        {
            solution.setCost(solution.paths.back()->getLength());
        }
    }
    else 
    {
        auto current = this;
        std::vector<std::shared_ptr<CBSConstraint>> constraints;
        auto constraint_agent = this->constraint->getAgent();
        while (current!= nullptr)
        {
            if (current->constraint != nullptr && current->constraint->getAgent() == constraint_agent)
            {
                constraints.push_back(current->constraint);
            }
            current = current->parent.get();
        }
        this->solution.paths[constraint_agent] = this->agents->at(constraint_agent).findPath(constraints);
    }

    std::size_t max_time = this->solution.getCost();

    for (std::size_t i = 0; i < max_time; i++)
    {
        std::unordered_map<std::pair<int, int>, int> conflicts;
        for (std::size_t j = 0; j < agents->size(); j++)
        {
            if (i < this->solution.paths[j]->path->size())
            {
                std::pair<int, int> location = this->solution.paths[j]->path->at(i);
                if (conflicts.find(location) != conflicts.end())
                {
                    // Resolve conflict
                    this->leftChild = std::make_shared<CBSNode>(std::make_shared<CBSConstraint>(j, location, i), this->solution, shared_from_this(), this->agents);
                    this->rightChild = std::make_shared<CBSNode>(std::make_shared<CBSConstraint>(conflicts[location], location, i), this->solution, shared_from_this(), this->agents);
                    auto leftSolution = this->leftChild->solve();
                    auto rightSolution =this->rightChild->solve();
                    if (leftSolution == nullptr && rightSolution == nullptr)
                    {
                        return nullptr;
                    }
                    if (leftSolution == nullptr)
                    {
                        return rightSolution;
                    }
                    if (rightSolution == nullptr)
                    {
                        return leftSolution;
                    }
                    return leftSolution->getCost() < rightSolution->getCost() ? leftSolution : rightSolution;
                } 
                else 
                {
                    conflicts[location] = j;
                }
            }
        }
    }
    return std::make_shared<CBSSolution>(this->solution);
}