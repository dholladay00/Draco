//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   ds++/test/tstFMA.cc
 * \author Kelly Thompson <kgt@lanl.gov>
 * \date   Wed Nov 10 09:35:09 2010
 * \brief  Test functions defined in ds++/FMA.cc
 * \note   Copyright (C) 2016-2017 Los Alamos National Security, LLC.
 *         All rights reserved. */
//---------------------------------------------------------------------------//

#include "ds++/Release.hh"
#include "ds++/ScalarUnitTest.hh"
#include <sstream>

#define FP_ACCURATE_FMA 1
#include "ds++/FMA.hh"

//---------------------------------------------------------------------------//
// Test 1: Accurate FMA
void test_fma1(rtt_dsxx::UnitTest &ut) {
  std::cout << "\n>>> Begin test 1..." << std::endl;

#define FP_ACCURATE_FMA 1
#include "ds++/FMA.hh"

  double const a(1.0e-16), b(1.0e16), c(-1.0);

  double const fma_result = fma(a, b, c);
  double const macro_fma_result = FMA(a, b, c);

  std::cout.precision(17);
  std::cout << "\nresult a*b+c      = " << fma_result << "\n"
            << "result fma(a,b,c) = " << fma(a, b, c) << "\n"
            << "result FMA(a,b,c) = " << macro_fma_result << "\n"
            << std::endl;

  if (fma_result == macro_fma_result)
    PASSMSG("With FP_ACCURATE_FMA=1, fma(a,b,c) == FMA(a,b,c).");
  else
    FAILMSG("With FP_ACCURATE_FMA=1, fma(a,b,c) != FMA(a,b,c).");

  return;
}

//---------------------------------------------------------------------------//
int main(int argc, char *argv[]) {
  rtt_dsxx::ScalarUnitTest ut(argc, argv, rtt_dsxx::release);
  try {
    test_fma1(ut);
  }
  UT_EPILOG(ut);
}

//---------------------------------------------------------------------------//
// end of tstFMA.cc
//---------------------------------------------------------------------------//
