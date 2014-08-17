#ifndef HW_CONTROL_H
#define HW_CONTROL_H

#define Breset BRR
#define Bset BSRR

#define ENABLE_CALC GPIO_Pin_0
#define SHORT_BACKUPBATT GPIO_Pin_1
#define ON_KEY GPIO_Pin_2
#define VIBRATE GPIO_Pin_15


void HW_CONTROL_init(void);
void HW_CONTROL_ENABLE_CALC(void);
void HW_CONTROL_DISABLE_CALC(void);
void HW_CONTROL_PRESS_ON_KEY(void);
void HW_CONTROL_RELEASE_ON_KEY(void);
void HW_CONTROL_CLICK_ON_KEY(void);

#endif