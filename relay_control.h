/*
 * relay_control.h
 *
 *  Created on: Dec 27, 2025
 *      Author: Dev-Laptop2
 */

#ifndef RELAY_CONTROL_H_
#define RELAY_CONTROL_H_

#include "main.h"
#include "strcture.h"

#define CMD_RELAY_ON  0x01
#define CMD_RELAY_OFF 0x02

/* Relay APIs */
void Relay_Init(void);
void Relay_ON(void);
void Relay_OFF(void);
void Relay_ProcessCommand(const command_t *cmd);

#endif

