#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

/*
チンパンジーでもわかる！
ichigoplus基板ドライバの作り方！
何をしたい？
１、ピンの配置を変えたい　→15行目へ
２、新しいピンを追加したい　→　ｎ行目へ
３、ピンを消したい　→　ｎ行目へ
４、基板の名前が変わった　→　ｎ行目へ
１、ピンの配置を変えたい
　１、デジタルピンかアナログピンの場合
　　例)#define D0_PIN		  GPIOE,GPIO_Pin_4
　　D0_PINはD0という名前のクラスのピンの名前を記したdefineです。
　　もしD1ならD1_PINとなります。
　　後ろのGPIOE,GPIO_Pin_4はピンの名前で、データシートのPC4を指します
　　例えばPA0を指定したければここにGPIOA,GPIO_Pin_0を入力してください。
　　アナログピンであればA0_PINみたいな名前になっているはずです。
　　これもA0という名前のクラスのピンの名前を記したdefineです。
　　もしA1ならA1_PINとなります。
　　後ろのGPIOE,GPIO_Pin_4はデータシートのPC4を指します
　　例えばPA0を指定したければここにGPIOA,GPIO_Pin_0を入力してください。
　２，エンコーダの場合
　　例)
　　#define ENC0TIM TIM5
　　#define ENC0		GPIOA,GPIO_Pin_0 | GPIO_Pin_1
　　ENC0TIMはEnc0という名前のクラスが使うタイマーを記したdefineです。
　　もしEnc1ならENC1TIMとなります。
　　後ろのTIM5はタイマーの名前で、データシートのTIM5を指します。
　　例えばTIM4を指定したければここにTIM4を入力してください。
　　ENC0はEnc0という名前のクラスが使うピンを記したdefineです。
　　もしEnc1ならENC1となります。
　　後ろのGPIOA,GPIO_Pin_0 | GPIO_Pin_1は使うピンの名前で、データシートのPA0,PA1を指します。
　　例えば、PE1,PE2を指したければGPIOE, GPIO_Pin_0 | GPIO_Pin_1 と入力してください。
　３，PWMの場合
　　例)
　　#define PWM0		    GPIOB,GPIO_Pin_14
　　#define PWM0SET			TIM12,PWM0
　　#define PWM0TIMCH		TIM12,1
　　PWM0はPwm0という名前のクラスが使うピンを記したdefineです。
　　デジタルと同じです。
　　PWM0SETはPwm0という名前のクラスが使うタイマーを記したdefineです。
　　もしPwm1ならPWM1SETとなります。
　　後ろのTIM12は使うタイマーの名前で、データシートのTIM12を指します。
　　PWM0は上で解説したdefineです。もしPWM1SETならPWM1としてください。
　　PWM0TIMCH　はタイマーとチャンネルを記したdefineです。
　　もしPwm1ならPWM1TIMCHとなります。
　　後ろの TIM12,1は TIM12のCH1を指します。　もしTIM8のCH3を指したければTIM8,3と入力してください。
　４，CANの場合
　　例)
　　#define CAN0_PORT GPIOB,GPIO_Pin_9,GPIOB,GPIO_Pin_8
　　#define CAN0_NUMBER 1
　　CAN0_PORTはCan0という名前のクラスが使うピンを記したdefineです。
　　デジタルと同じです。
　　CAN0_NUMBERはCANモジュールの番号を指します。CAN1なら1を、CAN2なら2を入れて下さい
　５，シリアルの場合
　　例)
　　#define SERIAL0TxRx GPIOB,GPIO_Pin_10,GPIOB,GPIO_Pin_11
　　#define SERIAL0CH USART3
　　SERIAL0TxRxはSerial0という名前のクラスが使うピンを記したdefineです。
　　デジタルと同じです
　　SERIAL0CHはSerial0という名前のクラスが使うシリアルモジュールを記したdefineです。
　　USART3ならUSART3を、UART6ならUSART6を入れて下さい
　  シリアルでは割り込みハンドラの名前も変更する必要があります。
　　extern "C" void USART6_IRQHandler(void)のUSART6の部分を利用するモジュールの名前に置き換えてください。
２，新しいピンを追加したい
　先にpin.hppを読んで下さい
　読んできました？
　既に書かれているものと同じ種類のクラスを見つけてコピーします。
　A0とかPwm0とかにはここからここまでがクラスが書いてあるところという印があります。そこからそこまでをコピーしてください。SerialだけはSerial1を使って下さい。
　それが終わったらコピーして貼り付けた部分のクラス名やdefineを全部新たなクラス名やdefineに書き直してください。全部です。一文字も間違えないで下さい。
３、ピンを消したい
　消したいクラスをまるごと消して下さい。
　クラス名::関数名　という名前で関数が宣言されています。同じクラス名のものを全部消してしまいましよう。
　pin.hppのほうも見て下さい。
４、基板の名前が変わった
　char* board_name()という関数があります。この中に基板の名前を書いてください。
 */

extern "C" {
#include "config_usart.h"
#include "config_encoder.h"
#include "config_systick.h"
#include "config_usart.h"
#include "config_pwm.h"
#include "config_port.h"
#include "config_adc.h"
#include "config_can.h"
#include "config_usb.h"
#include "config_i2c.h"
#include "config_iwdg.h"
#include "config_spi.h"
#include "config_tim_interrupt.h"
}

