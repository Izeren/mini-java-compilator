#include <cassert>
#include "symbol_table_utils.h"
#include "../../symbol_table/SymbolInfo.h"

int getFieldCountWithSuper(const SymbolTable* table, const std::string& className) {
    std::shared_ptr<const ClassInfo> clazz = table->classes.at(className);

    int fieldNumberWithSuper = 0;
    while (clazz != NULL) {
        fieldNumberWithSuper += static_cast<int>(clazz->fields->variableNames.size());
        if (clazz->baseClass != "") {
            clazz = table->classes.at(clazz->baseClass);
        } else{
            clazz = NULL;
        }
    }

    return fieldNumberWithSuper;
}

std::shared_ptr<VariableInfo>
getVariableInfoFromLocalArgAndFields(const SymbolTable *table, const std::string& currentClassName,
                                     const std::string &currentMethod, const std::string &varName) {

    std::shared_ptr<const ClassInfo> clazz = table->classes.at(currentClassName);
    std::shared_ptr<const MethodInfo> method = clazz->methods.at(currentMethod);

    auto argumentIt = method->arguments->variables.find(varName);
    if (argumentIt != method->arguments->variables.end()) {
        return argumentIt->second;
    }

    auto localVariableIt = method->fields->variables.find(varName);
    if (localVariableIt != method->fields->variables.end()) {
        return localVariableIt->second;
    }

    while (clazz != NULL) {
        auto classFieldIt = clazz->fields->variables.find(varName);
        if (classFieldIt != clazz->fields->variables.end()) {
            return classFieldIt->second;
        }

        if (clazz->baseClass != "") {
            clazz = table->classes.at(clazz->baseClass);
        } else {
            clazz = NULL;
        }

    }

    assert(false);
}
