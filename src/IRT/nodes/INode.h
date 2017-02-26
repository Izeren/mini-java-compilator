#pragma once

#include "../visitors/IVisitor.h"

namespace IRT {

    class INode {
    public:

        virtual void Accept( IVisitor& visitor ) = 0;

        virtual ~INode() {}
    };

}
