/*
 * common.h
 *
 *  Created on: Apr 30, 2020
 *      Author: Arek
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include <stdbool.h>
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"



#define EN1_Pin 		GPIO_PIN_14
#define EN1_Port 		GPIOB
#define IN1_1_Pin 	GPIO_PIN_13
#define IN1_1_Port 	GPIOB
#define IN1_2_Pin 	GPIO_PIN_12
#define IN1_2_Port 	GPIOB
#define TIM 				&htim1
#define TIM_CHANNEL TIM_CHANNEL_1


typedef enum {stop = 0, go = !stop} 									motorState;
typedef enum {forward = 0, back = !forward} 					driveDirection;
typedef enum {left = 0, right = !left, straight = 2} 	currentDirection;

//variables
extern TIM_HandleTypeDef 	htim1;

driveDirection 		_direction;
motorState 				_motorState;
currentDirection 	_currentTurningDirection;

//functions
void carInit();
void drive();
void changeDirection(driveDirection _direction);
void changeMotorState(motorState _motorState);

void turnLeft();
void turnRight();
void driveForward();



#endif /* INC_COMMON_H_ */
