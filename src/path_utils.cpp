#include "../include/path_utils.hpp"
#include <string>

std::string getResourcePath(const std::string &relativePath) {
  return "./resources/" + relativePath;
}
