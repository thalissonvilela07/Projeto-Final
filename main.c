
#include "config.h" 
#include "bits.h" 
#include "lcd.h" 
#include "keypad.h"
#include "pwm.h"
#include "timer.h"

#define PORTD (*(volatile unsigned char*)0xF83) 
#define TRISD (*(volatile unsigned char*)0xF95) 

//projeto final ECOP04
//Thalisson Vilela Carvalho  2017013320
//Jogo interativo para crianças

void delayms(unsigned int y) { //função para passar tempo
    unsigned int i;
    for (i = 0; i < y; i++) {
        volatile unsigned char j, k;
        for (j = 0; j < 41; j++) {
            for (k = 0; k < 3; k++);
        }
    }
}

void Reseta(void) {
    char i, k;
    char msg[17] = "Precione o Botao";
    lcdInit();
    for (i = 0; i < 16; i++) {
        lcdData(msg[i]);
    }
    lcdCommand(0xC5);
    char ms[6] = "Reset";
    for (k = 0; k < 5; k++) {
        lcdData(ms[k]);
    }
    lcdCommand(0x91);
    char msw[15] = "Para Recomecar";
    for (k = 0; k < 14; k++) {
        lcdData(msw[k]);
    }
}

void LedsVitoria(void) {
    TRISD = 0x00;
    PORTD = 0x00;

    PORTD = 0b00000000;
    delayms(250);
    PORTD = 0b11111111;
    delayms(250);
    PORTD = 0b00000000;
    delayms(250);
    PORTD = 0b11111111;
    delayms(250);
    PORTD = 0b00000000;
    delayms(250);
    PORTD = 0b11111111;
    delayms(250);
    PORTD = 0b00000000;
    delayms(250);
    PORTD = 0b11111111;
    delayms(250);
}

void LedsDerrota(void) {
    TRISD = 0x00;
    PORTD = 0x00;

    PORTD = 0b00000000;
    delayms(250);
    PORTD = 0b00000001;
    delayms(250);
    PORTD = 0b00000011;
    delayms(250);
    PORTD = 0b00000111;
    delayms(250);
    PORTD = 0b00001111;
    delayms(250);
    PORTD = 0b00011111;
    delayms(250);
    PORTD = 0b00111111;
    delayms(250);
    PORTD = 0b01111111;
    delayms(250);
    PORTD = 0b11111111;
    delayms(250);
}

void VitoriaCoolerERele(void) {
    pwmInit();
    pwmSet(64);
    delayms(2600);
    pwmSet(0);

}

void BemVindo(void) {
    char i, k;
    char msg[15] = "Ola, Bem Vindo";
    lcdInit();
    lcdCommand(0x81);
    for (i = 0; i < 14; i++) {
        lcdData(msg[i]);
    }
    lcdCommand(0xC1);
    char ms[15] = "Vamos Comecar?";
    for (k = 0; k < 14; k++) {
        lcdData(ms[k]);
    }
}

void Entrada(void) {
    char i, k;
    char msg[11] = "Qual Jogo";
    lcdInit();
    lcdCommand(0x81);
    for (i = 0; i < 10; i++) {
        lcdData(msg[i]);
    }
    lcdCommand(0xC4);
    char ms[12] = "Quer Jogar?";
    for (k = 0; k < 11; k++) {
        lcdData(ms[k]);
    }
}

void Acertou(void) {
    char i, k;
    char msg[9] = "Parabens";
    lcdInit();
    lcdCommand(0x84);
    for (i = 0; i < 8; i++) {
        lcdData(msg[i]);
    }
    lcdCommand(0xC2);
    char ms[13] = "Voce Acertou";
    for (k = 0; k < 12; k++) {
        lcdData(ms[k]);
    }
    LedsVitoria();
    VitoriaCoolerERele();
}

void Errou(void) {
    char i, k;
    char msg[6] = "Errou";
    lcdInit();
    lcdCommand(0x85);
    for (i = 0; i < 5; i++) {
        lcdData(msg[i]);
    }
    LedsDerrota();
}

