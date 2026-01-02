/*
 * dht11_driver.h
 *
 *  Created on: Dec 27, 2025
 *      Author: Dev-Laptop2
 */

#ifndef DHT11_DRIVER_H
#define DHT11_DRIVER_H

#include "main.h"  // Include the main header for HAL and other dependencies
#include <stdbool.h> // Include for the boolean type


/**
 * @brief DHT11 data structure
 */
typedef struct {
	 uint8_t humidity;      // 0–100 %
	 uint8_t temperature;   // 0–80 °C
    bool error;          // Indicates if there was an error
} dht11_data;


// Public API
void dht11_init(GPIO_TypeDef *gpio_port, uint16_t gpio_pin, TIM_HandleTypeDef *tim); // Initializes the dht11
dht11_data dht11_data_read(void); // Reads data from dht11

#endif // DHT11_DRIVER_H
#ifndef INC_DHT11_DRIVER_H_
#define INC_DHT11_DRIVER_H_



#endif /* INC_DHT11_DRIVER_H_ */
