#pragma once

#include <vector>
#include "ControlFlowGraphBuilder.h"

namespace AssemblyCode {

    AssemblyCommands allocateRegisters(AssemblyCommands& commands, int registerNumber);

}
