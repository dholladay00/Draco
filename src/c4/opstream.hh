//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   c4/opstream.hh
 * \author Kent G. Budge
 * \brief  Define class opstream
 * \note   Copyright (C) 2018-2019 Triad National Security, LLC.
 *         All rights reserved. */
//---------------------------------------------------------------------------//

#ifndef c4_opstream_hh
#define c4_opstream_hh

#include "c4/config.h"
#include <iostream>
#include <vector>

namespace rtt_c4 {

//===========================================================================//
/*!
 * \class opstream
 *
 * Output stream for serializing output from all MPI ranks.
 *
 * This class is an output stream that serialized output from all MPI ranks.
 * Output is inserted to the stream as with any other output stream. When the
 * send() function is invoked, which *must be done synchronously across all
 * processors*, all output inserted to the stream since the last call to send()
 * is printed to cout, by MPI rank. In other words, all output inserted to
 * pout by rank 0 since the last call to send() is printed to cout, then all
 * output inserted to pout by rank 1 is printed to cout, and so on for all
 * processors. There is no requirement that any processor have actually
 * inserted any output to pout since the last cal to send(), nor does the
 * output from any processor have to resemble that from any other processor in
 * any way (though it very often will.)
 *
 * Because this requires that output be buffered in the pout for each rank
 * between send() calls, memory consumption might become significant if
 * very large blocks of output are generated by MPI ranks between calls to
 * send(). In other words, this is for TL;DR type messages to the console.
 *
 * Memory allocated for buffering is retained between calls unless the
 * shrink_to_fit function is called, which returns all memory not needed
 * for the current buffered output. In typical usage, this means pout will
 * grow its buffer size silently until it is big enough for the largest
 * blocks of output being generated, then remain there through the rest
 * of the run, unless shrink_to_fit is called.
 *
 * Any output remaining in the buffer when the buffer goes out of scope and is
 * destroyed will be discarded. The alternative, of doing a final send() as
 * part of the destructor, risks propagating an exception out of the
 * destructor, which is bad practice.
 *
 * A stream of this type can be created only after MPI is initialized, and it
 * must be  destroyed before MPI is shut down.
 *
 * \example c4/test/tstopstream.cc
 */
//===========================================================================//

class opstream : public std::ostream {
public:
  //! Create a synchronized stream tied to the console.
  opstream() : std::ostream(&sb_) { /* empty */
  }

  //! Send all buffered data synchronously to the console.
  void send() { sb_.send(); }

  //! Shrink the internal buffer to fit the current buffered data.
  void shrink_to_fit() { sb_.shrink_to_fit(); }

private:
  struct mpibuf : public std::streambuf {

    void send();
    void shrink_to_fit();

    virtual int_type overflow(int_type c);

    std::vector<char> buffer_;
  };

  mpibuf sb_;
};

} // end namespace rtt_c4

#endif // c4_opstream_hh

//---------------------------------------------------------------------------//
// end of c4/opstream.hh
//---------------------------------------------------------------------------//
