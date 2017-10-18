.literals
	x
	y
	"this is a test string"
	s
	"string"
.code
	PUSH_INTEGER 13
	SET_LOCAL Integer 0
	PUSH_INTEGER 14
	SET_LOCAL Integer 1
	PUSH_STRING 2
	SET_LOCAL String 3
	GET_LOCAL *3
	PUSH_SELF
	CALL Object_puts_String 1
	PUSH_STRING 4
	PUSH_SELF
	CALL Object_puts_String 1