void Memoria2(void) {
    char quadrados[48] = {


        0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000,
        0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000,
        0b00011, 0b00111, 0b01000, 0b11000, 0b11000, 0b01000, 0b01111, 0b00011,
        0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000,
        0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000,
        0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000,

    };
    char i, k, l, a;
    int tcl = 16;

    char msg[8] = "Quantos";
    lcdInit();
    lcdCommand(0x84);
    for (i = 0; i < 7; i++) {
        lcdData(msg[i]);
    }
    lcdCommand(0xC4);
    char ms[10] = "Quadrados";
    for (k = 0; k < 9; k++) {
        lcdData(ms[k]);
    }
    lcdCommand(0x94);
    char mst[10] = "Aparecem?";
    for (k = 0; k < 9; k++) {
        lcdData(mst[k]);
    }

    delayms(3200);

    lcdCommand(0x40);
    lcdInit();
    for (i = 0; i < 48; i++) {
        lcdData(quadrados[i]);
    }
    lcdCommand(0x86);
    lcdData(0);
    lcdCommand(0x89);
    lcdData(1);
    lcdCommand(0xD4);
    lcdData(2);
    lcdCommand(0xC6);
    lcdData(3);
    lcdCommand(0xC1);
    lcdData(4);
    lcdCommand(0x95);
    lcdData(5);

    delayms(3200);

    char msgs[8] = "4--Dois";
    lcdInit();
    lcdCommand(0x80);
    for (l = 0; l < 7; l++) {
        lcdData(msgs[l]);
    }
    lcdCommand(0xC0);
    char mss[10] = "5--Quatro";
    for (a = 0; a < 9; a++) {
        lcdData(mss[a]);
    }
    lcdCommand(0x90);
    char msys[9] = "6--Cinco";
    for (a = 0; a < 8; a++) {
        lcdData(msys[a]);
    }

    for (;;) {
        kpInit();
        kpDebounce();
        if (kpRead() != tcl) {
            tcl = kpRead();
            if (bitTst(tcl, 2)) {

                Errou();
                Reseta();
            }

            if (bitTst(tcl, 6)) {

                Errou();
                Reseta();

            }
            if (bitTst(tcl, 10)) {

                Acertou();
                Reseta();
            }

        }
    }
}

void Ingles2(void) {
    int tcl = 16;
    char l, a;
    char i, k;
    char msg[6] = "Ontem";
    lcdInit();
    lcdCommand(0x85);
    for (i = 0; i < 5; i++) {
        lcdData(msg[i]);
    }
    lcdCommand(0xC4);
    char ms[10] = "Em Ingles";
    for (k = 0; k < 9; k++) {
        lcdData(ms[k]);
    }
    delayms(2000);

    char msgs[12] = "4--Tomorrow";
    lcdInit();
    lcdCommand(0x80);
    for (l = 0; l < 11; l++) {
        lcdData(msgs[l]);
    }
    lcdCommand(0xC0);
    char mss[9] = "5--After";
    for (a = 0; a < 8; a++) {
        lcdData(mss[a]);
    }
    lcdCommand(0x90);
    char msys[13] = "6--Yesterday";
    for (a = 0; a < 12; a++) {
        lcdData(msys[a]);
    }

    for (;;) {
        kpInit();
        kpDebounce();
        if (kpRead() != tcl) {
            tcl = kpRead();
            if (bitTst(tcl, 2)) {

                Errou();
                Reseta();
            }

            if (bitTst(tcl, 6)) {

                Errou();
                Reseta();


            }
            if (bitTst(tcl, 10)) {

                Acertou();
                Reseta();
            }

        }
    }
}

