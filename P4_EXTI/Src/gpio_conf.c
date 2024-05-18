/*
 * gpio_conf.c
 *
 *  Created on: May 18, 2024
 *      Author: Arkadiusz
 */



#include "gpio_conf.h"

void ConfigLD(){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;//Active port
	GPIOA->MODER |= GPIO_MODER_MODE5_0;//set output
	GPIOA->MODER &= ~(GPIO_MODER_MODE5_1);
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);// push pull
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED5);// speed react
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5);//no pull up, pull down

}

void ConfigLD2(){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;//Active port
	GPIOA->MODER |= GPIO_MODER_MODE7_0;//set output
	GPIOA->MODER &= ~(GPIO_MODER_MODE7_1);
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT7);// push pull
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED7);// speed react
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD7);//no pull up, pull down

}

void ConfigButton(){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODE6);//set input
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD6_1);// pull up
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD6_0;
}

