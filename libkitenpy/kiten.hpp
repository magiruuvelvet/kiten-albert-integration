#pragma once

#include <vector>
#include <string>

class Kiten
{
public:
    Kiten();
    ~Kiten();

    const std::vector<std::string> lookup(const char *query, unsigned int limit);

private:
    void *d = nullptr;
    bool isInitialized = false;
};
