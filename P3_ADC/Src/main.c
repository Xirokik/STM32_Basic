/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */


#include "main.h"

/*#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif*/

__IO uint32_t Tick;

void ADC_Pin(void);
void ADC_Config(void);
uint32_t ADC_Read(void);
void ADC_Conversion(void);

void Delay(uint32_t delay_ms);
uint32_t GetSystemTick(void);

uint32_t ADC_Data;
int main(void)
{
	SysTick_Config(4000000/1000);

	ADC_Config();
	ADC_Pin();

	/* Loop forever */
	while(1){
		ADC_Conversion();
		ADC_Data=ADC_Read();
	}
}

void ADC_Config(void){
	RCC->AHB2ENR|= RCC_AHB2ENR_ADCEN;//ADC clock enable

	RCC->CCIPR|=RCC_CCIPR_ADCSEL; //  ADCs clock source selection (System clock selected)
	ADC1->CR&= ~(ADC_CR_DEEPPWD); //Deep-power-down enable - NEED TO BE DISABLE
	ADC1->CR|= ADC_CR_ADVREGEN;//  ADC voltage regulator enable
	//ADCALDIF: Differential mode for calibration (single-ended inputs mode (default)
	ADC123_COMMON ->CCR &= ~(ADC_CCR_PRESC); //ADC prescaler (not divided) 4 MHZ

	ADC1->CFGR&=~(ADC_CFGR_RES); //Data resolution 12-bit
	ADC1->CFGR&=~(ADC_CFGR_ALIGN); //Data alignment right alignment
	//ADC1->SMPR1|= ADC_SMPR1_SMP5_2;// sampling time
	ADC1->SQR1&= ~(ADC_SQR1_L); //1 conversion default

	ADC1->SQR1|=ADC_SQR1_SQ1_2 | ADC_SQR1_SQ1_0;// IN5 in sequence
	ADC1->CR|=ADC_CR_ADCAL; // ADC calibration
	while(ADC1->CR&ADC_CR_ADCAL);
	ADC1->CR|=ADC_CR_ADEN; //ADC enable control

}


void ADC_Pin(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //enable gpioa

	GPIOA->MODER |= GPIO_MODER_MODE0; //Analog input(reset mode)

	GPIOA->ASCR|=GPIO_ASCR_ASC0;//Connect analog switch to the ADC input PA0

}

void ADC_Conversion(void){


	ADC1->CR|=ADC_CR_ADSTART;
	while(!(ADC1->ISR&ADC_ISR_EOS));

}
uint32_t ADC_Read(void){
	return ADC1->DR;
}
void Delay(uint32_t delay_ms){
	uint32_t StartTime=Tick;
	while(Tick<(StartTime+delay_ms)){

	}
}
uint32_t GetSystemTick(void){
	return Tick;
}
