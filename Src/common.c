/*
 * common.c
 *
 *  Created on: Apr 30, 2020
 *      Author: Arek
 */
#include <stdbool.h>
#include "common.h"
#include "gpio.h"
#include "tim.h"

extern TIM_HandleTypeDef 	htim1;
extern driveDirection 		_direction;
extern motorState 				_motorState;
extern currentDirection 	_currentTurningDirection;

void carInit()
{
	MX_TIM1_Init();
	HAL_TIM_PWM_Start(TIM, TIM_CHANNEL);
	_direction = forward;
	_motorState = stop;
	_currentTurningDirection = straight;
  __HAL_TIM_SET_COMPARE(TIM, TIM_CHANNEL, 1200);
}

void drive()
{
	//IN1 - '+'  IN2 - "-" drive forward
	//IN1 - '-'  IN2 - "+" drive back
	// more information you can find in L293 data sheet

	if(_motorState){
		if(_direction == forward){
			// turn off motor
			HAL_GPIO_WritePin(EN1_Port, EN1_Pin, RESET);

			HAL_GPIO_WritePin(IN1_1_Port, IN1_1_Pin, SET);
			HAL_GPIO_WritePin(IN1_2_Port, IN1_2_Pin, RESET);

			//turn on motor
			HAL_GPIO_WritePin(EN1_Port, EN1_Pin, SET);
		}
		else if(_direction == back){
			HAL_GPIO_WritePin(EN1_Port, EN1_Pin, RESET);
			HAL_GPIO_WritePin(IN1_1_Port, IN1_1_Pin, RESET);
			HAL_GPIO_WritePin(IN1_2_Port, IN1_2_Pin, SET);
			HAL_GPIO_WritePin(EN1_Port, EN1_Pin, SET);
		}
		else{
			// some error
			// turn on LED on PCB
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);

		}
	}
	else{ // _motorState == 0
		HAL_GPIO_WritePin(EN1_Port, EN1_Pin, RESET);
	}
}

void changeDirection(driveDirection d)
{
	_direction = d;
	drive();
}

void changeMotorState(motorState ms)
{
	_motorState = ms;
	drive();
}


void turnLeft()
{
	__HAL_TIM_SET_COMPARE(TIM, TIM_CHANNEL, 1450);
	_currentTurningDirection = left;
}

void turnRight()
{
	__HAL_TIM_SET_COMPARE(TIM, TIM_CHANNEL, 950);
	_currentTurningDirection = right;
}

void driveForward()
{
	//my servo doesn't work perfect. It's a reason why I used
	//other arguments
	if(_currentTurningDirection == left)
		__HAL_TIM_SET_COMPARE(TIM, TIM_CHANNEL, 1250);
	else if(_currentTurningDirection == right)
		__HAL_TIM_SET_COMPARE(TIM, TIM_CHANNEL, 1150);

}
