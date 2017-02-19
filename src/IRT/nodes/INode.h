#pragma once

#include "../visitors/IVisitor.h"

namespace IRT {

    class INode {
    public:

        virtual void Accept( IVisitor* visitor ) const = 0;

        virtual ~INode() {}
    };

}
