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
				name: b
				type: boolean
			} 
			variable: {
				name: fac
				type: Fac
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
		} 
	} 
}
"(7,28) : (7,32)" Type mismatch, expected: int got: boolean.
"(9,28) : (9,29)" Type mismatch, expected: int got: boolean.
"(15,16) : (15,26)" AST construction error.
