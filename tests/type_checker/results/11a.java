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
				name: num2
				type: int
			} 
		} 
	} 
}
"(9,19) : (9,22)" There is cyclic inheritance.