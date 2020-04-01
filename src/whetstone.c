#include "whetstone.h"

int whetstone (whetint loopcount)
{
    /* The array indices in the algol program (from paper) start from 1,
    * to start at element 0 for C, would require many changes,
    * including decrementing the variable indices by 1.
    * Instead, the array E1[] is declared 1 element larger in C */
    whetreal    e1[5];
    whetreal    x1, x2, x3, x4, x, y, z, t, t1, t2;
    whetint     i, j, k, l, n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11;

    // initialise constants

    t   = 0.499975;
    t1  = 0.50025;
    t2  = 2.0;

    /* two of the modules, numbers 1 and 10, were eliminated by the restriction to positive frequencies
     * The remaining 8 modules gave a weighted root mean square deviation over the 25 instructions of
     * 15% which was considered satisfactory
     * 
     * The execution frequency of each module is proportional to the input value of loopcount variable
     * and the scaling factors are such that a value of loopcount = 10 gives a total weight to the modules 
     * corresponding to one million Whetstone instructions */

    n1  = 0;
    n2  = 12 * loopcount;
    n3  = 14 * loopcount;
    n4  = 345 * loopcount;
    n5  = 0;
    n6  = 210 * loopcount;
    n7  = 32 * loopcount;
    n8  = 899 * loopcount;
    n9  = 616 * loopcount;
    n10 = 0;
    n11 = 93 * loopcount;

    // module 1: simple identifiers (does not run)

    x1 = 1.0;
    x2 = x3 = x4 = -1.0;

    for (i = 1; i <= n1; i++)
    {
        x1 = (x1 + x2 + x3 - x4) * t;
        x2 = (x1 + x2 - x3 + x4) * t;
        x3 = (x1 - x2 + x3 + x4) * t;
        x4 = (-x1 + x2 + x3 + x4) * t;
    }

#ifdef DEBUG
    pout("Module 1", n1, n1, n1, x1, x2, x3, x4);
#endif

    // module 2: array elements

    e1[1] = 1.0;
    e1[2] = e1[3] = e1[4] = -1.0;

    for (i = 1; i <= n2; i++)
    {
        e1[1] = (e1[1] + e1[2] + e1[3] - e1[4]) * t;
        e1[2] = (e1[1] + e1[2] - e1[3] + e1[4]) * t;
        e1[3] = (e1[1] - e1[2] + e1[3] + e1[4]) * t;
        e1[4] = (-e1[1] + e1[2] + e1[3] + e1[4]) * t;
    }

#ifdef DEBUG
    pout("Module 2", n2, n3, n2, e1[1], e1[2], e1[3], e1[4]);
#endif

    // module 3: array as parameter

    for (i = 1; i <= n3; i++)
    {
        pa(e1, t, t2);
    }
    
#ifdef DEBUG
    pout("Module 3", n3, n2, n2, e1[1], e1[2], e1[3], e1[4]);
#endif

    // module 4: conditional jumps

    j = 1;

    for (i = 1; i <= n4; i++)
    {
        if (j == 1)
            j = 2;
        else
            j = 3;

        if (j > 2)
            j = 0;
        else
            j = 1;

        if (j < 1)
            j = 1;
        else
            j = 0;
    }

#ifdef DEBUG
    pout("Module 4", n4, j, j, x1, x2, x3, x4);
#endif

    // module 5: omitted


    // module 6: integer arithmetic

    j = 1;
    k = 2;
    l = 3;

    for (i = 1; i <= n6; i++)
    {
        j = j * (k - j) * (l - k);
        k = l * k - (l - j) * k;
        l = (l - k) * (k + j);

        e1[(l < 0? -l: l) % 5] = j + k + l;

        e1[(k < 0? -k: k) % 5] = j * k * l;
    }

#ifdef DEBUG
    pout("Module 6", n6, j, k, e1[1], e1[2], e1[3], e1[4]);
#endif

    // module 7: trig. functions

    x = y = 0.5;

    for (i = 1; i <= n7; i++)
    {
        x = t * atan(t2 * sin(x) * cos(x) /
        (cos(x + y) + cos(x - y) - 1.0));

        y = t * atan(t2 * sin(y) * cos(y) /
        (cos(x + y) + cos(x - y) - 1.0));
    }

#ifdef DEBUG
    pout("Module 7", n7, j, k, x, x, y, y);
#endif

    // module 8: procedure calls

    x = y = z = 1.0;

    for (i = 1; i <= n8; i++)
    {
        p3(x, y, &z, t, t2);
    }

#ifdef DEBUG
    pout("Module 8", n8, j, k, x, y, z, z);
#endif

    // module 9: array references

    j = 1;
    k = 2;
    l = 3;

    e1[1] = 1.0;
    e1[2] = 2.0;
    e1[3] = 3.0;

    for (i = 1; i <= n9; i++)
    {
        p0(e1, j, k, l);
    }

#ifdef DEBUG
    pout("Module 9", n9, j, k, e1[1], e1[2], e1[3], e1[4]);
#endif

    // module 10: integer arithmetic

    j = 2;
    k = 3;

    for (i = 1; i <= n10; i++)
    {
        j = j + k;
        k = j + k;
        j = k - j;
        k = k - j - j;
    }

#ifdef DEBUG
    pout("Module 10", n10, j, k, x1, x2, x3, x4);
#endif

    // module 11: standard functions

    x = 0.75;

    for (i = 1; i <= n11; i++)
    {
        x = sqrt(exp(log(x) / t1));
    }
    
#ifdef DEBUG
    pout("Module 11", n11, j, k, x, x, x, x);
#endif

    return 0;
}

// used in module 3: array as parameter
void pa (whetreal e[], whetreal t, whetreal t2)
{
    int j = 0;

    lab:
        e[1] = (e[1] + e[2] + e[3] - e[4]) * t;
        e[2] = (e[1] + e[2] - e[3] + e[4]) * t;
        e[3] = (e[1] - e[2] + e[3] + e[4]) * t;
        e[4] = (-e[1] + e[2] + e[3] + e[4]) / t2;
    
        j += 1;

        if (j < 6)
            goto lab;
}

// used in module 9: array references
void p0 (whetreal e1[], whetint j, whetint k, whetint l)
{
    e1[j] = e1[k];
    e1[k] = e1[l];
    e1[l] = e1[j];
}

// used in module 8: procedure calls
void p3 (whetreal x, whetreal y, whetreal *z, whetreal t, whetreal t2)
{
    whetreal x1, y1;

	x1 = x;
	y1 = y;
	x1 = t * (x1 + y1);
	y1 = t * (x1 + y1);
	*z  = (x1 + y1) / t2;
}

void pout (const char * module, whetint n, whetint j, whetint k, whetreal x1, whetreal x2, whetreal x3, whetreal x4)
{
    printf("%s, n=%" PRId64 " j=%" PRId64 " k=%" PRId64 " x1=%.3lf x2=%.3lf x3=%.3lf x4=%.3lf\n", module, n, j, k, x1, x2, x3, x4);
}
