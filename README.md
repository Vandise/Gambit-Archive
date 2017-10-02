# The Gambit Language
This is a for-educational-purposes only programming language, compiler, and virtual machine.

## Gambit
Gambit is a strongly-typed, object-based, programming language. Not much has been implemented in the language as of yet.

```
# integers
10
12

# assignment
Integer::my_age = 24

```

## Check
Check is a human-readable error handler. Though optimized for the Mate compiler, it is a shared library that can be utilized for any C++ project. Features of Check are still being implemented and error messages continue to be improved upon.

![check handler error](doc/image/check_trace.png)

### Handling Errors with Check
Check provides a simple interface for when you throw errors in your application. With Check, you have to wrap your application in a `try - catch` block in order to handle errors properly. Your errors must also implement the `iException` interface.

```cpp

class AssignDataTypeMismatch : public iException
{
	// ...
	const char * what () const throw ()
	{
		this->check->load(ASSIGN_DATATYPE_MISMATCH);
		std::vector<std::string> p;		
		p.push_back("ASSIGNMENT DATATYPE MISMATCH");
		
		return this->check->getFactory()->create()->with(p)->emit().c_str();
	};
}

try
{
	// some errorous code
	throw AssignDataTypeMismatch();
}
catch(Exception::iException &e)
{
	std::cout << e.what() << std::endl;
}
```



## Mate
An extensible compiler that accepts a language driver containing a parsed AST. Emits Pawn bytecode.

## Pawn
The bytecode output by the Mate Compiler.

| OP Code       | Operand 1     | Operand 2     | Operand 3     | Operand 4     | Description   |
| ------------- |:-------------:|:-------------:|:-------------:|:-------------:|:-------------:|
| NOOP		      | 				  | 	            |               |               | No operation  |
| PUSH_INTEGER  | Integer Obj   |               |               |               | Pushes an Integer onto the Stack |
| PUSH_STRING   | String Obj    |               |               |               | Pushes a String onto the Stack |
| PUSH_ARRAY    | Array Size n  |               |               |               | Pops n elements from the Stack and pushes an array|
| SET_LOCAL     | Class         | Identifier    |               |               | Pops top element on the Stack, sets local variable in current frame |
| POP           |               |               |               |               | Pops top element from the Stack |


