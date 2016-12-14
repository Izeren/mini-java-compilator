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
				type: Fac2
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
"(3,14) : (3,17)" The object named: Fac2 is undeclared in this scope.
"(7,19) : (7,22)" There is cyclic inheritance.
