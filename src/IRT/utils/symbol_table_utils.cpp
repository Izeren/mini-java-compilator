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

std::string getMethodClassNameByObject(
        const SymbolTable* table,
        const std::string& currentClass,
        const std::string& currentMethod,
        const std::string& objectName) {

    std::shared_ptr<const ClassInfo> clazz = table->classes.at(currentClass);
    std::shared_ptr<const MethodInfo> method = clazz->methods.at(currentMethod);

    auto argumentIt = method->arguments->variables.find(objectName);
    if (argumentIt != method->arguments->variables.end()) {
        return argumentIt->second->type->className;
    }

    auto localVariableIt = method->fields->variables.find(objectName);
    if (localVariableIt != method->fields->variables.end()) {
        return localVariableIt->second->type->className;
    }

    while (clazz != NULL) {
        auto classFieldIt = clazz->fields->variables.find(objectName);
        if (classFieldIt != clazz->fields->variables.end()) {
            return classFieldIt->second->type->className;
        }

        if (clazz->baseClass != "") {
            clazz = table->classes.at(clazz->baseClass);
        } else {
            clazz = NULL;
        }

    }

    assert(false);
}
