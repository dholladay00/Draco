//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   c4/test/tstglobal_containers.cc
 * \author Kent Budge
 * \date   Mon Mar 24 09:41:04 2008
 * \note   Copyright (C) 2008-2017 Los Alamos National Security, LLC.
 *         All rights reserved. */
//---------------------------------------------------------------------------//

#include "c4/ParallelUnitTest.hh"
#include "c4/global_containers.i.hh"
#include "ds++/Release.hh"
#include "ds++/Soft_Equivalence.hh"
#include <cmath>
#include <set>

using namespace std;
using namespace rtt_dsxx;
using namespace rtt_c4;

//---------------------------------------------------------------------------//
// TESTS
//---------------------------------------------------------------------------//
#ifdef C4_MPI
void tstglobal_containers(UnitTest &ut) {
  unsigned const pid = rtt_c4::node();
  unsigned const number_of_processors = rtt_c4::nodes();

  {
    set<unsigned> local_set;
    local_set.insert(pid);
    local_set.insert(number_of_processors + pid);

    global_merge(local_set);

    if (local_set.size() == 2 * number_of_processors)
      PASSMSG("Correct number of global elements");
    else
      FAILMSG("NOT correct number of global elements");

    for (unsigned p = 0; p < number_of_processors; ++p) {
      if (local_set.count(p) != 1 ||
          local_set.count(number_of_processors + p) != 1) {
        FAILMSG("WRONG element in set");
      }
    }
  }

  {
    map<unsigned, double> local_map;
    local_map[pid] = pid;
    local_map[number_of_processors + pid] = 2 * pid;

    global_merge(local_map);

    if (local_map.size() == 2 * number_of_processors)
      PASSMSG("Correct number of global elements");
    else
      FAILMSG("NOT correct number of global elements");

    for (unsigned p = 0; p < number_of_processors; ++p) {
      if (local_map.count(p) != 1 ||
          local_map.count(number_of_processors + p) != 1) {
        FAILMSG("WRONG element in map");
      }
      if (!rtt_dsxx::soft_equiv(local_map[p], static_cast<double>(p)) ||
          !rtt_dsxx::soft_equiv(local_map[number_of_processors + p],
                                static_cast<double>(2 * p))) {
        FAILMSG("WRONG element value in map");
      }
    }
  }

  {
    map<unsigned, bool> local_map;
    local_map[pid] = false;
    local_map[number_of_processors + pid] = true;

    global_merge(local_map);

    if (local_map.size() == 2 * number_of_processors)
      PASSMSG("Correct number of global elements");
    else
      FAILMSG("NOT correct number of global elements");

    for (unsigned p = 0; p < number_of_processors; ++p) {
      if (local_map.count(p) != 1 ||
          local_map.count(number_of_processors + p) != 1) {
        FAILMSG("WRONG element in map");
      }
      if (local_map[p] != false ||
          local_map[number_of_processors + p] != true) {
        FAILMSG("WRONG element value in map");
      }
    }
  }
}
#endif // C4_MPI

//---------------------------------------------------------------------------//
int main(int argc, char *argv[]) {
  rtt_c4::ParallelUnitTest ut(argc, argv, release);
  try {
#ifdef C4_MPI
    tstglobal_containers(ut);
#else
    PASSMSG("Test inactive for scalar");

#endif // C4_MPI
  } catch (exception &err) {
    cout << "ERROR: While testing tstglobal_containers, " << err.what() << endl;
    ut.numFails++;
  } catch (...) {
    cout << "ERROR: While testing tstglobal_containers, "
         << "An unknown exception was thrown." << endl;
    ut.numFails++;
  }
  return ut.numFails;
}

//---------------------------------------------------------------------------//
// end of tstglobal_containers.cc
//---------------------------------------------------------------------------//