#include "pin.hpp"
using namespace rp_lib;

char* board_name() {
	return (char*)"STM32F4 SRC2022 Auto Main";
}

//--- ENCODER
#define ENC0TIM TIM3
#define ENC0    GPIOB,GPIO_Pin_4, GPIOB,GPIO_Pin_5

#define ENC1TIM TIM4
#define ENC1    GPIOB,GPIO_Pin_6, GPIOB,GPIO_Pin_7

#define ENC2TIM TIM2
#define ENC2	GPIOA,GPIO_Pin_5, GPIOB,GPIO_Pin_3

#define ENC3TIM TIM5
#define ENC3    GPIOA,GPIO_Pin_0, GPIOA,GPIO_Pin_1

//Motor
#define MD0R        GPIOA,GPIO_Pin_3
#define MD0RSET     TIM2,MD0R
#define MD0RTIMCH   TIM2,4
#define MD0L        GPIOA,GPIO_Pin_2
#define MD0LSET     TIM2,MD0L
#define MD0LTIMCH   TIM2,3

#define MD1R        GPIOB,GPIO_Pin_14
#define MD1RSET     TIM12,MD1R
#define MD1RTIMCH   TIM12,1
#define MD1L        GPIOB,GPIO_Pin_15
#define MD1LSET     TIM12,MD1L
#define MD1LTIMCH   TIM12,2

#define MD2R        GPIOC,GPIO_Pin_6
#define MD2RSET     TIM8,MD2R
#define MD2RTIMCH   TIM8,1
#define MD2L        GPIOC,GPIO_Pin_7
#define MD2LSET     TIM8,MD2L
#define MD2LTIMCH   TIM8,2

#define MD3R        GPIOC,GPIO_Pin_8
#define MD3RSET     TIM8,MD3R
#define MD3RTIMCH   TIM8,3
#define MD3L        GPIOC,GPIO_Pin_9
#define MD3LSET     TIM8,MD3L
#define MD3LTIMCH   TIM8,4

#define MD4R        GPIOA,GPIO_Pin_8
#define MD4RSET     TIM1,MD4R
#define MD4RTIMCH   TIM1,1
#define MD4L        GPIOA,GPIO_Pin_9
#define MD4LSET     TIM1,MD4L
#define MD4LTIMCH   TIM1,2


//SW
#define SW0_PIN      GPIOC,GPIO_Pin_0
#define SW1_PIN      GPIOC,GPIO_Pin_15
#define SW2_PIN      GPIOA,GPIO_Pin_10
#define SW3_PIN      GPIOA,GPIO_Pin_11
#define SW4_PIN      GPIOA,GPIO_Pin_12

//Photo
#define D0_PIN      GPIOB,GPIO_Pin_11
#define D1_PIN      GPIOB,GPIO_Pin_10
#define D2_PIN      GPIOB,GPIO_Pin_9
#define D3_PIN      GPIOB,GPIO_Pin_8


//LED
#define A0_PIN      GPIOC,GPIO_Pin_1
#define A1_PIN      GPIOC,GPIO_Pin_2
#define A2_PIN      GPIOC,GPIO_Pin_3
#define A3_PIN      GPIOC,GPIO_Pin_4
#define A4_PIN      GPIOC,GPIO_Pin_5
#define A5_PIN      GPIOB,GPIO_Pin_0
#define A6_PIN      GPIOB,GPIO_Pin_1


/*CAN*/
#define CAN0_PORT GPIOA,GPIO_Pin_12,GPIOA,GPIO_Pin_11
#define CAN0_NUMBER 1

/*UART*/

#define SERIAL0TxRx GPIOC,GPIO_Pin_12,GPIOD,GPIO_Pin_2
#define SERIAL0CH UART5

#define SERIAL1TxRx GPIOC,GPIO_Pin_10,GPIOC,GPIO_Pin_11
#define SERIAL1CH USART3

/*I2C*/
#define I2C_PORT_SCL_SDA	GPIOB,GPIO_Pin_8,GPIOB,GPIO_Pin_9
#define I2CMODE I2C1

bool DigitalInterrupt0::handlerMap[16];
DigitalInterruptHandler *DigitalInterrupt0::digitalInterruptHander[16];

// Led0 start

// Pwm0 start
int A0::_digitalWrite(){
	return GPIO_ReadOutputDataBit(A0_PIN);
}

void A0::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(A0_PIN);
	else GPIO_SetBits(A0_PIN);
}

int A0::_digitalRead(){
	return GPIO_ReadInputDataBit(A0_PIN);
}

int A0::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, A0_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A0::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, A0_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A0::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, A0_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A0::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, A0_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A0::_setupAnalogIn(){
	mode = MODE_ANALOG;
	Init_ADC1(A0_PIN);
	return 0;
}

float A0::_analogRead(){
	return (get_ADC1_value(A0_PIN) / analogResolution());
}
//--- A0 end
//--- A1 start
int A1::_digitalWrite(){
	return GPIO_ReadOutputDataBit(A1_PIN);
}

void A1::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(A1_PIN);
	else GPIO_SetBits(A1_PIN);
}

int A1::_digitalRead(){
	return GPIO_ReadInputDataBit(A1_PIN);
}

