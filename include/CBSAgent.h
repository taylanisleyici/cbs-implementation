#ifndef __CBS_AGENT_H__
#define __CBS_AGENT_H__

#include "CBSPath.h"
#include <memory>
#include <utility>
#include <vector>

class CBSConstraint;

class CBSAgent{
    public:
        CBSAgent(int id, std::pair<int, int> start, std::pair<int, int> goal, int height, int width, const std::shared_ptr<std::vector<std::vector<char>>> grid);
        std::shared_ptr<CBSPath> findPath(const std::vector<std::shared_ptr<CBSConstraint>> &constraints);
        ~CBSAgent() = default;
    private:
        int id;
        std::pair<int, int> start;
        std::pair<int, int> goal;
        int width;
        int height;
        std::vector<std::vector<int>> costToGoal;
        const std::shared_ptr<std::vector<std::vector<char>>> grid;
        bool isInitialized = false;

        void initializeCostToGoal();
};

#endif // __CBS_AGENT_H__