#include "CBSAgent.h"
#include "CBSConstraint.h"
#include "CBSPath.h"
#include <algorithm>
#include <memory>
#include <queue>
#include <fstream>
#include <vector>

CBSAgent::CBSAgent(int id, std::pair<int, int> start, std::pair<int, int> goal, int width, int height, const std::shared_ptr<std::vector<std::vector<char>>> grid) : grid(grid)
{
    this->id = id;
    this->start = start;
    this->goal = goal;
    this->width = width;
    this->height = height;
    this->costToGoal = std::vector<std::vector<int>>(width, std::vector<int>(height, -1));
    this->initializeCostToGoal();
}

void CBSAgent::initializeCostToGoal() {
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

std::shared_ptr<CBSPath> CBSAgent::findPath(const std::vector<std::shared_ptr<CBSConstraint>> &constraints)
{
    // Copy constraints and sort them by time
    std::vector<std::shared_ptr<CBSConstraint>> sortedConstraints(constraints);
    std::sort(sortedConstraints.begin(), sortedConstraints.end(), [](const std::shared_ptr<CBSConstraint> &a, const std::shared_ptr<CBSConstraint> &b) {
        return a->getTime() < b->getTime();
    });
    // Find path with a star, keep track of constraints
    std::shared_ptr<std::vector<std::pair<int, int>>> path = std::make_shared<std::vector<std::pair<int, int>>>();

    // TODO: Create a priority queue to store visiteds. Use cost to goal to solve A*.    
}