#pragma once

#include <string>

namespace IRT {

    class CTemp {
    public:
        CTemp( );

        CTemp( std::string _name );

        void setName(const std::string& string);

        std::string ToString( ) const;

    private:
        std::string name;
        static int counter;
    };

}