int A1::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, A1_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A1::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, A1_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A1::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, A1_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A1::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, A1_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A1::_setupAnalogIn(){
	mode = MODE_ANALOG;
	Init_ADC1(A1_PIN);
	return 0;
}

float A1::_analogRead(){
	return (get_ADC1_value(A1_PIN) / analogResolution());
}
//--- A1 end
//--- A2 start
int A2::_digitalWrite(){
	return GPIO_ReadOutputDataBit(A2_PIN);
}

void A2::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(A2_PIN);
	else GPIO_SetBits(A2_PIN);
}

int A2::_digitalRead(){
	return GPIO_ReadInputDataBit(A2_PIN);
}

int A2::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, A2_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A2::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, A2_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A2::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, A2_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A2::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, A2_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A2::_setupAnalogIn(){
	mode = MODE_ANALOG;
	Init_ADC1(A2_PIN);
	return 0;
}

float A2::_analogRead(){
	return (get_ADC1_value(A2_PIN) / analogResolution());
}
//--- A2 end
//--- A3 start
int A3::_digitalWrite(){
	return GPIO_ReadOutputDataBit(A3_PIN);
}

void A3::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(A3_PIN);
	else GPIO_SetBits(A3_PIN);
}

int A3::_digitalRead(){
	return GPIO_ReadInputDataBit(A3_PIN);
}

int A3::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, A3_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A3::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, A3_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A3::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, A3_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A3::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, A3_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A3::_setupAnalogIn(){
	mode = MODE_ANALOG;
	Init_ADC1(A3_PIN);
	return 0;
}

float A3::_analogRead(){
	return (get_ADC1_value(A3_PIN) / analogResolution());
}
//--- A3 end
//--- A4 start
int A4::_digitalWrite(){
	return GPIO_ReadOutputDataBit(A4_PIN);
}

void A4::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(A4_PIN);
	else GPIO_SetBits(A4_PIN);
}

int A4::_digitalRead(){
	return GPIO_ReadInputDataBit(A4_PIN);
}

int A4::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, A4_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A4::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, A4_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A4::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, A4_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A4::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, A4_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A4::_setupAnalogIn(){
	mode = MODE_ANALOG;
	Init_ADC1(A4_PIN);
	return 0;
}

float A4::_analogRead(){
	return (get_ADC1_value(A4_PIN) / analogResolution());
}
//--- A4 end
//--- A5 start
int A5::_digitalWrite(){
	return GPIO_ReadOutputDataBit(A5_PIN);
}

void A5::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(A5_PIN);
	else GPIO_SetBits(A5_PIN);
}

int A5::_digitalRead(){
	return GPIO_ReadInputDataBit(A5_PIN);
}

int A5::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, A5_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A5::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, A5_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A5::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, A5_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A5::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, A5_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A5::_setupAnalogIn(){
	mode = MODE_ANALOG;
	Init_ADC1(A5_PIN);
	return 0;
}

float A5::_analogRead(){
	return (get_ADC1_value(A5_PIN) / analogResolution());
}
//--- A5 end
//--- A6 start
int A6::_digitalWrite(){
	return GPIO_ReadOutputDataBit(A6_PIN);
}

void A6::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(A6_PIN);
	else GPIO_SetBits(A6_PIN);
}

int A6::_digitalRead(){
	return GPIO_ReadInputDataBit(A6_PIN);
}

int A6::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, A6_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A6::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, A6_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int A6::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, A6_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int A6::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, A6_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int A6::_setupAnalogIn(){
	mode = MODE_ANALOG;
	Init_ADC1(A6_PIN);
	return 0;
}

float A6::_analogRead(){
	return (get_ADC1_value(A6_PIN) / analogResolution());
}

//--- A2 end
//--- D0 start
D0::D0(){
	line=Pin_source(D0_PIN);
}

int D0::_digitalWrite(){
	return GPIO_ReadOutputDataBit(D0_PIN);
}

void D0::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(D0_PIN);
	else GPIO_SetBits(D0_PIN);
}

int D0::_digitalRead(){
	return GPIO_ReadInputDataBit(D0_PIN);
}

int D0::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, D0_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int D0::_setupDigitalOut(){
	Init_port(GPIO_Mode_OUT, D0_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int D0::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, D0_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int D0::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, D0_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}
//--- D0 end
//--- D1 start
D1::D1(){
	line=Pin_source(D1_PIN);
}

int D1::_digitalWrite(){
	return GPIO_ReadOutputDataBit(D1_PIN);
}

void D1::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(D1_PIN);
	else GPIO_SetBits(D1_PIN);
}

int D1::_digitalRead(){
	return GPIO_ReadInputDataBit(D1_PIN);
}

