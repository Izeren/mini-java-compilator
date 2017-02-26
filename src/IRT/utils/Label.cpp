#include "Label.h"

using namespace IRT;

int CLabel::counter = 0;

CLabel::CLabel( ) : label( "Label" + std::to_string( counter++ )) { }

CLabel::CLabel( std::string _label ) : label( _label ) { }

std::string CLabel::ToString( ) const {
    return label;
}
