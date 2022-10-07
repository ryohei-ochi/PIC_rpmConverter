// PIC12F683 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Detect (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

#define _XTAL_FREQ 4000000

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

int main(int argc, char** argv) {
    
    ANSEL  = 0b00000000 ;     // すべてデジタルI/O
    TRISIO = 0b00001000 ;     // ピンは全て出力に割当てる(GP3は入力のみ)
    WPU    = 0b00000100 ;     // GP2は内部プルアップ抵抗を指定する
    GPIO   = 0x00 ;           // 出力ピンの初期化
    
    
    // GP2 出力
    // GP3 入力
    
    int count;
    count = 0;
    
    int flag;
    flag = 0;

    while( 1 ){

        // 入力の立ち上がりを検出
        if( GP3 == 1 && flag == 0 ){
            flag = 1;
            count++;

            // 8分周して出力をオン
            if( count == 7 ){
                GP2  = 1;
            }
        }
        
        // 入力の立ち下がりを検出
        if( GP3 == 0 && flag == 1 ){
            flag = 0;
            GP2 = 0;
            
            // カウンタをリセット
            if( count == 7 ){
                count = 0;
            }
        }
    }

    return (EXIT_SUCCESS);
}
