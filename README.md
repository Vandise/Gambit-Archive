# The Gambit Language
This is a for-educational-purposes only programming language, compiler, and virtual machine.

## How to build this project
This project requires both a C (for extensions) and C++ compiler. By default it was tested on `GCC v8.1.0`, `clang version 4.0.0`, and `g++` with modifications to the makefile parameters. `sed` is also utilized to resolve and compile dependencies.

This project depends on bison v3.0.4 and flex v2.5.37. I can't guarantee it'll work on other versions, so they are included in the util package. Compile these two projects and update `build/gambit.mk` to point to their executables. You will also need to update the following line in the `Makefile` to include the header within util/flex as opposed to your system headers. You do not need to install these on your system, but the executables to generate the grammar files are needed.

```
INC         := -I$(INCDIR) -Isrc -Isrc/test -I$(LIBDIR) -I$(EXTDIR) -I/usr/local/opt/flex/include
```

Within the `build` directory, there is a bash file that will run various make commands to setup the mate compiler and its dependencies.

### What has this been tested on?
Mac, Ubuntu, CentOS.

### Will this work on Windows?
Possibly. If you utilize `clang v4.0` with C++ installed, set your PATH to include `mingw-w64`, and have `gnuwin32` on your system: you might be able to get Mate to compile. Due to different versions of `Flex`, `Bision`, and `Sed`, it is unlikely. 

Mate utilizes two external libraries, `args.hxx` for argument parsing, and `debugnew` for memory debugging. These both port over to Windows without an issue.  

Porting to Windows may come in the future.

## Gambit
Gambit is a strongly-typed, object-based, programming language. Not much has been implemented in the language as of yet.

```
# integers
10
12

# strings
"Benjamin Anderson"

# assignment
Integer::my_age = 24

#get locals
my_age


# methods (in current scope)
String::my_name = "Benjamin Anderson"

puts(my_name)

# method definitions
@echo -> Void
{
 puts("asdf")
}


@print_and_return -> String::a -> String::b -> String
{
  puts(a)
  puts(b)
  => a
}

```

## Board
Board is an in-memory log and VM state capture system that allows you to visualize the state of the RookVM. It can be utilized for debugging memory, bugs in the VM/instruction set, or for educational purposes.

![check handler error](doc/image/board_debug.png)

## Check
Check is a human-readable error handler. Though optimized for the Mate compiler, it is a shared library that can be utilized for any C++ project. Features of Check are still being implemented and error messages continue to be improved upon.

![check handler error](doc/image/return_type.png)

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
An extensible compiler that accepts a language driver containing a parsed AST. Mate emits Pawn bytecode.

### Basic Usage
Mate has the following flags:

```
-h displays the help meny
-c[filename] compile a file
-o[outfile] output filename of pawn bytecode
```

Example: `matec -c test.gbt -o test.pwn`

### Extending Mate / Gambit
Mate provides a simple interface for creating extensions. Mate uses `dlfcn` for extensions, so you can utilize both C and C++. This is still under development. A generic Make file will be provided once the interface is finalized. Macros will also be defined.

The following headers are required to create an extension (with methods) in Mate:

```cpp
#include "shared/runtime/iStandardClass.hpp"
#include "shared/runtime/iMethod.hpp"
```

The extension signature has a `create` definition and `destroy` definition:

```cpp
extern "C" Runtime::iStandardClass* create(Runtime::iStandardClass* runtime)
{
  return runtime;
}

extern "C" void destroy(Runtime::iStandardClass* runtime)
{
	// mate will delete your object passed to the runtime.
	// ensure your destructor is virtual to do needed cleanup
	// use destroy to add some debugging, local variable deleting, etc.
}

```

#### Adding Objects to the Runtime
When creating an extension, using native C++ classes that extend `Runtime::iStandardClass` is the easiest approach.

```cpp
namespace Runtime
{

  class Sqlite : public Runtime::iStandardClass
  {

    private:
      sqlite3 *db;
      int rc;

    public:

      using Runtime::iStandardClass::iStandardClass;

      virtual ~Sqlite()
      {
        std::cout << "deleting sqlite" << std::endl;
      };

  };
}

#define SQLITE_CLASS_NAME "Sqlite"

extern "C" Runtime::iStandardClass* create(Runtime::iStandardClass* obj)
{
  Runtime::Sqlite *sqliteExt = new Runtime::Sqlite(SQLITE_CLASS_NAME);
 
  // Sqlite class inherits from Object in our runtime
  sqliteExt->setSuperClass(obj);

  // register our class in the runtime
  obj->setConstant(SQLITE_CLASS_NAME, sqliteExt);

  return sqliteExt;
}
```

#### Adding Methods
Methods are also objects. The method interface is currently incomplete, Mate does not yet recognize data types for method parameters and return types. You can, however, currently add methods and execute them within the C++ environment.

