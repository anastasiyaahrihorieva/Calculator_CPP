#include "PluginManager.h"
#include <windows.h>
#include <filesystem>
#include <vector>

struct PluginManager::Impl {
    std::vector<std::shared_ptr<IOperation>> operations_;
    std::vector<HMODULE> loadedLibraries_;
};

PluginManager::PluginManager() : pimpl_(new Impl()) {}

PluginManager::~PluginManager() {
    for (auto& lib : pimpl_->loadedLibraries_) {
        FreeLibrary(lib);
    }
    delete pimpl_;
}

std::vector<std::shared_ptr<IOperation>> PluginManager::loadPlugins(const std::string& directory) {
    pimpl_->operations_.clear(); 
    
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".dll") {
            auto operation = createFromLibrary(entry.path().string());
            pimpl_->operations_.push_back(operation);
        }
    }
    
    return getOperations();
}

std::vector<std::shared_ptr<IOperation>> PluginManager::getOperations() const {
    return pimpl_->operations_;
}

std::shared_ptr<IOperation> PluginManager::createFromLibrary(const std::string& path) {
    HMODULE library = LoadLibraryA(path.c_str());
    auto getPluginInfo = reinterpret_cast<PluginInfo(*)()>(GetProcAddress(library, "getPluginInfo"));
    PluginInfo info = getPluginInfo();
    
    pimpl_->loadedLibraries_.push_back(library);
    
    return std::make_shared<FunctionOperation>(
        info.functionName, 
        info.functionPtr, 
        info.argumentCount
    );
}