#include "termometer.h"

#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)

#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)

unsigned int temp;
volatile float temperatureDegC;

void termometro(void){
    int firstTime = 0;
    REFCTL0 &= ~REFMSTR;
    ADC12CTL0 = ADC12SHT0_8 + ADC12REFON + ADC12ON;
    ADC12CTL1 = ADC12SHP;
    ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;
    __delay_cycles(100);
    ADC12CTL0 |= ADC12ENC;

    while(1){
        ADC12CTL0 &= ~ADC12SC;
        ADC12CTL0 |= ADC12SC;                   //o rising edge de ADC12SC inicia o sampling
        while ( (ADC12IFG&ADC12IFG0) == 0);
        temp = ADC12MEM0;
        // Temperatura em celsius
        temperatureDegC = (float)(((long)temp - CALADC12_15V_30C) * (85 - 30)) / (CALADC12_15V_85C - CALADC12_15V_30C) + 30.0f;
        if(firstTime == 0){
            printResult(temperatureDegC);
            firstTime = 1;
        }
        volatile int aux = (temperatureDegC - ((int) temperatureDegC)) * 10000;
        volatile short randomBit = BIT0 & aux;
        if((P2IN & 0x02)==0)
            return;
    }
}
