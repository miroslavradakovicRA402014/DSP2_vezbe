//////////////////////////////////////////////////////////////////////////////
// *
// * VE�BA 2 � Banke filtara
// * Godina: 2016
// *
// * Zadatak: Banke filtara
// * Autor:
// *
// *
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "ezdsp5535_i2s.h"
#include "ezdsp5535_sar.h"
#include "fir.h"
#include "filter_coeff.h"
#include "processing.h"

/* Frekvencija odabiranja */
#define SAMPLE_RATE 8000L
#define GAIN 0

/* Niz za smestanje ulaznih i izlaznih odbiraka */
#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(InputBufferMono,4)
Int16 InputBufferMono[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferMono,4)
Int16 OutputBufferMono[AUDIO_IO_SIZE];

Int16 history0[N_COEFF];
Int16 history1[N_COEFF];

Int16 out1B1[AUDIO_IO_SIZE/2];
Int16 out2B1[AUDIO_IO_SIZE/2];

Int16 out1B2[AUDIO_IO_SIZE/4];
Int16 out2B2[AUDIO_IO_SIZE/4];

Int16 out1B3[AUDIO_IO_SIZE/4];
Int16 out2B3[AUDIO_IO_SIZE/4];

Int16 out1B4[AUDIO_IO_SIZE/2];

Int16 out1B5[AUDIO_IO_SIZE/2];


Int16 out1_s[AUDIO_IO_SIZE];
Int16 out2_s[AUDIO_IO_SIZE];

Int16 out1[AUDIO_IO_SIZE];
Int16 out2[AUDIO_IO_SIZE];






void analise(Int16 *input,Int16 *output1,Int16 *output2,Int16 *history_h0,Int16 *history_h1,int N)
{
   int i;

   for (i = 0; i < N; i++)
   {
     out1[i] = fir_basic(input[i],H0,history_h0,N_COEFF);
     out2[i] = fir_basic(input[i],H1,history_h1,N_COEFF);
   }

   downsample(out1,output1,2,N);
   downsample(out2,output2,2,N);

}

void sintetise(Int16 *input1,Int16 *input2,Int16 *output,Int16 *history_h0,Int16 *history_h1,int N)
{
   int i;

   upsample(input1,out1,2,N);
   upsample(input2,out2,2,N);


   for (i = 0; i < N; i++)
   {
     out1_s[i] = fir_basic(out1_s[i],H0,history_h0,N_COEFF);
     out2_s[i] = fir_basic(out2_s[i],H1,history_h1,N_COEFF);
   }

   for (i = 0; i < 2*N; i++)
   {
      output[i] = out1_s[i] + out2_s[i];
   }
}


void stereoToMono(Int16* inputL, Int16* inputR, Int16* output, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		output[i] = (inputL[i]>>1) + (inputR[i]>>1);
	}
}

void main( void )
{
    int state=0;

    /* Inicijalizaija razvojne ploce */
    EZDSP5535_init( );

    /* Inicijalizacija kontrolera za ocitavanje vrednosti dugmeta*/
    EZDSP5535_SAR_init();

	printf("\n DTMF Predajnik\n");

    /* Inicijalizacija veze sa AIC3204 kodekom (AD/DA) */
    aic3204_hardware_init();

    /* Inicijalizacija AIC3204 kodeka */
	aic3204_init();

    aic3204_dma_init();

    /* Postavljanje vrednosti frekvencije odabiranja i pojacanja na kodeku */
    set_sampling_frequency_and_gain(SAMPLE_RATE, GAIN);


 	//while(1)
	//{

 		/* Promeniti stanje na osnovu pritisnutog tastera */
 		/* Za dobavljanje vrednosti tastera koristiti funkciju EZDSP5535_SAR_getKey */
 		/* Your code here */

 		aic3204_read_block(InputBufferL, InputBufferR);
 		stereoToMono(InputBufferL, InputBufferR, InputBufferMono, AUDIO_IO_SIZE);

 		analise(InputBufferMono,out1B1,out2B1,history0,history1,AUDIO_IO_SIZE);
 		analise(out1B1,out1B2,out2B2,history0,history1,AUDIO_IO_SIZE/2);
 		analise(out2B1,out1B3,out2B3,history0,history1,AUDIO_IO_SIZE/2);

 		sintetise(out1B2,out2B2,out1B4,history0,history1,AUDIO_IO_SIZE/4);
 		sintetise(out1B3,out2B3,out1B5,history0,history1,AUDIO_IO_SIZE/4);
 		sintetise(out1B4,out1B5,OutputBufferMono,history0,history1,AUDIO_IO_SIZE/2);




 		/* Izvrsiti analizu signala InputBufferMono upotrebom filter banke 4. reda */
 		/* Your code here */

 		/* U zavisnosti od trenutnog stanja nulirati odredjene komponente signala */
 		/* Stanje 0 - nema obrade (komponente signala na ulazu nalaze se i na izlazu) */
 		/* Stanje 1 - samo frekvencijske komponente iz prvog podopsega */
 		/* Stanje 2 - samo frekvencijske komponente iz drugog podopsega */
 		/* Stanje 3 - samo frekvencijske komponente iz treceg podopsega */
 		/* Stanje 4 - samo frekvencijske komponente iz cetvrtog podopsega */
 		/* Your code here */

 		/* Izvrsiti sintezu signala i rezultat smestiti u OutputBufferMono */
 		/* Your code here */

		aic3204_write_block(OutputBufferMono, OutputBufferMono);
	//}


	/* Prekid veze sa AIC3204 kodekom */
    aic3204_disable();

    printf( "\n***Kraj programa***\n" );
	SW_BREAKPOINT;
}


