#include <msp430.h>
#include "tecMat.h"
#include "lcd.h"

int choice = 2;

void configBt(){
    P1DIR &= ~BIT1;
    P1OUT |= BIT1;
    P1REN |= BIT1;
    P1IES |= BIT1;
    P1IE |= BIT1;
    P2DIR &= ~BIT1;
    P2REN |= BIT1;
    P2OUT |= BIT1;
    P2IES |= BIT1;
    P2IE |= BIT1;
    P1OUT &= ~BIT0;
    P1DIR |= BIT0;
    P4OUT &= ~BIT7;
    P4DIR |= BIT7;
}

void main(void){
    WDTCTL = WDTPW | WDTHOLD;
    configTecMat();
    config_I2C();
    initialize();
    configBt();
x:  printMenu();
    __enable_interrupt();
    __bis_SR_register(LPM3_bits + GIE);
    clrScreen();
    if(choice == 0){
        P4OUT |= BIT7;
        volatile int flag=0, tester=0, sig=0, flagfp=0, n=10, limop=5,fn=0;
        volatile long op1=0, op2=0;
        volatile float op1fp=0, op2fp=0, res=0;
        while(flag==0){
            tester=digitSel();
            if(((tester == 10)||(tester == 11)||(tester == 12)||(tester == 15)) && fn == 1){
                flag = 1;
                write(0x20);
                writeConv(tester);
            }
            else if(((tester == 10)||(tester == 11)||(tester == 12)||(tester == 15)) && fn == 0){
                continue;
            }
            else if(tester == 13)
                continue;
            else if(tester == 14 && flagfp == 1)
                continue;
            else if(tester == 14 && fn == 1 && limop != 0){
                write(0x2e);
                op1fp = (float) op1;
                flagfp = 1;
                limop--;
                continue;
            }else if(flagfp == 0 && limop != 0){
                op1 *= 10;
                op1 += tester;
                fn=1;
                limop--;
                writeConv(tester);
            }else if(flagfp == 1 && limop != 0){
                op1fp += (float) tester/n;
                n *=10;
                limop--;
                writeConv(tester);
            }
        }
        operatorPosition();
        if(op1fp == 0)
            op1fp = (float) op1;
        flag = 0;
        flagfp = 0;
        n = 10;
        sig = tester;
        fn=0;
        limop=5;
        while(flag==0){
            tester=digitSel();
            if((tester==10)||(tester==11)||(tester==12)||(tester==15))
                continue;
            else if(tester == 13 && fn == 1)
                flag = 1;
            else if(tester == 14 && flagfp == 1)
                continue;
            else if(tester == 14 && fn == 1 && limop != 0){
                write(0x2e);
                limop--;
                op2fp = (float) op2;
                flagfp = 1;
                continue;
            }else if(flagfp == 0 && limop != 0){
                op2 *= 10;
                op2 += tester;
                fn=1;
                limop--;
                writeConv(tester);
            }else if(flagfp == 1 && limop != 0){
                op2fp += (float) tester/n;
                n *=10;
                limop--;
                writeConv(tester);
            }
        }
        if(op2fp == 0)
                op2fp = (float) op2;
        clrScreen();
        if(sig == 10)
            res = op1fp + op2fp;
        if(sig == 11)
            res = op1fp - op2fp;
        if(sig == 12)
            res = op1fp * op2fp;
        if((sig == 15)&&(op2fp != 0))
            res= op1fp / op2fp;
        if(sig == 15 && op2fp == 0){
            write(0x45);
            write(0x52);
            write(0x52);
            write(0x4f);
            write(0x52);
            write(0x21);
        }else{
            printResult(res);
        }
        __bis_SR_register(LPM3_bits + GIE);
        P4OUT &= ~BIT7;
        clrScreen();
    }
    if(choice == 1){
        P1OUT |= BIT0;
        termometro();
        __bis_SR_register(LPM3_bits + GIE);
        P1OUT &= ~BIT0;
        clrScreen();
    }
    goto x;
}

#pragma vector = PORT1_VECTOR
__interrupt void p1 (void) {
    switch(__even_in_range(P1IV,0x10)){
        case 0x4:   choice = 0;
                    __bic_SR_register_on_exit (LPM3_bits);
                    break;
        default:    break;
    }
}

#pragma vector = PORT2_VECTOR
__interrupt void p2 (void) {
switch(__even_in_range(P2IV,0x10)){
        case 0x4:   choice = 1;
                    __bic_SR_register_on_exit (LPM3_bits);
                break;
        default: break;
    }
}