```cpp

namespace Runtime
{

  // .. previous code

  class SqliteInitializeMethod : public Runtime::iMethod
  {

    public:

      SqliteInitializeMethod()
      {
        // parameter datatypes
        PARAMETER_TYPE("String")
        PARAMETER_TYPE("Integer");
      };

      virtual Runtime::iStandardClass* call(Runtime::iStandardClass *receiver, std::vector<Runtime::iStandardClass*> arguments)
      {
        std::cout << "called initialize" << std::endl;
        return receiver;
      };

  };
}

extern "C" Runtime::iStandardClass* create(Runtime::iStandardClass* obj)
{
  Runtime::Sqlite *sqliteExt = new Runtime::Sqlite("Sqlite");

  sqliteExt->setSuperClass(obj);

  // bind native method to runtime "initialize" on sqlite object
  sqliteExt->addMethod("initialize", (new Runtime::SqliteInitializeMethod()));

  obj->setConstant("Sqlite", sqliteExt);

  return sqliteExt;
}

```

## Pawn
The bytecode output by the Mate Compiler.

| OP Code       | Operand 1     | Operand 2     | Operand 3     | Operand 4     | Description   |
| ------------- |:-------------:|:-------------:|:-------------:|:-------------:|:-------------:|
| NOOP		      | 				      | 	            |               |               | No operation  |
| PUSH_INTEGER  | Integer Obj   |               |               |               | Pushes an Integer onto the Stack |
| PUSH_STRING   | String Obj    |               |               |               | Pushes a String onto the Stack |
| PUSH_ARRAY    | Array Size n  |               |               |               | Pops n elements from the Stack and pushes an array|
| SET_LOCAL     | Class         | Identifier    |               |               | Pops top element on the Stack, sets local variable in current frame |
| PUSH_SELF     |               |               |               |               | Pushes the current object context onto the stack |
| CALL          | String MethodSignature | Args Count |         |               | Executes a method. Pushes result to stack. Void types are popped from the stack immediately |
| GET_LOCAL     | < *&>LiteralOffset |          |               |               | Gets local from current scope. ByReference or Value |
| RETURN		    | Bool PopStack	| 	            |               |               | Exits current frame. Operand 1 tells the VM whether or not to return a value  |
| POP           |               |               |               |               | Pops top element from the Stack |

The following are operators that can be appended to operands to modify the state/behavior of the virtual machine.

| Operator      | Description   |
| ------------- |:-------------:|
|               | Default behavior of instruction |
| *             | By Value - Clone        |
| &             | By Reference - Pointer  |


### Pawn to Assembler 
Pawns instructions are slowly being optimized to have a 1 ~ 2 or 3 corrospondence to Assembler. The Rook VM does many assumptions for us, for example, for each method and the initial `.code` block, Rook does the following:

```C++
// create a new frame and push it onto the stack
VM::iFrame* f = new VM::iFrame("frame identifier");
this->cg->getFrameStack()->pushFrame(f);
```

Whereas in Assembler, we have to explicitly state we are pushing up the base pointer

```asm
  pushl   %ebp
  movl    %esp,   %ebp
```

So each code and method label would have to begin with the above.

Pawn, like assembler, has a return statement at the end of each method and code block. Pawn, however, has an operand that states if the return value will be pushed to the parent frame/stack. Assembler moves the return value into `eax / rax`.

```
.code
// pawn bytecode
PUSH_INTEGER	10
RETURN 1
```

Would be the ASM equivelent

```asm
.start
  pushl   %ebp
  movl    %esp,   %ebp
  pushl	$10
  popl    %eax
  movl    %ebp,   %esp
  popl    %ebp
  ret						; 10 is in eax
```

### The RookVM Doesn't Care
The RookVM doesn't care about data types, it will call any function in its bytecode ie:

```
PUSH_INTEGER 10
CALL Object_puts_String
```

Even if the datatype on the stack would be incorrect. That is why we have the Mate Compiler to handle this for us.

### Literals Section is Just Data
The literals section in the Pawn Bytecode. C++ can easily load parsed text into memory, ASM needs a few extra steps

```asm
; pawn bytecode
; .literals
;	"this is a string"
; needs to translate to

.section data
	s_01: .ascii "this is a string\0"

; whenever it's used, you need to get the length
.start
	; frame pushing etc inferred
	pushl	$s_01
	call	str_len
	; eax now has the string length
```

### The issue with locals
Due to the nature of the Gambit Runtime, locals are not offset-based; but rather identifier-offset based. The RookVM still tracks identifiers, which is simple for VM reasons, but not practical in an ASM environment. The solution would be to add identifier offset tracking on a frame-basis.

## Where are the unit tests?
Test first, or you'll never write tests. That is the case with this project, except this is strictly a proof-of-concept as opposed to me actually wanting to build something to be taken seriously. It's for my and others learning purposes. Eventually I'll rewrite the entire project with tests (with catch.h) from the start as there is an end goal with the POC. Yes, a compiler and virtual machine require a lot of code to not consider writing tests from the start, but I'm patient.

## License
MIT - For educational purposes only.
