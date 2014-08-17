#include <stdio.h>

#include "linkport.h"
#include "stm32f10x_conf.h"
#include "img.h"
#include "gfx_2d.h"
#include "gfx_3d.h"
#include "hw_control.h"

#define Breset BRR
#define Bset BSRR



int x;






void boot()
{
  LINK_send_key(0x9b00);
  
  LINK_send_key(0xa800);

  LINK_send_key(0xa800);

  LINK_send_key(0xad00);

  LINK_send_key(0xa200);

  LINK_send_key(0xa700);

  LINK_send_key(0xa000);

  LINK_send_key(0xfe68);

  LINK_send_key(0xfe68);

  LINK_send_key(0xfe68);

}


RCC_ClocksTypeDef ClksFreq;
void SysClkSetHSI_4xPLLMul (uint32_t PLLMul ) {
      if (PLLMul > RCC_PLLMul_12) {
            FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
            // Flash 2 wait state for freq > 4x12 48MHz
            FLASH_SetLatency(FLASH_Latency_2);
      }
      else if (PLLMul > RCC_PLLMul_6) {
            FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
            // Flash 1 wait state for freq > 4x6 24MHz
            FLASH_SetLatency(FLASH_Latency_1);
      }
      // PLL provides frequency multiplier of (HSI/2) i.e. 4MHz x ...
      RCC_PLLConfig(RCC_PLLSource_HSI_Div2, PLLMul);
      // Enable PLL
      RCC_PLLCmd(ENABLE);
      // Wait till PLL is ready
      while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
      // Select PLL as system clock source
      RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
      // Wait till PLL is used as system clock source
      while (RCC_GetSYSCLKSource() != 0x08);
      // AHB, AP2 and AP1 clock are necessary for the peripherals to function
      // HCLK for AHB = SYSCLK (max is SYSCLK, up to 72MHz)
      RCC_HCLKConfig(RCC_SYSCLK_Div1);
      // PCLK2 for APB2 = HCLK (max is SYSCLK, up to 72MHz)
      RCC_PCLK2Config(RCC_HCLK_Div1);
      if (PLLMul > RCC_PLLMul_9) {
            // PCLK1 for APB1 = HCLK/2 (> 4x9MHz max of 36MHz, use slower clock)
            RCC_PCLK1Config(RCC_HCLK_Div2);
      }
      else {
            // PCLK1 for APB1 = HCLK (HCLK <= 36MHz)
            RCC_PCLK1Config(RCC_HCLK_Div1);
      }
      RCC_GetClocksFreq(&ClksFreq); // update SYSCLK, HCLK, PCLK1 and PCLK2 in ClksFreq
}



    int main(void)
  { 


  
  SysClkSetHSI_4xPLLMul(RCC_PLLMul_16);
 // Set_System();
 // Set_USBClock();
 // USB_Interrupts_Config();
 // USB_Init();
  LINK_init();
  
  
  LINK_RED_low
   for(volatile int x = 0; x < 1000000; x++);
   LINK_RED_high

  HW_CONTROL_init();
  HW_CONTROL_ENABLE_CALC();
  HW_CONTROL_CLICK_ON_KEY();

  for(volatile int x = 0; x < 9000000; x++);

  //boot();
  
  //while(!LINK_check_password());
  LINK_send_os();


  
//  uint64_t bin = 0;
//  for(int i = 512; i < 768; i++)
//      {
//          framebuffer[i] = 0xff;
//
//      }
//
//  for(int i = 2048; i < 4096; i++)
//  {
//     framebuffer[i % 96][i / 96] = 150;
//  }
//  for(int i = 4096; i < 6144; i++)
//  {
//     framebuffer[i % 96][i / 96] = 190;
//  }
//    

    for(int x = 0; x < 96; x++)
    {
    for(int y = 0; y < 64; y++)
    {
      framebuffer[x][y]=img1
      [y*96+x];
    }
    }
    gfx_3d_init();

int framecount = 0;

  while         (1)
  {   
  framecount ++;
      //if(framecount % 6 == 0)
      {
      framecount = 0;
      gfx_3d_tick();
      char c[] = "Trololoxyzabc";
      gfx_2d_string(c,sizeof(c),10,10,-2,-1);
      }
      LINK_transfer_framedata();
  }
      while (1)
      {
//     for(int i = 256; i < 512; i++)
//      {
//          framebuffer[i] = 0b10101010;
//          i++;
//          framebuffer[i] = 0b01010101;
//      }
//      LINK_transfer_framedata();
//
//       for(int i = 256; i < 512; i++)
//      {
//          framebuffer[i] = 0b01010101;
//          i++;
//          framebuffer[i] = 0b10101010;
//      }
//      LINK_transfer_framedata();


//      for(int i = 0; i < 768; i++)
//      {
//          framebuffer[i] = rand();
//          if(i % 32 == 0)
//          {
//              LINK_transfer_framedata();
//          }
//      }
//      for(int i = 0; i < 768; i++)
//      {
//          framebuffer[i] = screen[(i%64)*12+i/64];
//          if(i % 32 == 0)
//          {
//              LINK_transfer_framedata();
//          }
//      }
    
//    for(int i = 0; i < 64; i++)
//    {
//        framebuffer[i] = bin >> 24;
//        bin ++;
//    }
//    bin -= 64;
//
//    for(int i = 0; i < 64; i++)
//    {
//        framebuffer[i + 64] = bin >> 16;
//        bin ++;
//    }
//    bin -= 64;
//
//    for(int i = 0; i < 64; i++)
//    {
//        framebuffer[i + 128] = bin >> 8;
//        bin ++;
//    }
//    bin -= 64;
//
//    for(int i = 0; i < 64; i++)
//    {
//        framebuffer[i + 192] = bin;
//        bin ++;
//    }
//    bin -= 64;
//    LINK_transfer_framedata();
//    
//    if(x % 4 == 0)
//    bin+=40;
   
  
    for(int x = 0; x < 96; x++)
    {
    LINK_transfer_framedata();
    for(int y = 0; y < 64; y++)
    {
      framebuffer[x][y]=img1[y*96+x];
    }
    }
    gfx_2d_fill_rectangle(0,0,95,63,-1);

    for(int i = 0; i < 60; i++)
    LINK_transfer_framedata();

    for(int x = 0; x < 96; x++)
    {
    LINK_transfer_framedata();
    for(int y = 0; y < 64; y++)
    {
      framebuffer[x][y]=img2[y*96+x];
    }
    }
    
    for(int i = 0; i < 380; i++)
    LINK_transfer_framedata();

    gfx_2d_fill_rectangle(0,0,95,63,-1);

    for(int i = 0; i < 60; i++)
    LINK_transfer_framedata();

    for(int x = 0; x < 96; x++)
    {
    LINK_transfer_framedata();
    for(int y = 0; y < 64; y++)
    {
      framebuffer[x][y]=img3[y*96+x];
    }
    }

    gfx_2d_fill_rectangle(0,0,95,63,-1);

    for(int i = 0; i < 60; i++)
    LINK_transfer_framedata();


  


//    if (bDeviceState == CONFIGURED)
//    {
//        while(Receive_length == 0)
//        {
//          CDC_Receive_DATA();
//        }
//        Receive_length = 0;
//      LINK_get_screenshot();
//      send_lcd_data();
//
//    }
  }
} 




/**




  * @brief  SHA256 HASH digest compute example.
  * @param  InputMessage: pointer to input message to be hashed.
  * @param  InputMessageLength: input data message length in byte.
  * @param  MessageDigest: pointer to output parameter that will handle message digest
  * @param  MessageDigestLength: pointer to output digest length.
  * @retval error status: can be HASH_SUCCESS if success or one of
  *         HASH_ERR_BAD_PARAMETER, HASH_ERR_BAD_CONTEXT,
  *         HASH_ERR_BAD_OPERATION if error occured.
  */
