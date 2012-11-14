/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 Lawrence Livermore National Laboratory
 *
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
 *
 * Author: Peter D. Barnes, Jr. <pdbarnes@llnl.gov>
 */

#ifndef HASH_MURMUR3_H
#define HASH_MURMUR3_H

#include "hash-implementation.h"

namespace ns3 {
  
  namespace HashFunction {

/**
 *  \ingroup hash
 *
 *  \brief Murmur3 hash function implementation
 *
 *  Adapted from http://code.google.com/p/smhasher/
 *
 *  MurmurHash3 was written by Austin Appleby, and is placed in the public
 *  domain. The author hereby disclaims copyright to this source code.

 *  Note - The x86 and x64 versions do _not_ produce the same results, as the
 *  algorithms are optimized for their respective platforms. You can still
 *  compile and run any of them on any platform, but your performance with the
 *  non-native version will be less than optimal.
 */
class Murmur3 : public HashImplementation
{
public:
  /**
   * Compute 32-bit hash of a byte buffer
   *
   * \param [in] buffer pointer to the beginning of the buffer
   * \param [in] size length of the buffer, in bytes
   * \return 32-bit hash of the buffer
   */
  Hash32_t  GetHash32  (const char * buffer, const size_t size);
  /**
   * Compute 64-bit hash of a byte buffer.
   *
   * \param [in] buffer pointer to the beginning of the buffer
   * \param [in] size length of the buffer, in bytes
   * \return 64-bit hash of the buffer
   */
  Hash64_t  GetHash64  (const char * buffer, const size_t size);
  /**
   * Restore initial state
   */
  virtual void clear (void);

private:
  /**
   * Seed value
   *
   * This has to be a constant for all MPI ranks to generate
   * the same hash from the same string.
   */
  enum seed
    {
      SEED = 0x8BADF00D  // Ate bad food
    };

};  // class Murmur3

  }  // namespace HashFunction
  
} // namespace ns3

#endif  /* HASH_MURMUR3_H */