int D1::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, D1_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int D1::_setupDigitalOut(){
	Init_port(GPIO_Mode_OUT, D1_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int D1::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, D1_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int D1::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, D1_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}
//--- D1 end
//***D2 starg ***
D2::D2(){
	line=Pin_source(D2_PIN);
}
int D2::_digitalWrite(){
	return GPIO_ReadOutputDataBit(D2_PIN);
}

void D2::_digitalWrite(int value){
	if (value == 0) {
		GPIO_ResetBits(D2_PIN);
	} else {
		GPIO_SetBits(D2_PIN);
	}
}

int D2::_digitalRead(){
	return GPIO_ReadInputDataBit(D2_PIN);
}

int D2::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, D2_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int D2::_setupDigitalOut(){
	Init_port(GPIO_Mode_OUT, D2_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int D2::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, D2_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int D2::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, D2_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}
//*** D2 end ***
//*** D3 start ***
D3::D3(){
	line=Pin_source(D3_PIN);
}
int D3::_digitalWrite(){
	return GPIO_ReadOutputDataBit(D3_PIN);
}

void D3::_digitalWrite(int value){
	if (value == 0) {
		GPIO_ResetBits(D3_PIN);
	} else {
		GPIO_SetBits(D3_PIN);
	}
}

int D3::_digitalRead(){
	return GPIO_ReadInputDataBit(D3_PIN);
}

int D3::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, D3_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int D3::_setupDigitalOut(){
	Init_port(GPIO_Mode_OUT, D3_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int D3::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, D3_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int D3::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, D3_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}
//***D3 end**
//---MD start
int Md0r::_digitalWrite(){
	return GPIO_ReadOutputDataBit(MD0R);
}

void Md0r::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(MD0R);
	else GPIO_SetBits(MD0R);
}

int Md0r::_digitalRead(){
	return GPIO_ReadInputDataBit(MD0R);
}

int Md0r::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, MD0R, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md0r::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, MD0R, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md0r::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, MD0R, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Md0r::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, MD0R, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Md0r::_setupPwmOut(float frequency, float duty){
	int i;
	mode = MODE_PWM;
	i = Init_PWM(MD0RSET, frequency);
	Set_duty(MD0RTIMCH, duty);
	return i;
}

void Md0r::_pwmWrite(float duty){
	Set_duty(MD0RTIMCH, duty);
}

float Md0r::_pwmWrite(){
	return Read_duty(MD0RTIMCH);
}
//--- Md0r end

//--- Md0l start
int Md0l::_digitalWrite(){
	return GPIO_ReadOutputDataBit(MD0L);
}

void Md0l::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(MD0L);
	else GPIO_SetBits(MD0L);
}

int Md0l::_digitalRead(){
	return GPIO_ReadInputDataBit(MD0L);
}

int Md0l::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, MD0L, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md0l::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, MD0L, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md0l::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, MD0L, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Md0l::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, MD0L, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Md0l::_setupPwmOut(float frequency, float duty){
	int i;
	mode = MODE_PWM;
	i = Init_PWM(MD0LSET, frequency);
	Set_duty(MD0LTIMCH, duty);
	return i;
}

void Md0l::_pwmWrite(float duty){
	Set_duty(MD0LTIMCH, duty);
}

float Md0l::_pwmWrite(){
	return Read_duty(MD0LTIMCH);
}
//--- Md0l end

//--- Md1r start
int Md1r::_digitalWrite(){
	return GPIO_ReadOutputDataBit(MD1R);
}

void Md1r::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(MD1R);
	else GPIO_SetBits(MD1R);
}

int Md1r::_digitalRead(){
	return GPIO_ReadInputDataBit(MD1R);
}

int Md1r::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, MD1R, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md1r::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, MD1R, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md1r::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, MD1R, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Md1r::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, MD1R, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Md1r::_setupPwmOut(float frequency, float duty){
	int i;
	mode = MODE_PWM;
	i = Init_PWM(MD1RSET, frequency);
	Set_duty(MD1RTIMCH, duty);
	return i;
}

void Md1r::_pwmWrite(float duty){
	Set_duty(MD1RTIMCH, duty);
}

float Md1r::_pwmWrite(){
	return Read_duty(MD1RTIMCH);
}
//--- Md1r end

//--- Md1lstart
int Md1l::_digitalWrite(){
	return GPIO_ReadOutputDataBit(MD1L);
}

void Md1l::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(MD1L);
	else GPIO_SetBits(MD1L);
}

int Md1l::_digitalRead(){
	return GPIO_ReadInputDataBit(MD1L);
}

int Md1l::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, MD1L, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md1l::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, MD1L, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md1l::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, MD1L, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Md1l::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, MD1L, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Md1l::_setupPwmOut(float frequency, float duty){
	int i;
	mode = MODE_PWM;
	i = Init_PWM(MD1LSET, frequency);
	Set_duty(MD1LTIMCH, duty);
	return i;
}

void Md1l::_pwmWrite(float duty){
	Set_duty(MD1LTIMCH, duty);
}

float Md1l::_pwmWrite(){
	return Read_duty(MD1LTIMCH);
}
//--- Md1l end

//--- Md2r start
int Md2r::_digitalWrite(){
	return GPIO_ReadOutputDataBit(MD2R);
}

void Md2r::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(MD2R);
	else GPIO_SetBits(MD2R);
}

int Md2r::_digitalRead(){
	return GPIO_ReadInputDataBit(MD2R);
}

int Md2r::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, MD2R, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md2r::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, MD2R, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md2r::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, MD2R, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Md2r::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, MD2R, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Md2r::_setupPwmOut(float frequency, float duty){
	int i;
	mode = MODE_PWM;
	i = Init_PWM(MD2RSET, frequency);
	Set_duty(MD2RTIMCH, duty);
	return i;
}

void Md2r::_pwmWrite(float duty){
	Set_duty(MD2RTIMCH, duty);
}

