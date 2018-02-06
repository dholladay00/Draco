//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   quadrature/Tri_Chebyshev_Legendre.cc
 * \author Kelly Thompson
 * \date   Tue Feb 22 10:21:50 2000
 * \brief  A class representing an interval Gauss-Legendre quadrature set.
 * \note   Copyright 2016-2018 Los Alamos National Security, LLC. All rights
 *         reserved. */
//---------------------------------------------------------------------------//

#include "Tri_Chebyshev_Legendre.hh"
#include "parser/utilities.hh"

namespace rtt_quadrature {
using namespace rtt_parser;

//---------------------------------------------------------------------------//
std::shared_ptr<Quadrature>
Tri_Chebyshev_Legendre::parse(Token_Stream &tokens) {
  Token token = tokens.shift();
  tokens.check_syntax(token.text() == "order", "expected an order");

  unsigned sn_order = parse_positive_integer(tokens);
  tokens.check_semantics(sn_order % 2 == 0, "order must be even");

  bool has_axis_assignments;
  unsigned mu_axis, eta_axis;
  Octant_Quadrature::parse(tokens, has_axis_assignments, mu_axis, eta_axis);

  if (has_axis_assignments)
    return std::shared_ptr<Quadrature>(
        new Tri_Chebyshev_Legendre(sn_order, mu_axis, eta_axis));
  else
    return std::shared_ptr<Quadrature>(new Tri_Chebyshev_Legendre(sn_order));
}

} // end namespace rtt_quadrature

//---------------------------------------------------------------------------//
// end of quadrature/Tri_Chebyshev_Legendre.cc
//---------------------------------------------------------------------------//
