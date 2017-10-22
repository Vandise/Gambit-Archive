.literals
	"this is a test string"
	s
	"asdf"
	x
	y
	"hello"
.code
	PUSH_STRING 0
	SET_LOCAL String 1
	GET_LOCAL *1
	PUSH_STRING 5
	PUSH_SELF
	CALL Object_print_String_String 2
.Object_echo
	PUSH_STRING 2
	PUSH_SELF
	CALL Object_puts_String 1
.Object_print_String_String
	GET_LOCAL *3
	PUSH_SELF
	CALL Object_puts_String 1
	GET_LOCAL *4
	PUSH_SELF
	CALL Object_puts_String 1
