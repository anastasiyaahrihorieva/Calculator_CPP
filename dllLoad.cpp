#include <filesystem>
#include <iostream>
#include "dllLoad.h"

DllLoader::DllLoader(const std::string& pluginDir) {
    namespace fs = std::filesystem;

    if (!fs::exists(pluginDir) || !fs::is_directory(pluginDir)) {
        std::cerr << "Plugin directory not found: " << pluginDir << std::endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(pluginDir)) {
        if (entry.path().extension() == ".dll") {
            HMODULE hMod = LoadLibraryW(entry.path().c_str());
            if (!hMod) {
                std::cerr << "Failed to load DLL: " << entry.path().filename().string() << std::endl;
                continue;
            }

            auto getNameFunc = reinterpret_cast<const char* (*)()>( 
                GetProcAddress(hMod, "get_function_name")
            );
            auto evalFunc = reinterpret_cast<PluginFunc>(
                GetProcAddress(hMod, "evaluate")
            );

            if (!getNameFunc || !evalFunc) {
                std::cerr << "DLL " << entry.path().filename().string()
                          << " missing required exports" << std::endl;
                FreeLibrary(hMod);
                continue;
            }

            std::string funcName = getNameFunc();
            functions_[funcName] = [evalFunc](double x) -> double {
                return evalFunc(x);
            };

            loadedModules_.push_back(hMod);
            std::cout << "Loaded plugin: " << funcName << " from " << entry.path().filename().string() << std::endl;
        }
    }
}

DllLoader::~DllLoader() {
    for (HMODULE mod : loadedModules_) {
        FreeLibrary(mod);
    }
}