#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <memory>
#include <string>
#include <vector>

std::shared_ptr<std::vector<std::vector<char>>> readmap(const std::string &filename);

#endif // __HELPERS_H__