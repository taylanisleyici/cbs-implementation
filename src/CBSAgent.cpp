#include "CBSAgent.h"
#include "CBSConstraint.h"
#include "CBSPath.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <queue>
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

std::shared_ptr<CBSPath> CBSAgent::findPath(const std::vector<std::shared_ptr<CBSConstraint>> &constraints)
{
    // Copy constraints and sort them by time
    std::vector<std::shared_ptr<CBSConstraint>> sortedConstraints(constraints);
    std::sort(sortedConstraints.begin(), sortedConstraints.end(),
              [](const std::shared_ptr<CBSConstraint> &a, const std::shared_ptr<CBSConstraint> &b) {
                  return a->getTime() < b->getTime();
              });
    // Find path with a star, keep track of constraints
    std::shared_ptr<std::vector<std::pair<int, int>>> path = std::make_shared<std::vector<std::pair<int, int>>>();

    int time = 0;
    std::pair<int, int> current = start;

    while (current != goal)
    {
        // Check if there is a constraint at this time
        std::shared_ptr<CBSConstraint> constraint = nullptr;
        for (const auto &c : sortedConstraints)
        {
            if (c->getTime() == time)
            {
                constraint = c;
                break;
            }
        }
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
                std::pair<int, int> next = std::make_pair(current.first + j, current.second + i);
                if (next.first < 0 || next.first >= width || next.second < 0 || next.second >= height)
                {
                    continue;
                }
                if (costToGoal[next.second][next.first] == -1)
                {
                    continue;
                }
                if (constraint != nullptr && constraint->getLocation() == next)
                {
                    continue;
                }
                if (costToGoal[next.second][next.first] < costToGoal[current.second][current.first])
                {
                    current = next;
                    path->push_back(current);
                    time++;
                    break;
                }
            }
        }
    }
    return std::make_shared<CBSPath>(path);
}