/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "string.h"
#include<stdio.h>
#include<math.h>
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim14;
TIM_HandleTypeDef htim17;

UART_HandleTypeDef huart1;
uint8_t aTxBuffer1[] = "RXNE wake-up successful";


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
 void clean(char* buff,int val){
	 for(int i=0 ;i<val;i++)buff[i]=0;
 }
//static void MX_TIM1_Init(void);
//static void MX_TIM3_Init(void);
//static void MX_TIM14_Init(void);
//static void MX_TIM17_Init(void);
int getHexVal(char c);
void send(char* hex);
void delay (int i){
	while(i>0){
	TIM16->SR &=0xfe;
	  TIM16->CNT=0;
						while((!((TIM16->SR)&0x01)) );
			 
					 TIM16->CNT=0;
	i--;
	}
}
 

void sendcommand(char* command ,char* res,int time){
	  char response[100];
		while(strstr(res,response)==NULL){
			clean(response,100);
	HAL_UART_Transmit(&huart1, (uint8_t*) command ,strlen(command), 30);
		HAL_UART_Receive(&huart1,(uint8_t*)response,100,5000);
	 //HAL_UART_Transmit(&huart1, (uint8_t*) response ,strlen(response), 30);
		}
		//HAL_UART_Transmit(&huart1, (uint8_t*)response, COUNTOF(response), 5000);	
}
void chekresponse(char* respons){
	char receive[100];
	HAL_UART_Receive(&huart1,(uint8_t*)receive,100,10000);
		HAL_UART_Transmit(&huart1, (uint8_t*) receive ,100, 5000);
 	if(strstr(respons,receive)!= NULL){
				HAL_UART_Transmit(&huart1, (uint8_t*)"yess",4, 5000);
	}
}
  int main(void)
{
	HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

	
	
__HAL_RCC_USART1_CONFIG(RCC_USART1CLKSOURCE_HSI);
RCC->APB2ENR |= RCC_APB2ENR_TIM16EN; /* (1) */
RCC->AHBENR |= RCC_AHBENR_GPIOAEN; /* (2) */
RCC->AHBENR |= RCC_AHBENR_GPIOBEN; /* (2) */
RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; /* (1) */

//GPIOB->MODER = GPIO_MODER_MODER2_0;
//GPIOB->OSPEEDR=GPIO_OSPEEDR_OSPEEDR0_Msk;
	//GPIOB->PUPDR=GPIO_PUPDR_PUPDR0_1;
//	
//	GPIOA->MODER = GPIO_MODER_MODER4_0|GPIO_MODER_MODER5_0|GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0;
// 
//	GPIOA->PUPDR=GPIO_PUPDR_PUPDR0_1|GPIO_PUPDR_PUPDR1_1 |GPIO_PUPDR_PUPDR4_1|GPIO_PUPDR_PUPDR5_1|GPIO_PUPDR_PUPDR6_1
//	|GPIO_PUPDR_PUPDR7_1|GPIO_PUPDR_PUPDR8_1|GPIO_PUPDR_PUPDR9_1|GPIO_PUPDR_PUPDR11_1;
TIM16->PSC |=1; /* (1) */
TIM16->ARR = 500- 1; /* (2) */
TIM16->CCR1 = 500- 1; /* (3) */  
TIM1->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1; /* (4) */
TIM16->CCER |= TIM_CCER_CC1E; /* (5)*/
TIM16->BDTR |= TIM_BDTR_MOE; /* (6) */
TIM16->CR1 |= TIM_CR1_CEN; /* (7) */

TIM1->PSC |=8; /* (1) */
TIM1->ARR = 60000- 1; /* (2) */
TIM1->CCR1 = 60000- 1; /* (3) */
TIM1->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1; /* (4) */
TIM1->CCER |= TIM_CCER_CC1E; /* (5)*/
TIM1->BDTR |= TIM_BDTR_MOE; /* (6) */
TIM1->CR1 |= TIM_CR1_CEN; /* (7) */



 
char receive[100];
char* buf5;
 char* bufpax;
  bufpax = (char*) malloc (200);
 buf5 = (char*) malloc (200);
 
huart1.Instance = USART1;
HAL_UART_DeInit(&huart1); 
//huart1.Init.BaudRate   = 9600;//pax_ethernet
huart1.Init.BaudRate   = 115200;//pax_rs232
huart1.Init.WordLength = UART_WORDLENGTH_8B;
huart1.Init.StopBits   = UART_STOPBITS_1;
huart1.Init.Parity     = UART_PARITY_NONE; 
huart1.Init.Mode       = UART_MODE_TX_RX; 
HAL_UART_Init(&huart1) ;


//sprintf(hex2,"54454A415241545F42414E4B30323030303030303030303430303030303030303030303130303030313220202020202020202020202020202020202020202020202000006EB1C5B923FAF77A");

NVIC_EnableIRQ(SysTick_IRQn); /* (1) */
NVIC_SetPriority(SysTick_IRQn,2); /* (2) */

TIM1->SR &=0xfe;
// while(1){

// 
// 
// }		
 
 
  char post[6];
		char* data="salam,eshgham";
		uint8_t z=0x1a; 
  		GPIOA->ODR=0x10; 

 //HAL_UART_Transmit(&huart1, (uint8_t*)"ATZ0\n", COUNTOF("ATZ0\n"), 5000);
// HAL_UART_Transmit(&huart1, (uint8_t*)"ATE0\n", COUNTOF("ATE0\n"), 5000);
  	sendcommand("ATE0\n" ,"OK",1000);
 	sendcommand("AT\n" ,"OK",1000);
	sendcommand("AT+COPS=4,2,\"43235\"\n","OK",8000);
	sendcommand("AT+COPS?","+COPS: 1,2,\"43235\"",8000);


 HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CPIN?\n", COUNTOF("AT+CPIN?\n"), 5000);
	HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CREG?\n", COUNTOF("AT+CREG?\n"), 5000);
	HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CGACT?\n", COUNTOF("AT+CGACT?\n"), 5000);
 /*HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CMEE=1\n", COUNTOF("AT+CMEE=1\n"), 5000);
 //HAL_Delay(1000);		
 HAL_UART_Receive(&huart1,(uint8_t*)receive,100,3000);
 HAL_UART_Transmit(&huart1,(uint8_t*)receive,100,3000);
 //clean (receive,100);
  //HAL_UART_Transmit(&huart1,(uint8_t*)receive,100,3000);
 while(strstr(receive,"OK")== NULL){
   clean (receive,100);
	 HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CGATT=1\n", COUNTOF("AT+CGATT=1\n"), 5000);
	 HAL_UART_Receive(&huart1,(uint8_t*)receive,100,30);
	 HAL_UART_Transmit(&huart1,(uint8_t*)receive,100,3000);
 }
 */
 
	sendcommand("AT+CMEE=1\n" ,"OK",5000);
	sendcommand("AT+CSTT=\"bluevia.movistar.es\"\n" ,"OK",5000);
	sendcommand("AT+CIICR\n" ,"OK",5000);
	
//	 HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CSTT=\"bluevia.movistar.es\"\n", COUNTOF("AT+CSTT=\"bluevia.movistar.es\"\n"), 5000);
//HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CIICR\n", COUNTOF("AT+CIICR\n"), 5000);
// HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CIFSR\n", COUNTOF("AT+CIFSR\n"), 5000);
//  
 

char socket[45]="AT+CIPSTART=\"TCP\",\"www.fdli.ir\",\"80\"\n";
		char header[93]= "POST /input2.php HTTP/1.1\r\nHost: www.fdli.ir\r\nContent-Type:application/json;\r\nContent-Length:";

while (1)
  {
 for(int i=0;i<200;i++)bufpax[i]=0;
		// HAL_Delay(1000);	 
		HAL_UART_Transmit(&huart1, (uint8_t*) socket ,45, 2000);	
		//	 HAL_Delay(1000);	
	 	HAL_UART_Receive(&huart1,(uint8_t*)bufpax,200,3000);
		 
 //	HAL_UART_Transmit(&huart1,(uint8_t*) bufpax,200, 5000);	 
	 	if(strstr(bufpax,"ALREADY")!= NULL){
			//	HAL_UART_Transmit(&huart1, (uint8_t*)"yess",4, 5000);
 
 
	HAL_Delay(1000);
	HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CIPSEND\n", COUNTOF("AT+CIPSEND\n"), 5000);
				HAL_UART_Receive(&huart1,(uint8_t*)buf5,COUNTOF(buf5),3000);
				if(strstr(buf5,">")!= NULL){
				 
				HAL_UART_Transmit(&huart1, (uint8_t*) header , strlen(header), 5000);
				sprintf(post,"%d\r\n\r\n",strlen(data));
				HAL_UART_Transmit(&huart1, (uint8_t*) post , strlen(post), 5000);
				HAL_UART_Transmit(&huart1, (uint8_t*) data , strlen(data), 5000); 
				HAL_UART_Transmit(&huart1, &z,2, 5000);	
				}
}
		else if(strstr(bufpax,"+CME")){
//		HAL_Delay(1000);	
//				
//	HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CREG?\n", COUNTOF("AT+CREG?\n"), 5000);
//	HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CGACT?\n", COUNTOF("AT+CGACT?\n"), 5000);
//	HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CMEE=1\n", COUNTOF("AT+CMEE=1\n"), 5000);
//  HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CGATT=1\n", COUNTOF("AT+CGATT=1\n"), 5000);
//	HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CSTT=\"bluevia.movistar.es\"\n", COUNTOF("AT+CSTT=\"bluevia.movistar.es\"\n"), 5000);
//	HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CIICR\n", COUNTOF("AT+CIICR\n"), 5000);
//	HAL_UART_Transmit(&huart1, (uint8_t*)"AT+CIFSR\n", COUNTOF("AT+CIFSR\n"), 5000);
 
		
		} 
 }//end while
	}//end main
 
		
 
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

 
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %drn", file, line) */
  /* USER CODE END 6 */

}

#endif
int getHexVal(char c)
{
  if(c >= '0' && c<= '9')
    return c - '0';
  else if(c >= 'a' && c<= 'f')
    return c - 'a' + 10;
  else if(c >= 'A' && c<= 'F')
    return c - 'A' + 10;
  else
    return -1;//error
}

void send(char* hex){
	

int hexLen = strlen(hex);
char asciiStr[hexLen/2+1];
for(int i = 0; i < hexLen; i +=2)
{
  asciiStr[i/2] = getHexVal(hex[i])*16 + getHexVal(hex[i+1]);
	HAL_UART_Transmit(&huart1, (uint8_t*)(asciiStr+i/2), 1, 5000);
}

}
/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
