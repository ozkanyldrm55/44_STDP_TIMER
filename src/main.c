/* Discovery Board uzerindeki ledler 1 sn ara ile yanip soner */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

TIM_TimeBaseInitTypeDef TIM_InitStruct;
GPIO_InitTypeDef GPIO_InitStruct;

int count = 0;

/*   SN = ((periyod +1) * (prescaler +1)) / clock speed   */

void Timer_Config() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 3999;
	TIM_InitStruct.TIM_Prescaler = 41999;
	TIM_InitStruct.TIM_RepetitionCounter = 0; // kac tasmada sistemin bastan baslamasini ayarlar.her zaman bir fazlasini alir.yani 1 deseydik 2 tasmada sistem basa donecekti.

	TIM_TimeBaseInit(TIM2 ,&TIM_InitStruct);
	TIM_Cmd(TIM2,ENABLE);
}

void GPIO_Config() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD , &GPIO_InitStruct);
}

int main(void) {
	Timer_Config();
	GPIO_Config();

  while (1) {
    count = TIM_GetCounter(TIM2);

    if(count == 1999)
    	GPIO_SetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    if(count ==3999)
    	GPIO_ResetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