void Matematica2(void) {
    char i, k, l, a;
    int tcl = 16;

    char msg[10] = "A soma de";
    lcdInit();
    lcdCommand(0x83);
    for (i = 0; i < 9; i++) {
        lcdData(msg[i]);
    }
    lcdCommand(0xC5);
    char ms[6] = "9 + 6";
    for (k = 0; k < 5; k++) {
        lcdData(ms[k]);
    }
    delayms(2500);
    char msgs[11] = "4--Dezoito";
    lcdInit();
    lcdCommand(0x80);
    for (l = 0; l < 10; l++) {
        lcdData(msgs[l]);
    }
    lcdCommand(0xC0);
    char mss[12] = "5--Quatorze";
    for (a = 0; a < 11; a++) {
        lcdData(mss[a]);
    }
    lcdCommand(0x90);
    char msys[10] = "6--Quinze";
    for (a = 0; a < 9; a++) {
        lcdData(msys[a]);
    }

    for (;;) {
        kpInit();
        kpDebounce();
        if (kpRead() != tcl) {
            tcl = kpRead();
            if (bitTst(tcl, 2)) {

                Errou();
                Reseta();
            }

            if (bitTst(tcl, 6)) {

                Errou();
                Reseta();

            }
            if (bitTst(tcl, 10)) {

                Acertou();
                Reseta();
            }

        }
    }
}

void NovaFase(void) {
    int tecla = 16, i;
    unsigned char coluna = 0, linha = 0;
    char l, k;

    char msgyy[6] = "Jogue";
    lcdInit();
    lcdCommand(0x85);
    for (i = 0; i < 5; i++) {
        lcdData(msgyy[i]);
    }
    lcdCommand(0xC5);
    char msqq[5] = "Mais";
    for (k = 0; k < 4; k++) {
        lcdData(msqq[k]);
    }
    delayms(2000);
    char msg[11] = "*--Memoria";
    lcdInit();
    lcdCommand(0x80);
    for (l = 0; l < 10; l++) {
        lcdData(msg[l]);
    }
    lcdCommand(0xC0);
    char ms[10] = "0--Ingles";
    for (k = 0; k < 9; k++) {
        lcdData(ms[k]);
    }
    lcdCommand(0x90);
    char msy[14] = "#--Matematica";
    for (k = 0; k < 13; k++) {
        lcdData(msy[k]);
    }

    for (;;) {

        kpInit();
        kpDebounce();
        if (kpRead() != tecla) {
            tecla = kpRead();
            if (bitTst(tecla, 0)) {

                Memoria2();
            }

            if (bitTst(tecla, 4)) {
                Ingles2();

            }
            if (bitTst(tecla, 8)) {

                Matematica2();
            }

        }
    }

}

void AprenderIngles(void) {
    int tcl = 16;
    char l, a;
    char i, k;
    char msg[5] = "Azul";
    lcdInit();
    lcdCommand(0x86);
    for (i = 0; i < 4; i++) {
        lcdData(msg[i]);
    }
    lcdCommand(0xC4);
    char ms[10] = "Em Ingles";
    for (k = 0; k < 9; k++) {
        lcdData(ms[k]);
    }
    delayms(2000);


    char msgs[10] = "1--Yellow";
    lcdInit();
    lcdCommand(0x80);
    for (l = 0; l < 9; l++) {
        lcdData(msgs[l]);
    }
    lcdCommand(0xC0);
    char mss[8] = "2--Blue";
    for (a = 0; a < 7; a++) {
        lcdData(mss[a]);
    }
    lcdCommand(0x90);
    char msys[7] = "3--Red";
    for (a = 0; a < 6; a++) {
        lcdData(msys[a]);
    }

    for (;;) {
        kpInit();
        kpDebounce();
        if (kpRead() != tcl) {
            tcl = kpRead();
            if (bitTst(tcl, 3)) {

                Errou();
                NovaFase();
            }

            if (bitTst(tcl, 7)) {

                Acertou();
                NovaFase();


            }
            if (bitTst(tcl, 11)) {
                Errou();
                NovaFase();
            }

        }
    }
}

