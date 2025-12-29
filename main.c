/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "strcture.h"
#include "relay_control.h"
#include "dht11_driver.h"
#include "queue.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t rx;
provision_t g_provision;
command_t   g_command;
config_t    g_config;
#define MAX_PAYLOAD_SIZE  64

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

/* Definitions for UART_TASK */
osThreadId_t UART_TASKHandle;
const osThreadAttr_t UART_TASK_attributes = {
  .name = "UART_TASK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SENSOR_TASK */
osThreadId_t SENSOR_TASKHandle;
const osThreadAttr_t SENSOR_TASK_attributes = {
  .name = "SENSOR_TASK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TEMP_TASK */
osThreadId_t TEMP_TASKHandle;
const osThreadAttr_t TEMP_TASK_attributes = {
  .name = "TEMP_TASK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TEMP_UART_TASK */
osThreadId_t TEMP_UART_TASKHandle;
const osThreadAttr_t TEMP_UART_TASK_attributes = {
  .name = "TEMP_UART_TASK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Uart_queue */
osMessageQueueId_t Uart_queueHandle;
const osMessageQueueAttr_t Uart_queue_attributes = {
  .name = "Uart_queue"
};
/* Definitions for Temp_queue */
osMessageQueueId_t Temp_queueHandle;
const osMessageQueueAttr_t Temp_queue_attributes = {
  .name = "Temp_queue"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM6_Init(void);
void UART_Task(void *argument);
void Sensor_Task(void *argument);
void Temp_task(void *argument);
void Temp_Uart_Task(void *argument);
void Handle_Command_Frame(frame_header_t *header,
                          uint8_t *payload,
                          uint16_t payloadLen);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

  // Initialize DHT11 (pin example PA8)
    dht11_init(GPIOA, GPIO_PIN_8, &htim6);

   Relay_Init();

   HAL_UART_Receive_IT(&huart2, &rx, 1);

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of Uart_queue */
  Uart_queueHandle = osMessageQueueNew (256, sizeof(uint8_t), &Uart_queue_attributes);

  /* creation of Temp_queue */
  Temp_queueHandle = osMessageQueueNew (10, sizeof(dht11_data), &Temp_queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of UART_TASK */
  UART_TASKHandle = osThreadNew(UART_Task, NULL, &UART_TASK_attributes);

  /* creation of SENSOR_TASK */
  SENSOR_TASKHandle = osThreadNew(Sensor_Task, NULL, &SENSOR_TASK_attributes);

  /* creation of TEMP_TASK */
  TEMP_TASKHandle = osThreadNew(Temp_task, NULL, &TEMP_TASK_attributes);

  /* creation of TEMP_UART_TASK */
  TEMP_UART_TASKHandle = osThreadNew(Temp_Uart_Task, NULL, &TEMP_UART_TASK_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 84 - 1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TEMP_PIN_GPIO_Port, TEMP_PIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Relay_Pin */
  GPIO_InitStruct.Pin = Relay_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Relay_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TEMP_PIN_Pin */
  GPIO_InitStruct.Pin = TEMP_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TEMP_PIN_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

int _write(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    ITM_SendChar(*ptr++);
  }
  return len;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        osMessageQueuePut(Uart_queueHandle, &rx, 0, 0);

        /* Restart RX for next byte */
       HAL_UART_Receive_IT(&huart2, &rx, 1);
    }
}
void Handle_Command_Frame(frame_header_t *header,
                          uint8_t *payload,
                          uint16_t payloadLen)
{
    /* Copy header */
    memcpy(&g_command.header, header, sizeof(frame_header_t));

    /* Validate payload length */
    if (payloadLen < sizeof(command_type_t))
    {
        printf("Invalid command payload length\r\n");
        return;
    }

    /* Copy command */
    memcpy(&g_command.command,
           payload,
           sizeof(command_type_t));

    /* If actuator data exists */
    if (payloadLen >= sizeof(command_type_t) + sizeof(actuator_t))
    {
        memcpy(&g_command.actuator,
               payload + sizeof(command_type_t),
               sizeof(actuator_t));
    }

    /* Process command */
    Relay_ProcessCommand(&g_command);

    printf("Command Type : 0x%02X\r\n",
           g_command.command.command_type);
}

void Handle_Provision_Frame(frame_header_t *header,uint8_t *payload,uint16_t payloadLen)
{
    memcpy(&g_provision.header, header, sizeof(frame_header_t));

    if (payloadLen < sizeof(provision_t))
    {
        printf("Invalid provision payload\r\n");
        return;
    }

    memcpy(&g_provision.command, payload,sizeof(g_provision.command));
    memcpy(&g_provision.actuator, payload,sizeof(g_provision.actuator));
    memcpy(&g_provision.sensor, payload,sizeof(g_provision.sensor));
    memcpy(&g_provision.padding,payload,sizeof(g_provision.padding));

    printf("Provision Frame Received\r\n");
}

void Handle_Config_Frame(frame_header_t *header,uint8_t *payload,uint16_t payloadLen)
{
	//copy header
	memcpy(&g_config.header,header,sizeof(frame_header_t));

	if (payloadLen < sizeof(config_t))
	    {
	        printf("Invalid config payload\r\n");
	        return;
	    }

	memcpy(&g_config.interval,payload,sizeof(g_config.interval));
	memcpy(&g_config.sensor,payload,sizeof(g_config.sensor));

}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_UART_Task */
/**
  * @brief  Function implementing the Task1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_UART_Task */
void UART_Task(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
	 uint8_t data;

	    frame_header_t rx_header;
	    uint8_t headerIndex = 0;

	    uint8_t payload[MAX_PAYLOAD_SIZE];
	    uint16_t payloadIndex = 0;

	    uint8_t eeCount = 0;

	    enum
	    {
	        RX_HEADER,
	        RX_PAYLOAD
	    } rxState = RX_HEADER;

	    for (;;)
	    {
	        if (osMessageQueueGet(Uart_queueHandle, &data, NULL, osWaitForever) == osOK)
	        {
	            /* ================= EOF DETECTION ================= */
	            if (data == 0xEE)
	            {
	                eeCount++;
	                if (eeCount == 2)
	                {
	                    printf("\r\n--- FRAME RECEIVED ---\r\n");
	                    printf("Version    : %d\r\n", rx_header.version);
	                    printf("Frame Type : 0x%02X\r\n", rx_header.frame_type);
	                    printf("Device ID  : %d\r\n", rx_header.device_id);
	                    printf("Payload Len: %d\r\n", payloadIndex);

	                    /* ========== PROCESS FRAME ========== */
	                    switch (rx_header.frame_type)
	                    {
	                        case eFrame_Type_Command:
	                        	Handle_Command_Frame(&rx_header,payload,payloadIndex);
	                            break;

	                        case eFrame_Type_Provision:
	                        	 Handle_Provision_Frame(&rx_header,payload,payloadIndex);                        	    printf("Provision Frame Received\r\n");
	                            break;

	                        case eFrame_Type_Config:
	                        	Handle_Config_Frame(&rx_header,payload,payloadIndex);
	                            break;

	                        default:
	                            printf("Unknown Frame Type\r\n");
	                            break;
	                    }

	                    printf("--- FRAME DONE ---\r\n\r\n");

	                    /* ========== RESET STATE ========== */
	                    rxState = RX_HEADER;
	                    headerIndex = 0;
	                    payloadIndex = 0;
	                    eeCount = 0;
	                    memset(&rx_header, 0, sizeof(rx_header));
	                    memset(payload, 0, sizeof(payload));

	                    continue;
	                }
	                continue;
	            }
	            else
	            {
	                eeCount = 0;
	            }

	            /* ================= HEADER RECEIVE ================= */
	            if (rxState == RX_HEADER)
	            {
	                ((uint8_t *)&rx_header)[headerIndex++] = data;

	                if (headerIndex == sizeof(frame_header_t))
	                {
	                    rxState = RX_PAYLOAD;
	                }
	            }
	            /* ================= PAYLOAD RECEIVE ================= */
	            else if (rxState == RX_PAYLOAD)
	            {
	                if (payloadIndex < MAX_PAYLOAD_SIZE)
	                {
	                    payload[payloadIndex++] = data;
	                }
	            }
	        }
	    }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_Sensor_Task */
/**
* @brief Function implementing the Task2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Sensor_Task */
void Sensor_Task(void *argument)
{
  /* USER CODE BEGIN Sensor_Task */
  /* Infinite loop */
	for (;;)
	    {
//	        /* Provision Data */
//	        printf("\n--- Provision Frame ---\n");
//	        printf("Frame Type      : 0x%02X\r\n", g_provision.header.frame_type);
//	        printf("Device ID       : %d\n", g_provision.header.device_id);
//	        printf("Command Type    : %d\n", g_provision.command.command_type);
//	        printf("Interval Time   : %lu\n", g_provision.interval.interval_time);
//	        printf("Temp Threshold  : %d\n", g_provision.sensor.temperature_threshold);
//	        printf("Humidity Thres  : %d\n", g_provision.sensor.humidity_threshold);
//	        printf("Fan Speed       : %d\n", g_provision.actuator.fan_default_speed);
//
//	        /* Command Data */
//	        printf("\n--- Command Frame ---\n");
//	        printf("Frame Type      : 0x%02X\r\n", g_command.header.frame_type);
//	        printf("Command Type    : %d\n", g_command.command.command_type);
//	        printf("AC Default Temp : %d\n", g_command.actuator.ac_default_temp);
//
//	        osDelay(2000);
	    }

  /* USER CODE END Sensor_Task */
}

/* USER CODE BEGIN Header_Temp_task */
/**
* @brief Function implementing the TEMP_TASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Temp_task */
void Temp_task(void *argument)
{
  /* USER CODE BEGIN Temp_task */
  /* Infinite loop */
	dht11_data dht;
		    int curr_temp;
		    int prev_temp = -100;  // invalid initial value

		    dht11_data msg;

		    while (1)
		    {

		        dht = dht11_data_read();

		        if (!dht.error)
		        {

		            curr_temp = dht.temperature;  // no float needed

		            if(curr_temp != prev_temp)   // just check for change
		            {

		                msg.temperature = dht.temperature;
		                msg.humidity    = dht.humidity;


		                osMessageQueuePut(Temp_queueHandle, &msg, 0, 0);
		                prev_temp = curr_temp;
		            }
		        }

		        osDelay(2000);
		    }
  /* USER CODE END Temp_task */
}

/* USER CODE BEGIN Header_Temp_Uart_Task */
/**
* @brief Function implementing the TEMP_UART_TASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Temp_Uart_Task */
void Temp_Uart_Task(void *argument)
{
  /* USER CODE BEGIN Temp_Uart_Task */
  /* Infinite loop */
	        dht11_data  rx_msg;
		    char uart_buf[50];
		    uint16_t len;

		    while (1)
		    {

		        if (osMessageQueueGet(Temp_queueHandle, &rx_msg, NULL,osWaitForever) == osOK)
		        {
		        	len = snprintf(uart_buf, sizeof(uart_buf),
		        	                           "Temperature: %d C, Humidity: %d %%\r\n",
		        	                           rx_msg.temperature,
		        	                           rx_msg.humidity);

		        	            // Send via UART
		        	            HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, len, HAL_MAX_DELAY);

		        	            // Debug print also works now
		        	            printf("DEBUG: Temperature = %d C, Humidity = %d %%\n",
		        	                   rx_msg.temperature,
		        	                   rx_msg.humidity);
		        }
		    }
  /* USER CODE END Temp_Uart_Task */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM5 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM5)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
