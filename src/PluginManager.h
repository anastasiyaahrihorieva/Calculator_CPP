#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "IOperation.h"
#include "FunctionOperation.h"
#include <string>
#include <vector>
#include <memory>

class PluginManager {
public:
    PluginManager();
    ~PluginManager();

    std::vector<std::shared_ptr<IOperation>> loadPlugins(const std::string& directory);
    std::vector<std::shared_ptr<IOperation>> getOperations() const;

    PluginManager(const PluginManager&) = delete;
    PluginManager& operator=(const PluginManager&) = delete;

private:
    struct Impl;
    Impl* pimpl_;
    std::shared_ptr<IOperation> createFromLibrary(const std::string& path);
};

#endif