void JogoMemoria(void) {
    char quadrados[48] = {


        0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000,
        0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000,
        0b00011, 0b00111, 0b01000, 0b11000, 0b11000, 0b01000, 0b01111, 0b00011,
        0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000,
        0b00011, 0b00111, 0b01000, 0b11000, 0b11000, 0b01000, 0b01111, 0b00011,
        0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000,

    };
    char i, k, l, a;
    int tcl = 16;

    char msg[8] = "Quantos";
    lcdInit();
    lcdCommand(0x84);
    for (i = 0; i < 7; i++) {
        lcdData(msg[i]);
    }
    lcdCommand(0xC4);
    char ms[10] = "Quadrados";
    for (k = 0; k < 9; k++) {
        lcdData(ms[k]);
    }
    lcdCommand(0x94);
    char mst[10] = "Aparecem?";
    for (k = 0; k < 9; k++) {
        lcdData(mst[k]);
    }
    delayms(3200);

    lcdCommand(0x40);
    lcdInit();
    for (i = 0; i < 48; i++) {
        lcdData(quadrados[i]);
    }
    lcdCommand(0x86);
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(0xC6);
    lcdData(3);
    lcdData(4);
    lcdData(5);

    delayms(3200);

    char msgs[8] = "1--Dois";
    lcdInit();
    lcdCommand(0x80);
    for (l = 0; l < 7; l++) {
        lcdData(msgs[l]);
    }
    lcdCommand(0xC0);
    char mss[10] = "2--Quatro";
    for (a = 0; a < 9; a++) {
        lcdData(mss[a]);
    }
    lcdCommand(0x90);
    char msys[8] = "3--Seis";
    for (a = 0; a < 7; a++) {
        lcdData(msys[a]);
    }

    for (;;) {
        kpInit();
        kpDebounce();
        if (kpRead() != tcl) {
            tcl = kpRead();
            if (bitTst(tcl, 3)) {

                Errou();
                NovaFase();
            }

            if (bitTst(tcl, 7)) {

                Acertou();
                NovaFase();


            }
            if (bitTst(tcl, 11)) {

                Errou();
                NovaFase();
            }

        }
    }
}

void Matematica(void) {
    char i, k, l, a;
    int tcl = 16;

    char msg[10] = "A soma de";
    lcdInit();
    lcdCommand(0x83);
    for (i = 0; i < 9; i++) {
        lcdData(msg[i]);
    }
    lcdCommand(0xC5);
    char ms[6] = "3 + 4";
    for (k = 0; k < 5; k++) {
        lcdData(ms[k]);
    }
    delayms(2500);
    char msgs[8] = "1--Seis";
    lcdInit();
    lcdCommand(0x80);
    for (l = 0; l < 7; l++) {
        lcdData(msgs[l]);
    }
    lcdCommand(0xC0);
    char mss[8] = "2--Sete";
    for (a = 0; a < 7; a++) {
        lcdData(mss[a]);
    }
    lcdCommand(0x90);
    char msys[8] = "3--Oito";
    for (a = 0; a < 7; a++) {
        lcdData(msys[a]);
    }

    for (;;) {
        kpInit();
        kpDebounce();
        if (kpRead() != tcl) {
            tcl = kpRead();
            if (bitTst(tcl, 3)) {

                Errou();
                NovaFase();
            }

            if (bitTst(tcl, 7)) {

                Acertou();
                NovaFase();


            }
            if (bitTst(tcl, 11)) {

                Errou();
                NovaFase();
            }

        }
    }
}

void EscolherJogo(void) {

    int tecla = 16, i;
    unsigned char coluna = 0, linha = 0;
    char l, k;
    char msg[11] = "7--Memoria";
    lcdInit();
    lcdCommand(0x80);
    for (l = 0; l < 10; l++) {
        lcdData(msg[l]);
    }
    lcdCommand(0xC0);
    char ms[10] = "8--Ingles";
    for (k = 0; k < 9; k++) {
        lcdData(ms[k]);
    }
    lcdCommand(0x90);
    char msy[14] = "9--Matematica";
    for (k = 0; k < 13; k++) {
        lcdData(msy[k]);
    }

    for (;;) {

        kpInit();
        kpDebounce();
        if (kpRead() != tecla) {
            tecla = kpRead();
            if (bitTst(tecla, 1)) {

                JogoMemoria();
            }

            if (bitTst(tecla, 5)) {

                AprenderIngles();
            }
            if (bitTst(tecla, 9)) {

                Matematica();
            }

        }
    }
}

void main(void) {

    BemVindo();
    delayms(2000);
    Entrada();
    delayms(2000);
    EscolherJogo();
    delayms(2000);

}
