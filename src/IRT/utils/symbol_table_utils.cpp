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

