class: {
	name: Main
	fields: {
	} 
	method: {
		name: main 
		isPublic: 1 
		arguments: {
			variable: {
				name: args
				type: String[]
			} 
		} 
		fields: {
		} 
	} 
}
class: {
	name: A
	base: A
	fields: {
	} 
}
class: {
	name: B
	base: C
	fields: {
	} 
}
class: {
	name: C
	base: D
	fields: {
	} 
}
class: {
	name: D
	base: B
	fields: {
	} 
}
"(6,17) : (6,18)" There is cyclic inheritance.
"(9,17) : (9,18)" There is cyclic inheritance.
"(13,17) : (13,18)" There is cyclic inheritance.
"(17,17) : (17,18)" There is cyclic inheritance.
