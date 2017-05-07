#pragma once

#include <vector>
#include <map>
#include <string>
#include "../utils/Temporary.h"
#include "../utils/AssemblyCommand.h"

using AssemblyCommands = std::vector<std::shared_ptr<AssemblyCode::AssemblyCommand>>;

namespace AssemblyCode {

    struct RegisterInfo {
        IRT::CTemp espReg;
        IRT::CTemp spBeginReg;
        std::vector<std::string> registers;

    };

    AssemblyCommands allocateRegisters(AssemblyCommands& commands, RegisterInfo& registerInfo);

    void colorToRegisterChange( IRT::CTemp& temp,
            std::map<std::string, int> &tempToColorMap, AssemblyCode::RegisterInfo &registerInfo );

}
