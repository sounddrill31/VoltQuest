#include "../include/path_utils.hpp"
#include <filesystem>
#include <string>

static std::string basePath;

void initBasePath() { basePath = std::filesystem::current_path().string(); }

std::string getResourcePath(const std::string &relativePath) {
  return basePath + "/resources/" + relativePath;
}
