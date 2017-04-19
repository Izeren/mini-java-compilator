#pragma once

#include "../../symbol_table/SymbolInfo.h"
#include <string>

int getFieldCountWithSuper(const SymbolTable* table, const std::string& className);

std::shared_ptr<VariableInfo> getVariableInfoFromLocalArgAndFields(
        const SymbolTable* table,
        const std::string& currentClassName,
        const std::string& currentMethod,
        const std::string& varName);