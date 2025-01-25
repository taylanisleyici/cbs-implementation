#include "CBSAgent.h"
#include "CBSConstraint.h"
#include "CBSPath.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <queue>
#include <set>
#include <vector>

CBSAgent::CBSAgent(int id, std::pair<int, int> start, std::pair<int, int> goal, int width, int height,
                   const std::shared_ptr<std::vector<std::vector<char>>> grid)
    : grid(grid)
{
    this->id = id;
    this->start = start;
    this->goal = goal;
    this->width = width;
    this->height = height;
    this->costToGoal = std::vector<std::vector<int>>(width, std::vector<int>(height, -1));
    this->initializeCostToGoal();
}

void CBSAgent::initializeCostToGoal()
{
    std::queue<std::pair<int, int>> q;
    q.push(goal);
    costToGoal[goal.first][goal.second] = 0;
    while (!q.empty())
    {
        std::pair<int, int> current = q.front();
        q.pop();
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i == 0 && j == 0)
                {
                    continue;
                }
                if (i != 0 && j != 0)
                {
                    continue;
                }
                int newY = current.second + i;
                int newX = current.first + j;
                if (newX < 0 || newX >= width || newY < 0 || newY >= height)
                {
                    continue;
                }
                if (grid->at(newX)[newY] != '.' && grid->at(newX)[newY] != 'S')
                {
                    continue;
                }
                if (costToGoal[newX][newY] == -1)
                {
                    costToGoal[newX][newY] = costToGoal[current.first][current.second] + 1;
                    q.push(std::make_pair(newX, newY));
                }
            }
        }
    }
}

struct AStarNode {
    std::pair<int, int> pos;
    int time;
    double g_score;
    double f_score;
    std::shared_ptr<AStarNode> parent;
    
    AStarNode(std::pair<int, int> p, int t, double g, double f, std::shared_ptr<AStarNode> par = nullptr)
        : pos(p), time(t), g_score(g), f_score(f), parent(par) {}
};

struct CompareNode {
    bool operator()(const std::shared_ptr<AStarNode>& a, const std::shared_ptr<AStarNode>& b) {
        return a->f_score > b->f_score;
    }
};

std::shared_ptr<CBSPath> CBSAgent::findPath(const std::vector<std::shared_ptr<CBSConstraint>>& constraints) {
    std::priority_queue<std::shared_ptr<AStarNode>, 
                       std::vector<std::shared_ptr<AStarNode>>, 
                       CompareNode> openSet;
    
    std::set<std::tuple<int, int, int>> closedSet;
    
    auto startNode = std::make_shared<AStarNode>(
        start, 
        0, 
        0, 
        costToGoal[start.second][start.first]
    );
    
    openSet.push(startNode);
    
    const std::vector<std::pair<int, int>> dirs = {
        {0, -1}, {1, 0}, {0, 1}, {-1, 0}, {0, 0}
    };
    
    while (!openSet.empty()) {
        auto current = openSet.top();
        openSet.pop();
        
        if (current->pos == goal) {
            auto path = std::make_shared<std::vector<std::pair<int, int>>>();
            auto node = current;
            while (node != nullptr) {
                path->push_back(node->pos);
                node = node->parent;
            }
            std::reverse(path->begin(), path->end());
            return std::make_shared<CBSPath>(path);
        }
        
        closedSet.insert({current->pos.first, current->pos.second, current->time});
        
        for (const auto& dir : dirs) {
            std::pair<int, int> nextPos = {
                current->pos.first + dir.first,
                current->pos.second + dir.second
            };
            
            if (nextPos.first < 0 || nextPos.first >= width || 
                nextPos.second < 0 || nextPos.second >= height) {
                continue;
            }
            
            if (costToGoal[nextPos.second][nextPos.first] == -1) {
                continue;
            }
            
            bool constrained = false;
            for (const auto& constraint : constraints) {
                if (constraint->getTime() == current->time + 1 && 
                    constraint->getLocation() == nextPos) {
                    constrained = true;
                    break;
                }
            }
            if (constrained) continue;
            
            if (closedSet.find({nextPos.first, nextPos.second, current->time + 1}) 
                != closedSet.end()) {
                continue;
            }
            
            // Calculate scores
            double g_score = current->g_score + 1;
            double h_score = costToGoal[nextPos.second][nextPos.first];
            double f_score = g_score + h_score;
            
            // Create new node
            auto nextNode = std::make_shared<AStarNode>(
                nextPos,
                current->time + 1,
                g_score,
                f_score,
                current
            );
            
            openSet.push(nextNode);
        }
    }
    
    // No path found
    return std::make_shared<CBSPath>(std::make_shared<std::vector<std::pair<int, int>>>());
}