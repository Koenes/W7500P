/**
  ******************************************************************************
  * @file    I2C/I2C_EEPROM_24LC02B/main.c 
  * @author  IOP Team
  * @version V1.0.0
  * @date    26-AUG-2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"
#include <stdio.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_SIZE 9
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;
I2C_ConfigStruct conf;
///                   memaddress,data0,data1 data2,data3,data4,data5,data6,data7
uint8_t Transmit_Data[MAX_SIZE]={0x00, 0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x11,0x22};
uint8_t Recv_Data[MAX_SIZE];
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void delay_function(int time);


/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main()
{
    int i;

    /*System clock configuration*/
    SystemInit();
    /* Configure UART2 */
   	S_UART_Init(115200);
    conf.scl = I2C_PA_9;
    conf.sda = I2C_PA_10;
    
    I2C_Init(&conf);
    
    //============ Write ==============
    I2C_Write(&conf, 0xa0, &Transmit_Data[0], MAX_SIZE);
    
    delay_function(4000);
    
    //========= Read =============
    //Write memory address
    I2C_Write(&conf, 0xA0, &Transmit_Data[0], 1);
    
    delay_function(4000);
    //Read data
    I2C_Read(&conf, 0xA0, &Recv_Data[0], MAX_SIZE - 1);
    
    printf("Recv data : ");
    for(i=0; i<MAX_SIZE - 1; i++)
    {
        printf("0x%x ", Recv_Data[i]);
    }
    printf("\r\n");
    
    
}

void delay_function(int time)
{
    int i;
    
    for(i=0; i<time; i++)
    {
        __NOP();
    }
    
}


