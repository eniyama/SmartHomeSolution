/*
 * relay_control.c
 *
 *  Created on: Dec 27, 2025
 *      Author: Dev-Laptop2
 */

#include "relay_control.h"
#include "stm32f4xx_hal.h"

#include <string.h>
#include <stdio.h>

/* These macros move from main.c to here */
#define RELAY_ON_HW()   HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_RESET)
#define RELAY_OFF_HW()  HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_SET)

void Relay_Init(void)
{
	RELAY_ON_HW();   // default state
}

void Relay_ON(void)
{
    RELAY_ON_HW();
    printf("Relay ON\r\n");
}

void Relay_OFF(void)
{
    RELAY_OFF_HW();
    printf("Relay OFF\r\n");
}

void Relay_ProcessCommand(const command_t *cmd)
{
	switch (cmd->command.command_type)
	    {
	        case CMD_RELAY_ON:
	        {
	            Relay_OFF();
	            break;
	        }

	        case CMD_RELAY_OFF:
	        {
	            Relay_ON();
	            break;
	        }

	        default:
	            // Unknown command
	            break;
	    }
}

