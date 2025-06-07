#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include <string>

void initBasePath();

std::string getResourcePath(const std::string &relativePath);

void createWindow();

#endif
