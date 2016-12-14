class: {
	name: Factorial
	fields: {
	} 
	method: {
		name: main 
		isPublic: 1 
		arguments: {
			variable: {
				name: a
				type: String[]
			} 
		} 
		fields: {
			variable: {
				name: fac
				type: Fac
			} 
			variable: {
				name: a
				type: int
			} 
		} 
	} 
}
class: {
	name: Fac
	base: Fac
	fields: {
	} 
	method: {
		name: ComputeFac 
		returnType: int
		isPublic: 1 
		arguments: {
			variable: {
				name: num
				type: int
			} 
		} 
		fields: {
			variable: {
				name: num
				type: int
			} 
		} 
	} 
}
"(13,13) : (13,16)" Variable redefined.
"(3,13) : (3,14)" Variable redefined.
"(12,16) : (12,26)" AST construction error.