float Md2r::_pwmWrite(){
	return Read_duty(MD2RTIMCH);
}
//--- Md2r end

//--- Md2l start
int Md2l::_digitalWrite(){
	return GPIO_ReadOutputDataBit(MD2L);
}

void Md2l::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(MD2L);
	else GPIO_SetBits(MD2L);
}

int Md2l::_digitalRead(){
	return GPIO_ReadInputDataBit(MD2L);
}

int Md2l::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, MD2L, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md2l::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, MD2L, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md2l::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, MD2L, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Md2l::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, MD2L, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Md2l::_setupPwmOut(float frequency, float duty){
	int i;
	mode = MODE_PWM;
	i = Init_PWM(MD2LSET, frequency);
	Set_duty(MD2LTIMCH, duty);
	return i;
}

void Md2l::_pwmWrite(float duty){
	Set_duty(MD2LTIMCH, duty);
}

float Md2l::_pwmWrite(){
	return Read_duty(MD2LTIMCH);
}
//--- Md2l end
//--- Md3r start
int Md3r::_digitalWrite(){
	return GPIO_ReadOutputDataBit(MD3R);
}

void Md3r::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(MD3R);
	else GPIO_SetBits(MD3R);
}

int Md3r::_digitalRead(){
	return GPIO_ReadInputDataBit(MD3R);
}

int Md3r::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, MD3R, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md3r::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, MD3R, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md3r::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, MD3R, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Md3r::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, MD3R, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Md3r::_setupPwmOut(float frequency, float duty){
	int i;
	mode = MODE_PWM;
	i = Init_PWM(MD3RSET, frequency);
	Set_duty(MD3RTIMCH, duty);
	return i;
}

void Md3r::_pwmWrite(float duty){
	Set_duty(MD3RTIMCH, duty);
}

float Md3r::_pwmWrite(){
	return Read_duty(MD3RTIMCH);
}
//--- Md3r end
//--- Md3lstart
int Md3l::_digitalWrite(){
	return GPIO_ReadOutputDataBit(MD3L);
}

void Md3l::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(MD3L);
	else GPIO_SetBits(MD3L);
}

int Md3l::_digitalRead(){
	return GPIO_ReadInputDataBit(MD3L);
}

int Md3l::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, MD3L, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md3l::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, MD3L, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Md3l::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, MD3L, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Md3l::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, MD3L, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

int Md3l::_setupPwmOut(float frequency, float duty){
	int i;
	mode = MODE_PWM;
	i = Init_PWM(MD3LSET, frequency);
	Set_duty(MD3LTIMCH, duty);
	return i;
}

void Md3l::_pwmWrite(float duty){
	Set_duty(MD3LTIMCH, duty);
}

float Md3l::_pwmWrite(){
	return Read_duty(MD3LTIMCH);
}
//--- Md3l end

//--- Md4r start
int Md4r::_digitalWrite(){
	return GPIO_ReadOutputDataBit(MD4R);
}

void Md4r::_digitalWrite(int value){
	if (value == 4)GPIO_ResetBits(MD4R);
	else GPIO_SetBits(MD4R);
}

int Md4r::_digitalRead(){
	return GPIO_ReadInputDataBit(MD4R);
}

int Md4r::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, MD4R, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 4;
}

int Md4r::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, MD4R, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 4;
}

int Md4r::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, MD4R, GPIO_PuPd_UP, GPIO_OType_PP);
	return 4;
}

int Md4r::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, MD4R, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 4;
}

int Md4r::_setupPwmOut(float frequency, float duty){
	int i;
	mode = MODE_PWM;
	i = Init_PWM(MD4RSET, frequency);
	Set_duty(MD4RTIMCH, duty);
	return i;
}

void Md4r::_pwmWrite(float duty){
	Set_duty(MD4RTIMCH, duty);
}

float Md4r::_pwmWrite(){
	return Read_duty(MD4RTIMCH);
}
//--- Md4r end
//--- Md4l start
int Md4l::_digitalWrite(){
	return GPIO_ReadOutputDataBit(MD4L);
}

void Md4l::_digitalWrite(int value){
	if (value == 4)GPIO_ResetBits(MD4L);
	else GPIO_SetBits(MD4L);
}

int Md4l::_digitalRead(){
	return GPIO_ReadInputDataBit(MD4L);
}

int Md4l::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, MD4L, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 4;
}

int Md4l::_setupDigitalOut(){
	mode = MODE_DIGITAL;
	Init_port(GPIO_Mode_OUT, MD4L, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 4;
}

int Md4l::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, MD4L, GPIO_PuPd_UP, GPIO_OType_PP);
	return 4;
}

int Md4l::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, MD4L, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 4;
}

int Md4l::_setupPwmOut(float frequency, float duty){
	int i;
	mode = MODE_PWM;
	i = Init_PWM(MD4LSET, frequency);
	Set_duty(MD4LTIMCH, duty);
	return i;
}

void Md4l::_pwmWrite(float duty){
	Set_duty(MD4LTIMCH, duty);
}

float Md4l::_pwmWrite(){
	return Read_duty(MD4LTIMCH);
}
//--- Sw0 start
Sw0::Sw0(){
	line=Pin_source(SW0_PIN);
}

int Sw0::_digitalWrite(){
	return GPIO_ReadOutputDataBit(SW0_PIN);
}

