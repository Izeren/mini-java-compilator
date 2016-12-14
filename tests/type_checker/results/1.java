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
				name: c
				type: Fac2
			} 
			variable: {
				name: b
				type: bool
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
			variable: {
				name: num_aux
				type: int
			} 
			variable: {
				name: num2
				type: int
			} 
		} 
	} 
}
"(4,10) : (4,11)" The object named: Fac2 is undeclared in this scope.
"(5,10) : (5,11)" The object named: bool is undeclared in this scope.
"(0,0) : (0,0)" Type mismatch, expected: bool got: boolean.
"(9,24) : (9,28)" Type mismatch, expected: int got: boolean.
