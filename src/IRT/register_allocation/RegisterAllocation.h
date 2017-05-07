#pragma once

#include <vector>
#include <string>
#include "ControlFlowGraphBuilder.h"

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
