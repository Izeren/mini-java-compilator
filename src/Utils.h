#pragma once

namespace enums {
	enum TOperation { PLUS, MINUS, MULTIPLY, MOD };
	enum TLogicalOperation { AND, OR };
	enum TCompareOperation { GREATER, GREATER_OR_EQUAL, LESS, LESS_OR_EQUAL };
	enum TPrimitiveType { INT, BOOLEAN, INT_ARRAY, STRING_ARRAY, ERROR_TYPE, VOID };
}
