/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"


// Default Network Topology
//
//   Wifi 10.1.3.0
//                 AP
//  *    *    *    *
//  |    |    |    |    10.1.1.0
// n5   n6   n7   n0 -------------- n1   n2   n3   n4
//                   point-to-point  |    |    |    |
//                                   ================
//                                     LAN 10.1.2.0

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ThirdScriptExample");

#define OLSR_C 0.0625

uint8_t
SecondsToEmf (double seconds)
{
  int a, b = 0;

  double fracPart, intPart;
  fracPart = modf(seconds, &intPart);
  if(fracPart < .00005)
	  seconds = intPart;

  // find the largest integer 'b' such that: T/C >= 2^b
  for (b = 0; (seconds/OLSR_C) >= (1 << b); ++b)
    ;
  NS_ASSERT ((seconds/OLSR_C) < (1 << b));
  b--;
  NS_ASSERT ((seconds/OLSR_C) >= (1 << b));

  // compute the expression 16*(T/(C*(2^b))-1), which may not be a integer
  double tmp = 16*(seconds/(OLSR_C*(1<<b))-1);

  // round it up.  This results in the value for 'a'
  a = (int) std::ceil (tmp);

  // if 'a' is equal to 16: increment 'b' by one, and set 'a' to 0
  if (a == 16)
    {
      b += 1;
      a = 0;
    }

  // now, 'a' and 'b' should be integers between 0 and 15,
  NS_ASSERT (a >= 0 && a < 16);
  NS_ASSERT (b >= 0 && b < 16);

  // the field will be a byte holding the value a*16+b
  return (uint8_t)((a << 4) | b);
}

double
EmfToSeconds (uint8_t olsrFormat)
{
  int a = (olsrFormat >> 4);
  int b = (olsrFormat & 0xf);
  // value = C*(1+a/16)*2^b [in seconds]
  return OLSR_C * (1 + a/16.0) * (1 << b);
}

int 
main (int argc, char *argv[])
{
	std::cout << EmfToSeconds(SecondsToEmf(15.0)) << std::endl;
	std::cout << EmfToSeconds(SecondsToEmf(15.000000000000002)) << std::endl;
}
