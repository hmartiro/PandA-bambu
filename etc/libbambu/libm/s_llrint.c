/**
 * Porting of the libm library to the PandA framework
 * starting from the original FDLIBM 5.3 (Freely Distributable LIBM) developed by SUN
 * plus the newlib version 1.19 from RedHat and plus uClibc version 0.9.32.1 developed by Erik Andersen.
 * The author of this port is Fabrizio Ferrandi from Politecnico di Milano.
 * The porting fall under the LGPL v2.1, see the files COPYING.LIB and COPYING.LIBM_PANDA in this directory.
 * Date: September, 11 2013.
 */
/* lrint adapted to be llrint for Newlib, 2009 by Craig Howland.  */
/* @(#)s_lrint.c 5.1 93/09/24 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 * llrint(x)
 * Return x rounded to integral value according to the prevailing
 * rounding mode.
 * Method:
 *	Using floating addition.
 * Exception:
 *	Inexact flag raised if x not equal to llrint(x).
 */

#include "math_private.h"

/* Adding a double, x, to 2^52 will cause the result to be rounded based on
   the fractional part of x, according to the implementation's current rounding
   mode.  2^52 is the smallest double that can be represented using all 52 significant
   digits. */
static const double TWO52[2] = {
    4.50359962737049600000e+15,  /* 0x43300000, 0x00000000 */
    -4.50359962737049600000e+15, /* 0xC3300000, 0x00000000 */
};

#define SAFE_RIGHT_SHIFT(op, amt) (((amt) < 8 * sizeof(op)) ? ((op) >> (amt)) : 0)

long long int llrint(double x)
{
   int i0, j0, sx;
   unsigned int i1;
   double t;
   double w;
   long long int result;

   i0 = GET_HI(x);
   i1 = GET_LO(x);

   /* Extract sign bit. */
   sx = (i0 >> 31) & 1;

   /* Extract exponent field. */
   j0 = ((i0 & 0x7ff00000) >> 20) - 1023;
   /* j0 in [-1023,1024] */

   if(j0 < 20)
   {
      /* j0 in [-1023,19] */
      if(j0 < -1)
         return 0;
      else
      {
         /* j0 in [0,19] */
         /* shift amt in [0,19] */
         w = TWO52[sx] + x;
         t = w - TWO52[sx];
         i0 = GET_HI(t);
         /* Detect the all-zeros representation of plus and
            minus zero, which fails the calculation below. */
         if((i0 & ~((int)1 << 31)) == 0)
            return 0;
         /* After round:  j0 in [0,20] */
         j0 = ((i0 & 0x7ff00000) >> 20) - 1023;
         i0 &= 0x000fffff;
         i0 |= 0x00100000;
         /* shift amt in [20,0] */
         result = i0 >> (20 - j0);
      }
   }
   else if(j0 < (int)(8 * sizeof(long long int)) - 1)
   {
      /* 64bit return: j0 in [20,62] */
      if(j0 >= 52)
         /* 64bit return: j0 in [52,62] */
         /* 64bit return: left shift amt in [32,42] */
         result = ((long long int)((i0 & 0x000fffff) | 0x0010000) << (j0 - 20)) |
                  /* 64bit return: right shift amt in [0,10] */
                  (i1 << (j0 - 52));
      else
      {
         /* 64bit return: j0 in [20,51] */
         w = TWO52[sx] + x;
         t = w - TWO52[sx];
         i0 = GET_HI(t);
         i1 = GET_LO(t);
         j0 = ((i0 & 0x7ff00000) >> 20) - 1023;
         i0 &= 0x000fffff;
         i0 |= 0x00100000;
         /* After round:
          * 64bit return: j0 in [20,52] */
         /* 64bit return: left shift amt in [0,32] */
         /* ***64bit return: right shift amt in [32,0] */
         result = ((long long int)i0 << (j0 - 20)) | SAFE_RIGHT_SHIFT(i1, (52 - j0));
      }
   }
   else
   {
      return (long long int)x;
   }

   return sx ? -result : result;
}
