#pragma once
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include "dllLoad.h"
#include "supports.h"

std::vector<std::string> RPN_Parser(std::string& consoleExpr, const DllLoader::PluginMap& functions);