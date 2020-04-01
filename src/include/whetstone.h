#ifndef WHETSTONE_H
#define WHETSTONE_H

/* Whetstone benchmark is a synthetic benchmark,
 * used for evaluating the performance of computers,
 * originally written in Algol 60 (see paper in docs directory),
 * performance is measured in Millions of Whetstone Instructions Per Second (MWIPS),
 * it primarily measures the floating-point arithmetic performance,
 * 
 * The workload on a machine was represented as a set of frequencies 
 * of execution of the 124 instructions of the Whetstone Code,
 * a set of 42 simple ALGOL 60 statements,
 * which in a suitable combination matched the execution statistics 
 * 
 * Link to the original paper by Curnow, H.J. and Wichman, B.A can be
 * found in the wikipedia article on Whetstone (benchmark) */

#include <stdio.h>
#include <math.h>
#include <stdint.h>     // For int64_t
#include <inttypes.h>   // For PRId64 (printing int64_t type number)

//#define DEBUG
#define whetint     int64_t // MWIPS score may vary if size varies on diferent platforms
#define whetreal    double  // 64 bits on cl and gcc compiler

// Main function
int whetstone (whetint loopcount);

// used in module 3: array as parameter
void pa (whetreal e[], whetreal t, whetreal t2);

// used in module 9: array references
void p0 (whetreal e1[], whetint j, whetint k, whetint l);

// used in module 8: procedure calls
void p3 (whetreal x, whetreal y, whetreal *z, whetreal t, whetreal t2);

void pout (const char * module, whetint n, whetint j, whetint k, whetreal x1, whetreal x2, whetreal x3, whetreal x4);

#endif