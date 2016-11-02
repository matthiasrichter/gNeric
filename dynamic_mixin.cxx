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

/// @file   dynamic_mixin.cxx
/// @author Matthias Richter
/// @since  2016-06-10
/// @brief  Demonstrator for the composite factory for a mixin class creator

// The composite_factory is a compile time factory for creating combinations
// of the mixin type depending on the property flag.
//
// compilation:
// g++ -o dynamic_mixin -I$BOOST_ROOT/include -std=c++11 dynamic_mixin.cxx

#include <iostream>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/apply.hpp>

#include "composite_factory.h"
#include "mixinclass.h"

/**
 * Create an instance of the interface with implementation depending on runtime
 * property.
 *
 * This function allows to create different assemblies of the mixin class
 * example. A compile time map is used to define pairs of property flags to
 * mixin templates. Finally, the CompositeCreator functor selects the active
 * mixin templates depending on the runtime property parameter and creates an
 * object of the composite type.
 */
std::shared_ptr< Interface > create( int property )
{
  using namespace boost::mpl::placeholders;

  // define a compile time map of property flags to wrappers.
  // the mpl placeholder '_' is replaced by the base class of the mixin stage
  // during mpl fold of the selected wrappers
  typedef boost::mpl::map<
    boost::mpl::pair< boost::mpl::int_< 0x01 >, oct<_> >,
    boost::mpl::pair< boost::mpl::int_< 0x02 >, dec<_> >,
    boost::mpl::pair< boost::mpl::int_< 0x04 >, hex<_> >
  > flag_to_wrapper;

  return CompositeCreator< Interface, BaseFunctionality<int>, int, flag_to_wrapper >::apply( property );
}

int main()
{
  // use volatile to indicate that this is not treated compile-time fixed
  volatile uint16_t mode = 0x1 | 0x4;
  std::shared_ptr<Interface> dyninterface1(create( mode ));
  std::cout << "======== dynamic interface 1 ======================" << std::endl;
  dyninterface1->print();
  mode = 0x2;
  std::shared_ptr<Interface> dyninterface2(create( mode ));
  std::cout << "======== dynamic interface 2 ======================" << std::endl;
  dyninterface2->print();

  std::cout << "======== mixin with boost mpl apply  ==============" << std::endl;
  // define a data type for dec on top of base functionality
  typedef dec<BaseFunctionality<int>> dec_t;

  // A simple demonstrator for mpl placeholders and apply functor.
  // Define an application of hex on top of dec_t as new data type
  // the Nth occurrence of the unnamed placeholder '_' is replaced
  // by the Nth argument, in this example '_1' could also be used
  using namespace boost::mpl::placeholders;
  typedef boost::mpl::apply1< hex<_>, dec_t >::type hexdec_t;

  // make objects from the data types and print the structure
  dec_t deco;
  hexdec_t hexdeco;
  std::cout << "one-level mixin (explicitely declared):" << std::endl;
  deco.print();
  std::cout << "two-level mixin (boost mpl apply):" << std::endl;
  hexdeco.print();
}
