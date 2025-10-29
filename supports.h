#pragma once
#include <string>
#include <string>
#include <stdexcept>
#include "dllLoad.h" 

bool isNumber(const std::string& s);
bool isFunction(const std::string& token, const DllLoader::PluginMap& funcs);
int priority(const std::string& op, const DllLoader::PluginMap& functions);