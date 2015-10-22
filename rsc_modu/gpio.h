#ifndef GPIO_H
#define GPIO_H

#include "gpio_lib.h"

//#define debug

#define KEY1   SUNXI_GPH(17)
#define KEY2   SUNXI_GPH(6)
#define KEY3   SUNXI_GPH(11)
#define KEY4   SUNXI_GPH(12)
#define KEY5   SUNXI_GPH(16)
#define KEY6   SUNXI_GPH(20)

#define LED1   SUNXI_GPB(3)
#define LED2   SUNXI_GPB(4)
#define LED3   SUNXI_GPH(23)
#define LED4   SUNXI_GPH(25)


#define ENCODER_CW   SUNXI_GPH(18)
#define ENCODER_CCW   SUNXI_GPH(13)
#define ENCODER_COUNTER   SUNXI_GPH(19)

#define PMW    SUNXI_GPB(2)
#define EN12V SUNXI_GPI(3)

int gpio_set_cfgpin(unsigned int gpio,int status);
int gpio_output(unsigned int gpio,int status);
int gpio_intput(unsigned int gpio);
int gpio_init(void);
void gpio_exit(void);

#endif // GPIO_H
