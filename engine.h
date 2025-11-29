#ifndef ENGINE_H
#define ENGINE_H

#include <functional>
#include <unordered_map>
#include <string>
#include <map>
#include "wrapper.h"

class Engine {
public:
    void register_command(Wrapper<Subject>* wrapper, const std::string& name);
    void execute(const std::string& name, const std::map<std::string, int>& args);

private:
    std::unordered_map<std::string, std::function<void(const std::map<std::string, int>&)>> commands_;
};

#endif 