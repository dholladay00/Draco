//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   ds++/SP.hh
 * \author Geoffrey Furnish, Thomas Evans
 * \date   Tue Feb  4 11:27:53 2003
 * \brief  Smart Point class file.
 * \note   Copyright (C) 2016-2017 Los Alamos National Security, LLC.
 *         All rights reserved.
 */
//---------------------------------------------------------------------------//

#ifndef RTT_ds_SP_HH
#define RTT_ds_SP_HH

#include "Assert.hh"
#include <memory>
#include <typeinfo>

namespace rtt_dsxx {

template <class T> using SP = std::shared_ptr<T>;

using std::dynamic_pointer_cast;

} // end namespace rtt_dsxx

#endif // RTT_ds_SP_HH

//---------------------------------------------------------------------------//
// end of ds++/SP.hh
//---------------------------------------------------------------------------//
