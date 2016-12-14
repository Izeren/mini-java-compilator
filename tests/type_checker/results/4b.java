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
	fields: {
	} 
	method: {
		name: ComputeFac3 
		returnType: int
		isPublic: 1 
		arguments: {
			variable: {
				name: fac
				type: Fac2
			} 
		} 
		fields: {
		} 
	} 
	method: {
		name: ComputeFac4 
		returnType: int
		isPublic: 1 
		arguments: {
			variable: {
				name: b
				type: boolean
			} 
			variable: {
				name: fac
				type: Fac2
			} 
			variable: {
				name: a
				type: int
			} 
		} 
		fields: {
		} 
	} 
	method: {
		name: ComputeFac2 
		returnType: int
		isPublic: 1 
		arguments: {
			variable: {
				name: fac
				type: Fac
			} 
		} 
		fields: {
		} 
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
"(3,9) : (3,13)" Fac2 is undeclared in this scope.
"(17,28) : (17,32)" Fac2 is undeclared in this scope.
"(21,35) : (21,39)" Fac2 is undeclared in this scope.
