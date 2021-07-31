#include "config.h" 
#include "bits.h" 
#include "lcd.h" 
#include "keypad.h"
#include "pwm.h"
#include "timer.h"
#define PORTD (*(volatile unsigned char*)0xF83) 
#define TRISD (*(volatile unsigned char*)0xF95) 



void EscolherJogo(void) {
    
    int tecla = 16, i;
    unsigned char coluna = 0, linha = 0;
    char l, k;
    char msg[11] = "1--Memoria";
    lcdInit();
    lcdCommand(0x80);
    for (l = 0; l < 10; l++) {
        lcdData(msg[l]);
    }
    lcdCommand(0xC0);
    char ms[10] = "2--Ingles";
    for (k = 0; k < 9; k++) {
        lcdData(ms[k]);
    }
    lcdCommand(0x90);
    char msy[14] = "3--Matematica";
    for (k = 0; k < 13; k++) {
        lcdData(msy[k]);
    }

    for (;;) {
        
        kpInit();
        kpDebounce();
        if (kpRead() != tecla) {
            tecla = kpRead();
            if (bitTst(tecla, 0)) {

                JogoMemoria();
            }

            if (bitTst(tecla, 4)) {

                AprenderIngles();
            }
            if (bitTst(tecla, 8)) {

                Matematica();
            }

        }
    }
}
