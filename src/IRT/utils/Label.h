#pragma once

#include <string>

namespace IRT {

    class CLabel {
    public:
        CLabel( );

        CLabel( std::string _label );

        std::string ToString( ) const;

    private:
        std::string label;
        static int counter;
    };

}
