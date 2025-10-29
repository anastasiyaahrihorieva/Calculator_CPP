#include <string>
#include<stack>
#include <stdexcept>
#include "dllLoad.h"
#include "parser.h"
#include "supports.h"

double Calculate(std::string& consoleExpr, const DllLoader::PluginMap& functions); 