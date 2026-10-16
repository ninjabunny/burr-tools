/* BurrTools
 *
 * BurrTools is the legal property of its developers, whose
 * names are listed in the COPYRIGHT file, which is included
 * within the source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "burrspec.h"

#include "voxel.h"

std::string burrSpec(const voxel_c & v) {

  unsigned int lo[3] = { v.getX(), v.getY(), v.getZ() };
  unsigned int hi[3] = { 0, 0, 0 };
  bool any = false;
  for (unsigned int z = 0; z < v.getZ(); z++)
    for (unsigned int y = 0; y < v.getY(); y++)
      for (unsigned int x = 0; x < v.getX(); x++)
        if (!v.isEmpty(x, y, z)) {
          const unsigned int c[3] = { x, y, z };
          for (int i = 0; i < 3; i++) {
            if (c[i] < lo[i]) lo[i] = c[i];
            if (c[i] > hi[i]) hi[i] = c[i];
          }
          any = true;
        }

  std::string spec = "[";

  if (any)
    for (unsigned int z = lo[2]; z <= hi[2]; z++) {
      if (z > lo[2]) spec += ", ";
      spec += '"';
      for (unsigned int y = lo[1]; y <= hi[1]; y++) {
        if (y > lo[1]) spec += '|';
        for (unsigned int x = lo[0]; x <= hi[0]; x++)
          spec += v.isFilled(x, y, z) ? 'x' : v.isVariable(x, y, z) ? 'v' : '.';
      }
      spec += '"';
    }
  spec += ']';

  return spec;
}
