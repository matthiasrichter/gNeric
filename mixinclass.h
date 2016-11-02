//-*- Mode: C++ -*-

#ifndef MIXINCLASS_H
#define MIXINCLASS_H
//****************************************************************************
//* This file is free software: you can redistribute it and/or modify        *
//* it under the terms of the GNU General Public License as published by     *
//* the Free Software Foundation, either version 3 of the License, or        *
//* (at your option) any later version.                                      *
//*                                                                          *
//* Primary Author(s): Matthias Richter <mail@matthias-richter.com>          *
//*                                                                          *
//* The authors make no claims about the suitability of this software for    *
//* any purpose. It is provided "as is" without express or implied warranty. *
//****************************************************************************

/// @file   mixinclass.h
/// @author Matthias Richter
/// @since  2016-06-10
/// @brief  A mixin class demonstrator

// Demonstrator for a mixin class to combine functionality from
// orthogonal functional modules. This is a pure theoretical example,
// the module names (hexa)decimal and octal are chosen arbitrarily.
// But this can illustrate orthogonal groups of functionality.
//
// In this example, functionality is accumulated rather then replaced
// by overloading.

#include <iostream>
#include <iomanip>

/**
 * @class Interface
 * A common interface
 */
class Interface {
 public:
  Interface() {}
  ~Interface() {}

  virtual void print() = 0;
};

/**
 * @class BaseFunctionality
 * @brief Basic functionality of the mixin class
 *
 * A mixin class always has some kind of base functionality which is used
 * as template parameter to the first mixin stage. The print function implements
 * the "orthogonal" mixin functionality. It is also possible to define individual
 * functions per mixin template, that implies also an extension of the interface
 * class.
 */
template<typename T>
struct BaseFunctionality : public Interface
{
 BaseFunctionality() : value(0xdead) {}
  typedef T value_type;
  value_type value;
  void set(value_type v) { value = v; }
  value_type get() const { return value; }
  void print() {
    std::cout << "The base functionality" << std::endl;
  }
};

/**
 * @class dec
 * Mixin class template implements printout in decimal format
 */
template <typename BASE>
struct dec : public BASE
{
  typedef typename BASE::value_type value_type;
  void print() {
    std::cout << "The decimal     functionality: v=" << std::dec << BASE::get() << std::endl;
    BASE::print();
  }
};

/**
 * @class hex
 * Mixin class template implements printout in hexadecimal format
 */
template <typename BASE>
struct hex : public BASE
{
  typedef typename BASE::value_type value_type;
  void print() {
    std::cout << "The hexadecimal functionality: v=0x" << std::hex << BASE::get() << std::endl;
    BASE::print();
  }
};

/**
 * @class oct
 * Mixin class template implements printout in octal format
 */
template <typename BASE>
struct oct : public BASE
{
  typedef typename BASE::value_type value_type;
  void print() {
    std::cout << "The octal       functionality: v=0" << std::oct << BASE::get() << std::endl;
    BASE::print();
  }
};
#endif