void Sw0::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(SW0_PIN);
	else GPIO_SetBits(SW0_PIN);
}

int Sw0::_digitalRead(){
	return GPIO_ReadInputDataBit(SW0_PIN);
}

int Sw0::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, SW0_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw0::_setupDigitalOut(){
	Init_port(GPIO_Mode_OUT, SW0_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw0::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, SW0_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Sw0::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, SW0_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}
//--- Sw0 end
//--- Sw1 start
Sw1::Sw1(){
	line=Pin_source(SW1_PIN);
}

int Sw1::_digitalWrite(){
	return GPIO_ReadOutputDataBit(SW1_PIN);
}

void Sw1::_digitalWrite(int value){
	if (value == 0)GPIO_ResetBits(SW1_PIN);
	else GPIO_SetBits(SW1_PIN);
}

int Sw1::_digitalRead(){
	return GPIO_ReadInputDataBit(SW1_PIN);
}

int Sw1::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, SW1_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw1::_setupDigitalOut(){
	Init_port(GPIO_Mode_OUT, SW1_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw1::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, SW1_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Sw1::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, SW1_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}
//--- Sw1 end
//***SW2縺ｯ縺倥∪繧�**
Sw2::Sw2(){
	line=Pin_source(SW2_PIN);
}
int Sw2::_digitalWrite(){
	return GPIO_ReadOutputDataBit(SW2_PIN);
}

void Sw2::_digitalWrite(int value){
	if (value == 0) {
		GPIO_ResetBits(SW2_PIN);
	} else {
		GPIO_SetBits(SW2_PIN);
	}
}

int Sw2::_digitalRead(){
	return GPIO_ReadInputDataBit(SW2_PIN);
}

int Sw2::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, SW2_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw2::_setupDigitalOut(){
	Init_port(GPIO_Mode_OUT, SW2_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw2::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, SW2_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Sw2::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, SW2_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}
//***SW2縺翫ｏ繧�**
//***SW3縺ｯ縺倥∪繧�**
Sw3::Sw3(){
	line=Pin_source(SW3_PIN);
}
int Sw3::_digitalWrite(){
	return GPIO_ReadOutputDataBit(SW3_PIN);
}

void Sw3::_digitalWrite(int value){
	if (value == 0) {
		GPIO_ResetBits(SW3_PIN);
	} else {
		GPIO_SetBits(SW3_PIN);
	}
}

int Sw3::_digitalRead(){
	return GPIO_ReadInputDataBit(SW3_PIN);
}

int Sw3::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, SW3_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw3::_setupDigitalOut(){
	Init_port(GPIO_Mode_OUT, SW3_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw3::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, SW3_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Sw3::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, SW3_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}
//***SW3 end ***
//***SW3 end ***
Sw4::Sw4(){
	line=Pin_source(SW4_PIN);
}
int Sw4::_digitalWrite(){
	return GPIO_ReadOutputDataBit(SW4_PIN);
}

void Sw4::_digitalWrite(int value){
	if (value == 0) {
		GPIO_ResetBits(SW4_PIN);
	} else {
		GPIO_SetBits(SW4_PIN);
	}
}

int Sw4::_digitalRead(){
	return GPIO_ReadInputDataBit(SW4_PIN);
}

int Sw4::_setupDigitalIn(){
	Init_port(GPIO_Mode_IN, SW4_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw4::_setupDigitalOut(){
	Init_port(GPIO_Mode_OUT, SW4_PIN, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	return 0;
}

int Sw4::_setupDigitalInPullUp(){
	Init_port(GPIO_Mode_IN, SW4_PIN, GPIO_PuPd_UP, GPIO_OType_PP);
	return 0;
}

int Sw4::_setupDigitalInPullDown(){
	Init_port(GPIO_Mode_IN, SW4_PIN, GPIO_PuPd_DOWN, GPIO_OType_PP);
	return 0;
}

//--- Enc0 start
namespace encoder {
int Enc0::setup()
{
	Init_encoder(ENC0TIM, ENC0);
	return 0;
}

void Enc0::cycle() {
	count_ = is_reverse ? -Select_encoder_count(ENC0TIM) : Select_encoder_count(ENC0TIM);
	radian_ = (float)count_ / cpr_ * 2.f * f_pi;
}
//--- Enc0 end
//--- Enc1 start
int Enc1::setup()
{
	Init_encoder(ENC1TIM, ENC1);
	return 0;
}

void Enc1::cycle() {
	count_ = is_reverse ? -Select_encoder_count(ENC1TIM) : Select_encoder_count(ENC1TIM);
	radian_ = (float)count_ / cpr_ * 2.f * f_pi;
}
//--- Enc1 end
//--- Enc2 start
int Enc2::setup()
{
	Init_encoder(ENC2TIM, ENC2);
	return 0;
}

void Enc2::cycle() {
	count_ = is_reverse ? -Select_encoder_count(ENC2TIM) : Select_encoder_count(ENC2TIM);
	radian_ = (float)count_ / cpr_ * 2.f * f_pi;
}
//--- Enc2 end
//--- Enc3 start
int Enc3::setup()
{
	Init_encoder(ENC3TIM, ENC3);
	return 0;
}

void Enc3::cycle() {
	count_ = is_reverse ? -Select_encoder_count(ENC3TIM) : Select_encoder_count(ENC3TIM);
	radian_ = (float)count_ / cpr_ * 2.f * f_pi;
}
}

//--- Enc3 end
//--- Serial0 start
int serialParitySelect(int parity){
	if(parity==Serial::SERIAL_PARITY_EVEN){
		return USART_Parity_Even;
	}else if(parity==Serial::SERIAL_PARITY_ODD){
		return USART_Parity_Odd;
	}else
		return USART_Parity_No;
}

int serialLengthSelect(int wordLength){
	if(wordLength==9){
		return USART_WordLength_9b;
	}else
		return USART_WordLength_8b;
}

SerialHandler *Serial0::Handler;
RingBuffer<char,256> Serial0::txBuf;
int Serial0::isTransmitting=0;

int Serial0::readNewLine=Serial0::SERIAL0_NEWLINE_NULL;
int Serial0::writeNewLine=Serial0::SERIAL0_NEWLINE_NULL;
char Serial0::oldWriteChar=0;
char Serial0::oldReadChar=0;
#define SERIAL0_TXINT

int Serial0::_setup(int baudrate, SerialHandler &HandlerArg, int parity, int wordLength)
{
#ifdef SERIAL0_TXINT
	Init_USARTi(SERIAL0CH,baudrate,SERIAL0TxRx, serialParitySelect(parity), serialLengthSelect(wordLength));
#else
	Init_USART(SERIAL0CH,baudrate,SERIAL0TxRx, serialParitySelect(parity), serialLengthSelect(wordLength));
#endif
	Handler=&HandlerArg;
	Handler->serialHandlerSetup(this);
	return 0;
}

void Serial0::writeChar(char value)
{
	transmit(value);
}

void serial0_rxInterrupt(){
	char value=USART_ReceiveData(SERIAL0CH);
	//char value1=0;
	/*		if(Serial0::writeNewLine==Serial0::SERIAL0_NEWLINE_LF){
			if(value=='\r'){
				if(Serial0::oldWriteChar!='\n')value='\n';
			}
			Serial0::oldWriteChar=value;
		}
		if(Serial0::writeNewLine==Serial0::SERIAL0_NEWLINE_CR){
			if(value=='\n'){
				if(Serial0::oldWriteChar!='\r')value='\r';
			}
			Serial0::oldWriteChar=value;
		}
		if(Serial0::writeNewLine==Serial0::SERIAL0_NEWLINE_CRLF){
			if(value=='\n'||value=='\r'){
				if(Serial0::oldWriteChar!='\n'||Serial0::oldWriteChar!='\r'){
					Serial0::oldWriteChar=value;
					value='\r';
					value1='\n';
				}
			}else{
				Serial0::oldWriteChar=value;
			}
		}*/
	Serial0::Handler->serialReadChar(value);
	//	if(value1)Serial0::Handler->serialReadChar(value1);
	//USART_ClearFlag(SERIAL0CH,USART_FLAG_RXNE);
	USART_ClearITPendingBit(SERIAL0CH,USART_IT_RXNE);

}

void serial0_txInterrupt(){
#ifdef SERIAL0_TXINT
	if(Serial0::txBuf.isEmpty()==0) USART_SendData(SERIAL0CH,Serial0::txBuf.read());
	if(Serial0::txBuf.isEmpty()==1) Serial0::isTransmitting=0;
	//USART_ClearFlag(SERIAL0CH,USART_FLAG_TC);
	USART_ClearITPendingBit(SERIAL0CH,USART_IT_TC);
#endif
}
void Serial0::transmit(char value){
#ifdef SERIAL0_TXINT
	char value1=0;
	if(writeNewLine==SERIAL0_NEWLINE_LF){
		if(value=='\r'){
			if(oldWriteChar!='\n')value='\n';
		}
		oldWriteChar=value;
	}
	if(writeNewLine==SERIAL0_NEWLINE_CR){
		if(value=='\n'){
			if(oldWriteChar!='\r')value='\r';
		}
		oldWriteChar=value;
	}
	if(writeNewLine==SERIAL0_NEWLINE_CRLF){
		if(value=='\n'||value=='\r'){
			if(oldWriteChar!='\n'||oldWriteChar!='\r'){
				oldWriteChar=value;
				value='\r';
				value1='\n';
			}
		}else{
			oldWriteChar=value;
		}
	}
	if(isTransmitting==0){
		USART_SendData(SERIAL0CH, value);
		//if(value1)USART_SendData(SERIAL0CH, value1);
		if(value1)while(txBuf.write(value1));
		isTransmitting=1;
	}else{
		while(txBuf.write(value));
		if(value1)while(txBuf.write(value1));
	}
#if 0
	if(isTransmitting==0){
		USART_SendData(SERIAL0CH, value);
		if(value=='\n')txBuf.write('\r');
		if(value=='\r')txBuf.write('\n');
		isTransmitting=1;
	}else{
		while(txBuf.write(value));
		if(value=='\n')while(txBuf.write('\r'));
		if(value=='\r')while(txBuf.write('\n'));
	}
#endif

#else
	while(USART_GetFlagStatus(SERIAL0CH, USART_FLAG_TXE) == RESET);
	USART_SendData(SERIAL0CH, value);
	if(value=='\n'){
		while(USART_GetFlagStatus(SERIAL0CH, USART_FLAG_TXE) == RESET);
		USART_SendData(SERIAL0CH, '\r');
	}
	if(value=='\r'){
		while(USART_GetFlagStatus(SERIAL0CH, USART_FLAG_TXE) == RESET);
		USART_SendData(SERIAL0CH, '\n');
	}
#endif
}

void Serial0::setReadNewLineLF(){readNewLine=SERIAL0_NEWLINE_LF;}
void Serial0::setReadNewLineCR(){readNewLine=SERIAL0_NEWLINE_CR;}
void Serial0::setReadNewLineCRLF(){readNewLine=SERIAL0_NEWLINE_CRLF;}
void Serial0::setWriteNewLineLF(){writeNewLine=SERIAL0_NEWLINE_LF;}
void Serial0::setWriteNewLineCR(){writeNewLine=SERIAL0_NEWLINE_CR;}
void Serial0::setWriteNewLineCRLF(){writeNewLine=SERIAL0_NEWLINE_CRLF;}


extern "C" void UART5_IRQHandler(void) {
	//serial0_rxInterrupt();
	//if (USART_GetFlagStatus(SERIAL0CH, USART_FLAG_TC) == SET)serial0_txInterrupt();
	//if (USART_GetFlagStatus(SERIAL0CH, USART_IT_RXNE) == SET)serial0_rxInterrupt();
	if (USART_GetITStatus(SERIAL0CH, USART_IT_TC) == SET)serial0_txInterrupt();
	if (USART_GetITStatus(SERIAL0CH, USART_IT_RXNE) == SET)serial0_rxInterrupt();
}

void std_char_out(char value) {
	//	while(USART_GetFlagStatus(SERIAL0CH, USART_FLAG_TXE) == RESET);
	//	USART_SendData(SERIAL0CH, value);
	Serial0::transmit(value);
}

void std_char_out_with_flush(char value){
	while(USART_GetFlagStatus(SERIAL0CH, USART_FLAG_TXE) == RESET);
	USART_SendData(SERIAL0CH, value);
	while(USART_GetFlagStatus(SERIAL0CH, USART_FLAG_TXE) == RESET);
}

int std_char_out_setup() {
	Serial0::Handler = new SerialHandler();
#ifdef SERIAL0_TXINT
	Init_USARTi(SERIAL0CH, 9600, SERIAL0TxRx, 0, 8);
#else
	Init_USART(SERIAL0CH, 9600, SERIAL0TxRx, 0, 8);
#endif
	return 0;
}

SerialHandler *Serial1::Handler;
RingBuffer<char, 256> Serial1::txBuf;
int Serial1::isTransmitting = 0;
#define SERIAL1_TXINT
// ---Serial0 end
//***Serial1はじまり***
int Serial1::_setup(int baudrate, SerialHandler &HandlerArg, int parity, int wordLength)
{
#ifdef SERIAL1_TXINT
	Init_USARTi(SERIAL1CH, baudrate, SERIAL1TxRx, serialParitySelect(parity), serialLengthSelect(wordLength));
#else
	Init_USART(SERIAL1CH, baudrate, SERIAL1TxRx,serialParitySelect(parity), serialLengthSelect(wordLength));
#endif
	Handler = &HandlerArg;
	Handler->serialHandlerSetup(this);
	return 0;
}

void Serial1::writeChar(char value)
{
	transmit(value);
}

void serial1_rxInterrupt() {
	Serial1::Handler->serialReadChar(USART_ReceiveData(SERIAL1CH));
	//USART_ClearFlag(SERIAL1CH, USART_FLAG_RXNE);
	USART_ClearITPendingBit(SERIAL1CH,USART_IT_RXNE);
}

void serial1_txInterrupt() {
#ifdef SERIAL1_TXINT
	if (Serial1::txBuf.isEmpty() == 0) USART_SendData(SERIAL1CH, Serial1::txBuf.read());
	if (Serial1::txBuf.isEmpty() == 1) Serial1::isTransmitting = 0;
	//USART_ClearFlag(SERIAL1CH, USART_FLAG_TC);
	USART_ClearITPendingBit(SERIAL1CH,USART_IT_TC);
#endif
}

void Serial1::transmit(char value) {
#ifdef SERIAL1_TXINT
	if (isTransmitting == 0) {
		USART_SendData(SERIAL1CH, value);
		isTransmitting = 1;
	}
	else {
		while (txBuf.write(value));
	}
#else
	while (USART_GetFlagStatus(SERIAL1CH, USART_FLAG_TXE) == RESET);
	USART_SendData(SERIAL1CH, value);
#endif
}


extern "C" void USART3_IRQHandler(void) {
	//serial1_rxInterrupt();
	//if (USART_GetFlagStatus(SERIAL1CH, USART_FLAG_TC) == SET)serial1_txInterrupt();
	//if (USART_GetFlagStatus(SERIAL1CH, USART_IT_RXNE) == SET)serial1_rxInterrupt();
	if (USART_GetITStatus(SERIAL1CH, USART_IT_TC) == SET)serial1_txInterrupt();
	if (USART_GetITStatus(SERIAL1CH, USART_IT_RXNE) == SET)serial1_rxInterrupt();
}
//***Serial1おわり***

int WatchDog::setup() {
	return Init_watchdog();
}

void WatchDog::cycle() {
	watchdog_reset();
}

