#pragma once

#include <string>

namespace IRT {

    class CTemp {
    public:
        CTemp( );

        CTemp( std::string _name );

        std::string ToString( ) const;

    private:
        std::string name;
        static int counter;
    };

}
