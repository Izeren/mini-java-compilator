#include "Temporary.h"

using namespace IRT;

int CTemp::counter = 0;

CTemp::CTemp( ) : name( "Temp" + std::to_string( counter++ )) { }

CTemp::CTemp( std::string _name ) : name( _name ) { }

std::string CTemp::ToString( ) const {
    return name;
}
