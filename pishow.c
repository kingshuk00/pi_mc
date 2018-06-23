/*
  Copyright <suckmycode@gmail.com>.
  This file is part of Monte-Carlo example to find value of Pi.
  This is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  EasyVectorLib is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with EasyVectorLib. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define GET_A_DOUBLE() 9.3132257504915938e-10*((double)rand_r(&seed))-1.0
#define DBL_LEQ(a,b) (a-b<DBL_EPSILON)?1:(a<b)

int main(int argc, char *argv[])
{
   long unsigned int imax= 0;
   if (argc< 2) {
      printf("Need argument as \"prog #max-iteration\"\n");
      exit(1);
   } else {
      imax= (long unsigned int) atol(argv[1]);
   }

   long unsigned int yes= 0;
   _Thread_local static unsigned int seed;
   seed= time(NULL);
#pragma omp parallel for reduction(+:yes)
   for(long unsigned int i= 0; i< imax; ++i) {
      const register double x= GET_A_DOUBLE();
      const register double y= GET_A_DOUBLE();
      const register double z= x* x+ y* y;
      if (DBL_LEQ(z,1.0)) {
         ++yes;
      }
   }

   printf("%lu %.6e\n", imax, ((double) yes)/ ((double) imax)* 4.0);

   return 0;
}
