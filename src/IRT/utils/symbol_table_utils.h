#pragma once

#include "../../symbol_table/SymbolInfo.h"
#include <string>

int getFieldCountWithSuper(const SymbolTable* table, const std::string& className);

std::string getMethodClassNameByObject(
        const SymbolTable* table,
        const std::string& currentClass,
        const std::string& currentMethod,
        const std::string& objectName);
