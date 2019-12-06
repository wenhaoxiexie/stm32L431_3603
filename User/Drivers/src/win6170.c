#include "win6170.h"
#include "delay.h"
#include "stdio.h"
#include "ssd1305.h"
#include "flash.h"
#include "74hc595.h"
#include "menu.h"

extern KEY_STATE get_cur_number;
extern uint8_t prying_flag;

void horn_powerOff(void)
{
	HAL_GPIO_WritePin(AUDData_GPIO_Port, AUDData_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(VWIN6_GPIO_Port,VWIN6_Pin,GPIO_PIN_RESET);
}

void horn_powerOn(void)
{
	HAL_GPIO_WritePin(VWIN6_GPIO_Port,VWIN6_Pin,GPIO_PIN_SET);
}

void set_win6170(uint8_t addr)
{
	int i;
	HAL_GPIO_WritePin(AUDData_GPIO_Port, AUDData_Pin, GPIO_PIN_RESET);
	sys_delay_us(5000);
	for(i=0;i<8;i++)
	{
		if(addr&0x01)
		{
			HAL_GPIO_WritePin(AUDData_GPIO_Port, AUDData_Pin, GPIO_PIN_SET);
			sys_delay_us(1200);
			HAL_GPIO_WritePin(AUDData_GPIO_Port, AUDData_Pin, GPIO_PIN_RESET);
			sys_delay_us(400);
		}else{
			HAL_GPIO_WritePin(AUDData_GPIO_Port, AUDData_Pin, GPIO_PIN_SET);
			sys_delay_us(400);
			HAL_GPIO_WritePin(AUDData_GPIO_Port, AUDData_Pin, GPIO_PIN_RESET);
			sys_delay_us(1200);
		}
		addr>>=1;				
	}
	HAL_GPIO_WritePin( AUDData_GPIO_Port, AUDData_Pin, GPIO_PIN_SET);
	
}

void sys_voice_set(uint8_t addr)
{
	set_win6170(addr);
		// ±¨¾¯ÒôÓÅÏÈ
	if(prying_flag)
	{
		sys_delay_us(100000);
		set_win6170(0XEF);
		sys_delay_us(2000);
		set_win6170(3);
		sys_delay_us(2000);
		set_win6170(0XF2);
		sys_delay_us(2000);
	}
}


uint8_t vol_set(void)
{
	uint16_t delay_count;
	
START:
	display_subsubmenu_sys();
	send_bytes(KEY_VOICE);
	APT_KeyEnableSel(KDR0_CH_1_2_10_11_EN,KDR1_CH_1_2_10_11_EN);
RECALL:
	delay_count=1300;

	voice_repeat(10);
	
	do{
		if(get_cur_number.key_prees==1)
		{
			get_cur_number.key_prees=0;
			delay_count=1300;
			switch(get_cur_number.number){
				case 1:
					set_win6170(0xEF);
					display_set_sucess();
					sys_delay_us(500000);
					get_cur_info->cur_vol_size=0xEF;
					stm_flash_erase_write(ADDR_FLASH_PAGE_100,(uint64_t*)get_cur_info,CUR_INDEX_SIZE);
					goto START;
				case 2:
					set_win6170(0xE7);
					display_set_sucess();
					sys_delay_us(500000);
					get_cur_info->cur_vol_size=0xE7;
					stm_flash_erase_write(ADDR_FLASH_PAGE_100,(uint64_t*)get_cur_info,CUR_INDEX_SIZE);
					goto START;
				case 3:
					set_win6170(0xE2);
					display_set_sucess();
					sys_delay_us(500000);
					get_cur_info->cur_vol_size=0xE2;
					stm_flash_erase_write(ADDR_FLASH_PAGE_100,(uint64_t*)get_cur_info,CUR_INDEX_SIZE);
					goto START;
				case 4:
					set_win6170(0xE0);
					display_set_sucess();
					sys_delay_us(500000);
					get_cur_info->cur_vol_size=0xE0;
					stm_flash_erase_write(ADDR_FLASH_PAGE_100,(uint64_t*)get_cur_info,CUR_INDEX_SIZE);
					goto START;
				case 10:
					return LOCK_OK;
				case 11:
						goto RECALL;
				default:
					break;
			}
		}
		sys_delay_us(10000);
	}while(--delay_count);

	return LOCK_OUTTIME;

}

