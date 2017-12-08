#ifndef LCD_H_
#define LCD_H_

void config_I2C(void);
int  PCF_read(void);
void PCF_write(short dado);
void delay(long limite);
void initialize();
void write(volatile short dado);
void operatorPosition();
void clrScreen();
void writeConv(volatile int conv);
void printResult(float result);
void makingItPossible(volatile int digs, volatile long result);
void printMenu();

#endif /* LCD_H_ */
