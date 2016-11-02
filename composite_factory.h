//-*- Mode: C++ -*-

#ifndef COMPOSITE_FACTORY_H
#define COMPOSITE_FACTORY_H
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

/// @file   composite_factory.h
/// @author Matthias Richter
/// @since  2016-06-10
/// @brief  Factory for a flexible mixin class approach

// The composite factory is a compile time factory for creating combinations
// of the mixin objects depending on a property flag. An MPL map of flags to
// mixin templates has to be provided to the CompositeCreator functor

#include <memory>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/apply.hpp>

/******************************************************************************
 * @brief apply functor for recursive accumulation of creation wrappers
 * depending on runtime property.
 * 
 * This meta function loops recursively through a compile time sequence mpl
 * pairs using mpl iterators. The mpl pair consists of a flag and a type to be
 * applied to mixin if the flag is set in the runtime property.
 *
 * The meta function loops recursively to itself until the iterator is at the
 * end position, in which case the template specialization kicks in.
 *
 * TODO:
 * - a possible extension would be a more flexible operation to check the
 *   flag vs property field, currently its a bit-wise and
 */
template < typename _Interface,
           typename _Base,
           typename _Iterator,
           typename _End,
           typename _Property,
           typename _WrappersToApply >
struct WrapperAccumulation
{
  static std::shared_ptr< _Interface > apply( _Property property )
  {
    typedef typename boost::mpl::deref< _Iterator >::type        flag_to_wrapper;
    typedef typename boost::mpl::first< flag_to_wrapper >::type  flag;
    typedef typename boost::mpl::second< flag_to_wrapper >::type wrapper;

    if ( property & flag::value ) {
      // add current wrapper
      return WrapperAccumulation<
        _Interface, 
        _Base,
        typename boost::mpl::next< _Iterator >::type,
        _End,
        _Property,
        typename boost::mpl::push_back<
          _WrappersToApply,
          wrapper
          >::type
        >::apply( property );
    } else {
      // don't add current wrapper
      return WrapperAccumulation<
        _Interface,
        _Base,
        typename boost::mpl::next< _Iterator >::type,
        _End,
        _Property,
        _WrappersToApply
      >::apply( property );
    }
  }
};


/**
 * @brief termination condition for apply functor
 * The termination in the recursive loop is realized through partial template
 * specialization and reached when _Iterator is the same as _End
 *
 * Now, the complete mixin type is build from the selected wrappers by folding.
 * Finally, a shared pointer of this type is created.
 */
template < typename _Interface,
           typename _Base, 
           typename _End,
           typename _Property,
           typename _WrappersToApply >
struct WrapperAccumulation< _Interface, _Base, 
                            _End, _End, _Property, _WrappersToApply >
{
  static std::shared_ptr< _Interface > apply( _Property property )
  {
    using boost::mpl::placeholders::_1;
    using boost::mpl::placeholders::_2;

    typedef typename
      boost::mpl::fold<
        _WrappersToApply,
        _Base,
        boost::mpl::apply1< _2, _1 >
      >::type mixin;

    return std::make_shared< mixin >();
  }
};

/******************************************************************************
 * @brief meta functor to create a composite mixin depending on the property
 * Depending on the runtime property parameter, a sequence of wrappers is
 * selected to build the mixin class type. A shared pointer to an object of
 * this type is returned.
 *
 * Template Parameters:
 * - _Interface  Specifies the type of the shared pointer
 * - _Base       Base of mixin type
 * - _Property   Type of runtime property field to select wrappers
 * - WrapperMap  MPL map of property flags to wrappers
 *
 * TODO:
 * - return type and pointer creation can be generalized
 */
template < typename _Interface, typename _Base, typename _Property, typename WrapperMap >
struct CompositeCreator
{
  static std::shared_ptr< _Interface > apply( _Property property )
  {
    return WrapperAccumulation<
      _Interface,
      _Base,
      typename boost::mpl::begin< WrapperMap >::type,
      typename boost::mpl::end< WrapperMap >::type,
      _Property,
      boost::mpl::vector< >
    >::apply( property );
  }
};

#endif
