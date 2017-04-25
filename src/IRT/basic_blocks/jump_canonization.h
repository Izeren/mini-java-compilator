#pragma once

#include "../visitors/CBuildVisitor.h"

namespace IRT {

    std::shared_ptr<MethodToIRTMap> canonizeJumps(std::shared_ptr<const MethodToIRTMap> trees);

}