#pragma once

#include <string>
#include <functional>
#include <map>

#ifdef _WIN32
#include <windows.h>
#endif

class DllLoader {
public:
    using PluginFunc = double(*)(double);
    using PluginMap = std::map<std::string, std::function<double(double)>>;

    DllLoader(const std::string& pluginDir = "./plugins");
    ~DllLoader();

    const PluginMap& getFunctions() const { return functions_; }

private:
    std::vector<HMODULE> loadedModules_;
    PluginMap functions_;
};