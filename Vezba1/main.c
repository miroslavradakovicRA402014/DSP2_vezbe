//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// * Description:  Vezba 1 - Interpolacija i decimacija
// *
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *
//////////////////////////////////////////////////////////////////////////////

#include "tistdtypes.h"
#include <cstdio>
#include "ezdsp5535.h"
#include "math.h"
#include "signal.h"
#include "filter_coeff.h"
#include "processing.h"


/*
 *
 *  main( )
 *
 */

Int16 signal1_fil1[SIGNAL1_LENGTH/M_FACT];
Int16 signal1_fil2[SIGNAL1_LENGTH/M_FACT];

Int16 signal2_fil1[SIGNAL2_LENGTH*L_FACT];
Int16 signal2_fil2[SIGNAL2_LENGTH*L_FACT];

Int16 signal2_fil3[SIGNAL2_LENGTH*4/3];

void main( void )
{

      printf("\n Vezba 1 - Interpolacija i decimacija \n");
	
	/* Your code here */
      //downsample(signal1,signal1_fil1,M_FACT,SIGNAL1_LENGTH);
      //decimate(signal1,signal1_fil2,M_FACT,SIGNAL1_LENGTH);

      //upsample(signal2,signal2_fil1,L_FACT,SIGNAL2_LENGTH);
      //interpolate(signal2,signal2_fil2,L_FACT,SIGNAL2_LENGTH);

      resample(signal2,signal2_fil3,4,3,SIGNAL2_LENGTH);

      printf( "\n***Program has Terminated***\n" );
      SW_BREAKPOINT;
}

