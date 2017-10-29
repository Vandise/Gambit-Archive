.literals
	x
	y
	"this is a test string"
	s
	"string"
	"asdf"
	a
	b
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
	GET_LOCAL *3
	PUSH_STRING 8
	PUSH_SELF
	CALL Object_print_String_String 2
	RETURN 0
.Object_echo
	PUSH_STRING 5
	PUSH_SELF
	CALL Object_puts_String 1
	RETURN 0
.Object_print_String_String
	SET_LOCAL String 6
	SET_LOCAL String 7
	GET_LOCAL *6
	PUSH_SELF
	CALL Object_puts_String 1
	GET_LOCAL *7
	PUSH_SELF
	CALL Object_puts_String 1
	GET_LOCAL *6
	RETURN 1
