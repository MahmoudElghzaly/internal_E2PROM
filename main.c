
#define PART_TM4C123GH6PM
#define SCB_CPAC (*((volatile unsigned int*)0xE000ED88))
	
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/eeprom.h"
#include "utils/uartstdio.h"
#define MAX_SIZE  20

#define ID_1    1
#define ID_2    2
#define ID_3    3
#define ID_4 		4
#define ID_5		5
#define MAX_ELEMENT_NO 5

#define Start_Address   0x0000
#define Address_step(element_size)   element_size+4
typedef struct E2PROM_Def
{
	uint8_t ID;
	uint16_t start_address;
	
	uint8_t act_size;
	
}def;  

def EE_var[5]= {{ID_1,Start_Address,0},
{ID_2,Start_Address+Address_step(MAX_SIZE),0},
{ID_3,Start_Address+2*Address_step(MAX_SIZE),0},
{ID_4,Start_Address+3*Address_step(MAX_SIZE),0},
{ID_5,Start_Address+4*Address_step(MAX_SIZE),0}};

typedef struct E2PROM_DATA
{
    uint16_t size;
    uint8_t data[MAX_SIZE];
}E2data;

 
 void W_data(uint16_t ID, uint8_t* data, uint8_t size){
	 //uint8_t arr[
	 E2data write;
	 write.size=size;
	 for(uint8_t i=0;i<= size-1;i++){
		write.data[i]=data[i];
/*
write.data[i]=*data;
		 data++;
*/		 
	 }
	 for (int i=0; i<MAX_ELEMENT_NO; i++){
		 if( EE_var[i].ID==ID){
				EE_var[i].act_size= size;
				EEPROMProgram((uint32_t *)&write, EE_var[i].start_address,sizeof(write));
				break;
		 }  
 }
 }
 
 void R_data(uint8_t ID){
	 E2data read = {0,""};
	 for (uint8_t i=0; i<MAX_ELEMENT_NO; i++){
		if( EE_var[i].ID==ID){
				EEPROMRead((uint32_t *)&read, EE_var[i].start_address,sizeof(read));
				break;
 }
 }
 }
void E2PROM_init(){
	  /* EEPROM SETTINGS */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0); // EEPROM activate
    EEPROMInit(); // EEPROM start
		E2data read;
		for(uint8_t i=0;i<MAX_ELEMENT_NO;i++){
			EEPROMRead((uint32_t *)&read, EE_var[i].start_address,sizeof(read));
			EE_var[i].act_size=read.size; 
		}
	
}
 uint32_t e2size,e2block,structsize;


int main(void) 
{
		uint8_t ID;
		uint8_t data[MAX_SIZE];
		uint8_t size;
		
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ); // islemcimizi 80 Mhz'e ayarliyoruz.
		E2PROM_init();
		W_data(ID,data,size);
		R_data(ID);
	
	
		structsize = sizeof(struct E2PROM_DATA); 
    e2size = EEPROMSizeGet(); // Get EEPROM Size 
    e2block = EEPROMBlockCountGet(); // Get EEPROM Block Count
	
		
 
while(1)
 {
	 
 }
 
}

void SystemInit(){
SCB_CPAC |= 0x00F00000;
}
