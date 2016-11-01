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
dynamic_mixin.cxx
mixinclass.cxx

test_runtime_container.cxx
bench_runtime_container.cxx
multiple_distributions.cxx
compare_polymorphism.cxx
