#include <msp430.h>
#include "tecMat.h"

#define L1 P2IN & BIT5
#define L2 P2IN & BIT4
#define L3 P1IN & BIT5
#define L4 P1IN & BIT4
#define C1 P2IN & BIT0
#define C2 P2IN & BIT2
#define C3 P2IN & BIT6
#define C4 P2IN & BIT3

//ATRIBUIÇÃO DE DIGITOS
int digit[4][4] = {{1, 2, 3, 10} , {4, 5, 6, 11} , {7, 8, 9, 12} , {14, 0, 15, 13}};


void debounce(){
    volatile int i;
    for(i=0x41;i<0xff;i++);
}

void configTecMat(){
    //INCIALIZAÇÃO PINOS PARA TECLADO
    P2DIR |= BIT0;
    P2DIR |= BIT2;
    P2DIR |= BIT6;
    P2DIR |= BIT3;

    P2DIR &= ~BIT4;
    P2DIR &= ~BIT5;
    P1DIR &= ~BIT5;
    P1DIR &= ~BIT4;

    P2REN |= BIT4;
    P2REN |= BIT5;
    P1REN |= BIT5;
    P1REN |= BIT4;

    P2OUT &= ~BIT4;
    P2OUT &= ~BIT5;
    P1OUT &= ~BIT5;
    P1OUT &= ~BIT4;
}


int turn = 0; //VARIÁVEL DE CONTROLE
              //ativa uma coluna por vez para leitura
int digitSel(){
  while(1){
    if(turn==4)
        turn=0;
    if(turn==0){
        P2OUT |= BIT0;      //C1
        P2OUT &= ~BIT2;     //C2
        P2OUT &= ~BIT6;     //C3
        P2OUT &= ~BIT3;     //C4
    }
    else if(turn==1){
        P2OUT &= ~BIT0;     //C1
        P2OUT |= BIT2;      //C2
        P2OUT &= ~BIT6;     //C3
        P2OUT &= ~BIT3;     //C4
    }
    else if(turn==2){
        P2OUT &= ~BIT0;     //C1
        P2OUT &= ~BIT2;     //C2
        P2OUT |= BIT6;      //C3
        P2OUT &= ~BIT3;     //C4
    }
    else if(turn==3){
        P2OUT &= ~BIT0;     //C1
        P2OUT &= ~BIT2;     //C2
        P2OUT &= ~BIT6;     //C3
        P2OUT |= BIT3;      //C4
        turn = -1;
    }

    //AS FUNÇÕES A SEGUIR RELACIONAM AS LINHAS E COLUNAS PARA
    //RETORNAR O VALOR CORRESPONDENTE

    //Linha 1
    if((L1) && (C1)){
        while((L1)!=0);
        debounce();
        return digit[0][0];
     }
     else if((L1) && (C2)){
         while((L1)!=0);
         debounce();
         return digit[0][1];
     }
     else if((L1)&&(C3)){
         while((L1)!=0);
         debounce();
         return digit[0][2];
     }
     else if((L1)&&(C4)){
         while((L1)!=0);
         debounce();
         return digit[0][3];
     }

     //Linha 2
     else if((L2)&&(C1)){
         while((L2)!=0);
         debounce();
         return digit[1][0];
     }
     else if((L2)&&(C2)){
         while((L2)!=0);
         debounce();
         return digit[1][1];
      }
      else if((L2)&&(C3)){
         while((L2)!=0);
         debounce();
         return digit[1][2];
      }
      else if((L2)&&(C4)){
         while((L2)!=0);
         debounce();
         return digit[1][3];
      }

      //Linha 3
      else if((L3)&&(C1)){
         while((L3)!=0);
         debounce();
         return digit[2][0];
      }
      else if((L3)&&(C2)){
        while((L3)!=0);
        debounce();
        return digit[2][1];
      }
      else if((L3)&&(C3)){
        while((L3)!=0);
        debounce();
        return digit[2][2];
      }
      else if((L3)&&(C4)){
        while((L3)!=0);
        debounce();
        return digit[2][3];
      }

      //Linha 4
      else if((L4)&&(C1)){
        while((L4)!=0);
        debounce();
        return digit[3][0];
      }
      else if((L4)&&(C2)){
        while((L4)!=0);
        debounce();
        return digit[3][1];
      }
      else if((L4)&&(C3)){
        while((L4)!=0);
        debounce();
        return digit[3][2];
      }
      else if((L4)&&(C4)){
        while((L4)!=0);
        debounce();
        return digit[3][3];
      }
      turn++;
  }
}


