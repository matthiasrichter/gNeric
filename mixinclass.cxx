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

/// @file   mixinclass.cxx
/// @author Matthias Richter
/// @since  2016-06-10
/// @brief  Demonstrator for usage of mixin classes as defined in mixinclass.h

// See header files for additional comments
//
// compilation:
// g++ -o mixinclass -std=c++11 mixinclass.cxx
//
// run:
// ./mixinclass

#include "mixinclass.h"

typedef BaseFunctionality<int> IntFunctionality;

int main()
{
  hex<IntFunctionality > plainhex;
  oct< hex<IntFunctionality > > octhex;
  oct< dec< hex<IntFunctionality > > > octdechex;
  oct< dec< oct<IntFunctionality > > > octdecoct;

  std::cout << "==============================" << std::endl;
  plainhex.print();
  std::cout << "==============================" << std::endl;
  octhex.print();
  std::cout << "==============================" << std::endl;
  octdechex.print();
  std::cout << "==============================" << std::endl;
  octdecoct.print();
}
