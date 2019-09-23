#include "nrf52.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"

#define LED_0          17
#define KEY_1 				 13
#define KEY_2 				 14
#define TCH            12
 
void Delay(uint32_t temp)
{
  for(; temp!= 0; temp--);
} 
 
 void LED_Init(void)
{
  // Configure LED-pins as outputs
  nrf_gpio_cfg_output(LED_0);
	nrf_gpio_cfg_input(12, NRF_GPIO_PIN_PULLUP);
}

void LED1_Open(void)
{
	nrf_gpio_pin_clear(LED_0);
}

void LED1_Close(void)
{
	nrf_gpio_pin_set(LED_0);
}

void LED1_Toggle(void)
{
  nrf_gpio_pin_toggle(LED_0);
}
 
void KEY_Init(void)
{
  nrf_gpio_cfg_input(13,NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(14,NRF_GPIO_PIN_PULLUP);
}

uint8_t TCH_Down(void)
{
	 if(nrf_gpio_pin_read(TCH) ==1)
	 {
		    /*延时消抖*/
	  	Delay(10000);		
	   	if(nrf_gpio_pin_read(TCH)== 1 )  
			{	 
				/*等待按键释放 */
				while(nrf_gpio_pin_read(TCH)== 1 ){LED1_Open();}
			 	return 	0	; 
			}
			else
				return 1;
	 }
	 else
		return 1;
 }

uint8_t KEY1_Down(void)
{			
		  /*检测是否有按键按下 */
   	if( nrf_gpio_pin_read(KEY_1)== 0 ) 
	  {	   
	 	  /*延时消抖*/
	  	Delay(10000);		
	   	if(nrf_gpio_pin_read(KEY_1)== 0 )  
			{	 
				/*等待按键释放 */
				while(nrf_gpio_pin_read(KEY_1)== 0 ){LED1_Open();}
			 		return 	0	; 
			}
			else
					return 1;
		}
		else
			return 1;
}


uint8_t KEY2_Down(void)
{			
		  /*检测是否有按键按下 */
   	if( nrf_gpio_pin_read(KEY_2)== 0 ) 
	  {	   
	 	  /*延时消抖*/
	    Delay(10000);		
	   	if(nrf_gpio_pin_read(KEY_2)== 0 )  
			{	 
				/*等待按键释放 */
				while(nrf_gpio_pin_read(KEY_2)== 0 );   
			 	return 	0	; 
			}
			else
				return 1;
		}
	  else
			return 1;
}



int main()
{
	KEY_Init();
	LED_Init();
	while(1)
	{
		LED1_Close();
		if(KEY1_Down() == 0 || TCH_Down() == 0)
		{
		
		}
	}
}