/*#include <msp430.h>
#include "tecMat.h"

int digit[4][4] = {{1, 2, 3, 10} , {4, 5, 6, 11} , {7, 8, 9, 12} , {14, 0, 15, 13}};

void debounce(){
    volatile int i;
    for(i=0x41;i<0xff;i++);
}

void configTecMat(){
    P1DIR |= BIT3;
    P1DIR |= BIT4;
    P1DIR |= BIT5;
    P1DIR |= BIT6;
    P2DIR &= ~BIT4;
    P2DIR &= ~BIT5;
    P2DIR &= ~BIT6;
    P2DIR &= ~BIT7;
    P2REN |= BIT4;
    P2REN |= BIT5;
    P2REN |= BIT6;
    P2REN |= BIT7;
    P2OUT &= ~BIT4;
    P2OUT &= ~BIT5;
    P2OUT &= ~BIT6;
    P2OUT &= ~BIT7;
}

int turn=0;
int digitSel(){
  while(1){
    if(turn==4)
        turn=0;
    if(turn==0){
        P1OUT |= BIT3;
        P1OUT &= ~BIT4;
        P1OUT &= ~BIT5;
        P1OUT &= ~BIT6;
    }
    else if(turn==1){
        P1OUT &= ~BIT3;
        P1OUT |= BIT4;
        P1OUT &= ~BIT5;
        P1OUT &= ~BIT6;
    }
    else if(turn==2){
        P1OUT &= ~BIT3;
        P1OUT &= ~BIT4;
        P1OUT |= BIT5;
        P1OUT &= ~BIT6;
    }
    else if(turn==3){
        P1OUT &= ~BIT3;
        P1OUT &= ~BIT4;
        P1OUT &= ~BIT5;
        P1OUT |= BIT6;
    }

    //Linha 1
    if((P2IN & BIT4) && (P1OUT & BIT3)){
        while((P2IN & BIT4)!=0);
        debounce();
        return digit[0][0];
     }
     else if((P2IN & BIT4) && (P1OUT & BIT4)){
         while((P2IN & BIT4)!=0);
         debounce();
         return digit[0][1];
     }
     else if((P2IN & BIT4)&&(P1OUT & BIT5)){
         while((P2IN & BIT4)!=0);
         debounce();
         return digit[0][2];
     }
     else if((P2IN & BIT4)&&(P1OUT & BIT6)){
         while((P2IN & BIT4)!=0);
         debounce();
         return digit[0][3];
     }

     //Linha 2
     else if((P2IN & BIT5)&&(P1OUT & BIT3)){
         while((P2IN & BIT5)!=0);
         debounce();
         return digit[1][0];
     }
     else if((P2IN & BIT5)&&(P1OUT & BIT4)){
         while((P2IN & BIT5)!=0);
         debounce();
         return digit[1][1];
      }
      else if((P2IN & BIT5)&&(P1OUT & BIT5)){
         while((P2IN & BIT5)!=0);
         debounce();
         return digit[1][2];
      }
      else if((P2IN & BIT5)&&(P1OUT & BIT6)){
         while((P2IN & BIT5)!=0);
         debounce();
         return digit[1][3];
      }

      //Linha 3
      else if((P2IN & BIT6)&&(P1OUT & BIT3)){
         while((P2IN & BIT6)!=0);
         debounce();
         return digit[2][0];
      }
      else if((P2IN & BIT6)&&(P1OUT & BIT4)){
        while((P2IN & BIT6)!=0);
        debounce();
        return digit[2][1];
      }
      else if((P2IN & BIT6)&&(P1OUT & BIT5)){
        while((P2IN & BIT6)!=0);
        debounce();
        return digit[2][2];
      }
      else if((P2IN & BIT6)&&(P1OUT & BIT6)){
        while((P2IN & BIT6)!=0);
        debounce();
        return digit[2][3];
      }

      //Linha 4
      else if((P2IN & BIT7)&&(P1OUT & BIT3)){
        while((P2IN & BIT7)!=0);
        debounce();
        return digit[3][0];
      }
      else if((P2IN & BIT7)&&(P1OUT & BIT4)){
        while((P2IN & BIT7)!=0);
        debounce();
        return digit[3][1];
      }
      else if((P2IN & BIT7)&&(P1OUT & BIT5)){
        while((P2IN & BIT7)!=0);
        debounce();
        return digit[3][2];
      }
      else if((P2IN & BIT7)&&(P1OUT & BIT6)){
        while((P2IN & BIT7)!=0);
        debounce();
        return digit[3][3];
      }
      turn++;
  }
}
*/
