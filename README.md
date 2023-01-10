
# The C Standard `void *` Library

## Introduction

Are you the type of person to *wince* whenever you read or hear "C/C++"? And
yet, you still kind of see some utilitarian charm in doing a `foreach` over an 
`std::map<string, int>`? Well look no further. 

That's right, with the CSVL you'll have access to a very <s>in</s>convenient
API for typeless collection data structures in standard C99 without any of the 
compile-time bloat of templates! This single small binary will allocate and
free a bunch of memory on your behalf, move random pointers around, and you'll
have an associative map with `struct unreasonably_complicated` valued keys and
`union why_are_you_doing_this` valued outputs that just <s>segfaults</s>works.

## Goals

To be very honest, if you couldn't tell by the rampant sarcasm in the
introduction, this is mostly a fun exercise. As such, there are no hard
requirements for this project. However, the principles cling to are, in short:

+ The collections should be completely generic - if you can store it in memory, 
you can make a collection out of it
+ Macros are useful, but should not be everywhere - we're not trying to emulate
templates, Leave that to C++
+ Memory locality should be a priority - a warm cache is a happy cache
+ Don't worry too much about performance - the time you save by using these
generic collections comes at the cost of making your code impossible to be 
optimized at compile-time

## Features

Right now our happy family of generic collections includes

+ Basic Iterators / `for_each` loops
+ Vectors

But the idea is to also implement

+ Advanced Iterators (`apply, filter, reduce`)
+ Stacks
+ Queues
+ Heaps
+ Lists
+ Ordered Maps
+ Unordered Maps

As well as reasonable iterators for each collection.

## Building

Just use CMake:

    cmake .
    make

Then `libcsvl.so` will be built to the `lib/` directory, and all tests/examples
will be in the `bin/` directory.

Since this builds a shared library and I can't be bothered to `__declspec`
things, for now the codebase is \*nix only.

## Dependencies

Right now I'm linking against [Criterion](https://github.com/Snaipe/Criterion)
for unit testing. If you don't have it or don't want it, just empty out
`test/CMakeLists.txt` and you'll be fine.

## Copying

Since for now this is just a fun project with no clear use case, you may use
the code in this repository solely under the permissions described in the 
[GitHub Terms of Service](https://docs.github.com/en/site-policy/github-terms/github-terms-of-service)
Section D.5. If for some reason this gets enough attention to prove to me that
other people would *actually* use it, I'll consider proper licensing.
