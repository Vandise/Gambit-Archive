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
An extensible compiler that accepts a language driver containing a parsed AST. Mate emits Pawn bytecode.

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
| NOOP		      | 				  | 	            |               |               | No operation  |
| PUSH_INTEGER  | Integer Obj   |               |               |               | Pushes an Integer onto the Stack |
| PUSH_STRING   | String Obj    |               |               |               | Pushes a String onto the Stack |
| PUSH_ARRAY    | Array Size n  |               |               |               | Pops n elements from the Stack and pushes an array|
| SET_LOCAL     | Class         | Identifier    |               |               | Pops top element on the Stack, sets local variable in current frame |
| POP           |               |               |               |               | Pops top element from the Stack |


