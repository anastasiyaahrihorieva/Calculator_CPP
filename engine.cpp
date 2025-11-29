#include "engine.h"

void Engine::register_command(Wrapper<Subject>* wrapper, const std::string& name) {
    commands_[name] = [wrapper](const std::map<std::string, int>& args) {
        wrapper->call(args);
    };
}

void Engine::execute(const std::string& name, const std::map<std::string, int>& args) {
    if (commands_.count(name)) {
        commands_[name](args);
    } else {
        throw std::runtime_error("Command not found: " + name);
    }
}