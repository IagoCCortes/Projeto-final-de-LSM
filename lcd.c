#include "lcd.h"
#include <msp430.h>

#define PCF 0x27    //Endereço PCF8574T

void initialize(){
    delay(150);

    PCF_write(0x38);
    delay(150);
    PCF_write(0x3c);
    delay(150);
    PCF_write(0x38);

    delay(150);
    PCF_write(0x38);
    delay(150);
    PCF_write(0x3c);
    delay(150);
    PCF_write(0x38);

    delay(150);
    PCF_write(0x38);
    delay(150);
    PCF_write(0x3c);
    delay(150);
    PCF_write(0x38);

    delay(150);
    PCF_write(0x28);
    delay(150);
    PCF_write(0x2c);
    delay(150);
    PCF_write(0x28);

    PCF_write(0x28);
    delay(150);
    PCF_write(0x2c);
    delay(150);
    PCF_write(0x28);
    delay(150);
    PCF_write(0x88);
    delay(150);
    PCF_write(0x8c);
    delay(150);
    PCF_write(0x88);

    PCF_write(0x08);
    delay(150);
    PCF_write(0x0c);
    delay(150);
    PCF_write(0x08);
    delay(150);
    PCF_write(0xc8);
    delay(150);
    PCF_write(0xcc);
    delay(150);
    PCF_write(0xc8);

    delay(150);
    PCF_write(0x08);
    delay(150);
    PCF_write(0x0c);
    delay(150);
    PCF_write(0x08);
    delay(150);
    PCF_write(0x18);
    delay(150);
    PCF_write(0x1c);
    delay(150);
    PCF_write(0x18);

    delay(150);
    PCF_write(0x08);
    delay(150);
    PCF_write(0x0c);
    delay(150);
    PCF_write(0x08);
    delay(150);
    PCF_write(0x68);
    delay(150);
    PCF_write(0x6c);
    delay(150);
    PCF_write(0x68);
}

void write(volatile short dado){
    short x = (dado & 0xf0) + 15;
    short y = dado & 0x0f;
    y <<= 4;
    y += 15;
    short charFLow = x & 0xf9;
    int charFHigh = x & 0xfd;
    int charSLow = y & 0xf9;
    int charSHigh = y & 0xfd;
    delay(150);
    PCF_write(charFLow);
    delay(150);
    PCF_write(charFHigh);
    delay(150);
    PCF_write(charFLow);
    delay(150);
    PCF_write(charSLow);
    delay(150);
    PCF_write(charSHigh);
    delay(150);
    PCF_write(charSLow);
    delay(150);
}

// Escrever dado na porta
//essa função segue todo o processo de transmissão de dados master-> slave
//e é usada para controlar e passar dados para o lcd
void PCF_write(short dado){
    UCB0I2CSA = PCF;                            //Endereço do Escravo

    UCB0CTL1 |= UCTR    |                       //Mestre transmissor
                UCTXSTT;                        //Gerar START e envia endereço

    while ( (UCB0IFG & UCTXIFG) == 0);          //Esperar TXIFG (completar transm.)

    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG){   //NACK?
        while(1);                               //Se NACK, prender
    }

    UCB0TXBUF = dado;                           //Dado a ser escrito

    while ( (UCB0IFG & UCTXIFG) == 0);          //Esperar Transmitir

    UCB0CTL1 |= UCTXSTP;                        //Gerar STOP

    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);   //Esperar STOP

    delay(50);                                  //Atraso p/ escravo perceber stop
}

// Configurar Pinos I2C - UCSB0
// P3.0 --> SDA
// P3.1 --> SCL
//nessa função os pinos e os registradores utilizados na comunicação i2c são configurados
void config_I2C(void){
    P3SEL |=  BIT0;    // Usar módulo dedicado
    P3REN |=  BIT0;    // Habilitar resistor
    P3OUT |=  BIT0;    // Pull-up

    P3SEL |=  BIT1;    // Usar módulo dedicado
    P3REN |=  BIT1;    // Habilitar resistor
    P3OUT |=  BIT1;    // Pull-up

    UCB0CTL1 |= UCSWRST;    // UCSI B0 em reset

    UCB0CTL0 = UCSYNC |     //Síncrono
               UCMODE_3 |   //Modo I2C
               UCMST;       //Mestre

    UCB0BRW = 10;       //100 kbps
    UCB0CTL1 = UCSSEL_2;   //SMCLK e remove reset
}

void delay(long limite){
    volatile long cont=0;
    while (cont++ < limite) ;
}

void operatorPosition(){
    delay(150);
    PCF_write(0xc8);
    delay(150);
    PCF_write(0xcc);
    delay(150);
    PCF_write(0xc8);
    delay(150);
    PCF_write(0x08);
    delay(150);
    PCF_write(0x0c);
    delay(150);
    PCF_write(0x08);
    delay(150);
}

void clrScreen(){
    delay(150);
    PCF_write(0x08);
    delay(150);
    PCF_write(0x0c);
    delay(150);
    PCF_write(0x08);
    delay(150);
    PCF_write(0x18);
    delay(150);
    PCF_write(0x1c);
    delay(150);
    PCF_write(0x18);
    delay(150);
}

void writeConv(volatile int conv){
    switch (conv){
    case 0:
        write(0x30);
        break;
    case 1:
        write(0x31);
        break;
    case 2:
        write(0x32);
        break;
    case 3:
        write(0x33);
        break;
    case 4:
        write(0x34);
        break;
    case 5:
        write(0x35);
        break;
    case 6:
        write(0x36);
        break;
    case 7:
        write(0x37);
        break;
    case 8:
        write(0x38);
        break;
    case 9:
        write(0x39);
        break;
    case 10:
        write(0x2b);
        break;
    case 11:
        write(0x2d);
        break;
    case 12:
        write(0x58);
        break;
    case 15:
        write(0x2f);
        break;
    }
}

void printResult(float result){
    if(result < 0){
        result *= -1;
        write(0x2d);
    }
    volatile long intResult = result;
    result -= (float) intResult;
    result *= 10000;
    volatile long decResult = (int) result;
    volatile long n = intResult;
    volatile int digs = 0;
    while(n != 0){
        n /= 10;
        digs++;
    }
    makingItPossible(digs, intResult);
    write(0x2e);
    makingItPossible(4, decResult);
}

void makingItPossible(volatile int digs, volatile long result){
    volatile int i, j=digs-1;
    volatile long step1 = 0, l = 10;
    volatile float step=0;
    for(i=0;i<digs-1;i++)
        l*=10;
    for(i=0;i<digs;i++){
        step = (float) result / l;
        step1 = (long)((step - ((long) step)) * 10);
        j--;
        l /= 10;
        writeConv(step1);
    }
}

void printMenu(){ //1- Calculadora  2- Termometro
    //1- Calculadora
    write(0x31);
    write(0x2d);
    write(0x20);
    write(0x43);
    write(0x41);
    write(0x4c);
    write(0x43);
    write(0x55);
    write(0x4c);
    write(0x41);
    write(0x44);
    write(0x4f);
    write(0x52);
    write(0x41);

    operatorPosition();

    //2- Termometro
    write(0x32);
    write(0x2d);
    write(0x20);
    write(0x54);
    write(0x45);
    write(0x52);
    write(0x4d);
    write(0x4f);
    write(0x4d);
    write(0x45);
    write(0x54);
    write(0x52);
    write(0x4f);
}
