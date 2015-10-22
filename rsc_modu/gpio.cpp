#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>

#include "gpio.h"

int gpio_set_cfgpin(unsigned int gpio,int status) //输入
{
    if(SETUP_OK != sunxi_gpio_set_cfgpin(gpio,status)){
        printf("Failed to config GPIO pin\n");
        return -1;
    }
    return 0;
}

int gpio_output(unsigned int gpio,int status)
{
    int ret;
    switch(gpio)
    {
    case 0:
        ret=sunxi_gpio_output(LED1,status);
        break;
    case 1:
        ret=sunxi_gpio_output(LED2,status);
        break;
    case 2:
        ret=sunxi_gpio_output(LED3,status);
        break;
    case 3:
        ret=sunxi_gpio_output(LED4,status);
        break;
    case 4:
	ret=sunxi_gpio_output(PMW,status);
    break;
    case 5:
        ret = sunxi_gpio_output(EN12V,status);
	break;
    default:
        break;
    }

    if(ret){
        printf("Failed to set GPIO pin value %d\n",gpio);
        return -1;
    }
    else{

#ifdef debug
        printf("gpio=%d,status=%d\n",gpio,status);
#endif

    }
    return 0;
}

int gpio_intput(unsigned int gpio)
{
    int status;
    switch(gpio)
    {
    case 0:
        status=sunxi_gpio_input(KEY1);
        break;
    case 1:
        status=sunxi_gpio_input(KEY2);
        break;
    case 2:
        status=sunxi_gpio_input(KEY3);
        break;
    case 3:
        status=sunxi_gpio_input(KEY4);
        break;
    case 4:
        status=sunxi_gpio_input(KEY5);
        break;
    case 5:
        status=sunxi_gpio_input(KEY6);
        break;
    case 6:
        status=sunxi_gpio_input(ENCODER_COUNTER);
        break;
    case 7:
        status=sunxi_gpio_input(ENCODER_CW);
        break;
    case 8:
        status=sunxi_gpio_input(ENCODER_CCW);
        break;

    }

    if(status==-1){
        printf("Failed to get GPIO pin value\n");
        return -1;
    }
    else{

#ifdef debug
        printf("gpio=%d,status=%d\n",gpio,status);
#endif

    }
    return status;
}

int gpio_init()
{
    if(SETUP_OK != sunxi_gpio_init()){
        printf("Failed to initialize GPIO\n");
        return -1;
    }
    gpio_set_cfgpin(LED1,OUTPUT);
    gpio_set_cfgpin(LED2,OUTPUT);
    gpio_set_cfgpin(LED3,OUTPUT);
    gpio_set_cfgpin(LED4,OUTPUT);

    gpio_set_cfgpin(LED4,PMW);

    gpio_set_cfgpin(KEY1,INPUT);
    gpio_set_cfgpin(KEY2,INPUT);
    gpio_set_cfgpin(KEY3,INPUT);
    gpio_set_cfgpin(KEY4,INPUT);
    gpio_set_cfgpin(KEY5,INPUT);
    gpio_set_cfgpin(KEY6,INPUT);

    gpio_set_cfgpin(ENCODER_CW,INPUT);
    gpio_set_cfgpin(ENCODER_CCW,INPUT);
    gpio_set_cfgpin(ENCODER_COUNTER,INPUT);
    gpio_set_cfgpin(EN12V,SUNXI_GPIO_OUTPUT);
    gpio_output(0,HIGH);
    gpio_output(1,HIGH);
    gpio_output(2,HIGH);
    gpio_output(3,HIGH);


    gpio_output(1,LOW);
    gpio_output(2,LOW);
    gpio_output(3,LOW);

    return 0;
}

void gpio_exit()
{
    sunxi_gpio_cleanup();
}


