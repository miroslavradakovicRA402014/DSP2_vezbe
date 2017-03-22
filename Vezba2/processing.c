/*
 * processing.c
 *
 *  Created on: 29.02.2016.
 *      Author: Dejan Bokan (dejan.bokan@rt-rk.com)
 */
#include "tistdtypes.h"

//Int16 input_fil[SIGNAL2_LENGTH/M_FACT];
//Int16 output_fil[SIGNAL2_LENGTH*L_FACT];

void downsample(Int16 *input, Int16 *output, int M, int N)
{
	/* your code here... */
    int i;

    for (i = 0; i < N/M; i++)
    {
       *(output + i) = *(input + M*i);
    }


}

/*
void decimate(Int16 *input, Int16 *output, int M, int N)
{

    int i;

    for (i = 0 ; i < N ; i++)
    {
	*(input_fil + i) = fir_basic(*(input + i),lp_filter,history, N_COEFF);
    }

    downsample(input_fil,output,M,N);

}
*/
void upsample(Int16 *input, Int16 *output, int L, int N)
{
	/* your code here... */
    int i;

    for (i = 0; i < L*N; i++)
    {
       *(output + i) = 0;
    }
  
    for (i = 0; i < N; i++)
    {
       *(output + L*i) = *(input + i);
    }


}
/*
void interpolate(Int16 *input, Int16 *output, int L, int N)
{
    upsample(input,output,L,N);

    int i;
    for (i = 0; i < L*N; i++)
    {
      *(output + i) = fir_basic(*(output + i),lp_filter,history, N_COEFF);
    }
}


void resample(Int16 *input, Int16 *output, int L, int M, int N)
{

    upsample(input,output_fil,L,N);

    int i ;

    for (i = 0; i < L*N; i++)
    {
      *(output_fil + i) = fir_basic(*(output_fil + i),lp_filter,history, N_COEFF);
    }

    downsample(output_fil,output,M,L*N);

}
*/


