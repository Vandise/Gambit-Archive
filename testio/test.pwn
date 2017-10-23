.literals
	x
	y
	"this is a test string"
	s
	"string"
	"asdf"
	"hello world"
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
	PUSH_STRING 6
	PUSH_SELF
	CALL Object_puts_String 1
.echo
	PUSH_STRING 5
	PUSH_SELF
	CALL Object_puts_String 1
.print_String_String
	GET_LOCAL *0
	PUSH_SELF
	CALL Object_puts_String 1
	GET_LOCAL *1
	PUSH_SELF
	CALL Object_puts_String 1
