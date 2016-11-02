# gNeric - Generic programming tools

This package provides some basic generic programming tools.

## Tools
Class/Macro                        | Description
-----------------------            | -----------
[`mixinclass.h`](mixinclass.h) | A mixin class demonstrator
[`composite_factory.h`](composite_factory.h)| A composite factory for mixin classes
[`runtime_container.h`](runtime_container.h)| Runtime container to use static polymorphism

### `mixinclass.h`
A mixin class allows to assemble class functionality from a number of independent class templates.
The templates are combined by taking the type of the previous mixin stage as template parameter.
The example implements a base class interface in order to access methods of the mixin class. The
overloaded print function demonstrates how different types of functionality are accumulated.

### `composite_factory.h`
The composite factory is a compile time factory for creating combinations
of mixin templates depending on a runtime property flag.

### `runtime_container.h`
A generic runtime container to create runtime objects for meta programming structures.
It can be used to replace runtime polymorphism by static polymorphism for time critical
algorithms. The meta programming structures are pure types without a runtime state. The
container implements a mixin approach in which every mixin level wraps a data type and
defines a member variable of the wrapped type. The different types are accessed by static
casts, which now allow the compiler to optimize the code.

## Test programs
Program                        | Description
-----------------------            | -----------
[`mixinclass.cxx`](mixinclass.cxx) | Demonstrator for usage of mixin classes as defined in `mixinclass.h`
[`dynamic_mixin.cxx`](dynamic_mixin.cxx) | Demonstrator for the composite factory for a mixin class creator
[`test_runtime_container.cxx`](test_runtime_container.cxx) | Simple test program for `runtime_container.h`
[`bench_runtime_container.cxx`](bench_runtime_container.cxx) | Simple benchmark program for `runtime_container.h`
[`multiple_distributions.cxx`](multiple_distributions.cxx) | A runtime container application for different data types
[`compare_polymorphism.cxx`](compare_polymorphism.cxx) | Comparison of runtime and static polymorphism

### `mixinclass.cxx`
Test program for a mixin based class design.

### `dynamic_mixin.cxx`
Factory approach for creating mixin assemblies depending on runtime property parameter.

### `test_runtime_container.cxx`
Preliminary test of various mpl operations and runtime container functionality. Dacomentation needs to be improved.

### `bench_runtime_container.cxx`
Preliminary benchmark program for the runtime container. Documentation and statistics printout need to be improved.

#### compilation
    g++ --std=c++11 -O3 -I$BOOST_ROOT/include -o bench_runtime_container bench_runtime_container.cxx

### `multiple_distributions.cxx`
Demonstrator for using the runtime container as a type safe container for multiple statistics distributions. The example uses distributions from std `<random>`, which do not have a common base class type.

#### compilation
    g++ --std=c++11 -g -ggdb -I$BOOST_ROOT/include -o multiple_distributions multiple_distributions.cxx

### `compare_polymorphism.cxx`
This is a lightweight test program for comparison of runtime and static polymorphism. It defines an interface
with virtual functions in the runtime polymorphic case, object pointers are stored in a stl vector.
In the static polymorphic case, a runtime container object is created from the compile time sequence of
types. The mode can be selected by compile time switches.

Switch | Description
-------|------------
-DNROLLS=number  | default is 1000000000
-DSTATIC_POLY    | select static polymorphism (default runtime)
-DBULK_OPERATION | select static polymorphism with bulk operation

#### compilation
Compilation requires the ``boost`` mpl package. It consists of header files, no library is required.
Include path has to be provided, e.g. one can set variable `BOOST_ROOT` to the boost installation and
use `-I$BOOST_ROOT/include`

    g++ --std=c++11 -O3 -I$BOOST_ROOT/include -o compare_polymorphism compare_polymorphism.cxx

Add compile switches of your choice

#### running
The test loop runs a simple incrementation of the data member of each object in the vector and simply
measures the wall time.

    ./compare_polymorphism
