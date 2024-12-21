#ifndef __CBS_PATH_H__
#define __CBS_PATH_H__

#include <memory>
#include <utility>
#include <vector>

class CBSPath
{
  public:
    CBSPath();
    CBSPath(std::shared_ptr<std::vector<std::pair<int, int>>> path);
    ~CBSPath() = default;
  private:
    std::shared_ptr<std::vector<std::pair<int, int>>> path; // path[i] is the location of the agent at time i
};

#endif // __CBS_PATH_H__