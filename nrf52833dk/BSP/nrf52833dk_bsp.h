/*
 * Copyright (c) 2022 Mauro Medina Serangeli
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef NRF52833_DK_H
#define NRF52833_DK_H

#include <stdint.h>

#include <errno.h>
#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/util.h>

/* The devicetree node identifier for the "ledx" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

/* The devicetree node identifier for the "buttonx" alias. */
#define SW0_NODE DT_ALIAS(sw0)
#define SW1_NODE DT_ALIAS(sw1)
#define SW2_NODE DT_ALIAS(sw2)
#define SW3_NODE DT_ALIAS(sw3)

//Button init
void bsp_init(gpio_callback_handler_t btn1, 
                    gpio_callback_handler_t btn2, 
                    gpio_callback_handler_t btn3, 
                    gpio_callback_handler_t btn4);

void bsp_led0_toggle(void);
void bsp_led1_toggle(void);
void bsp_led2_toggle(void);
void bsp_led3_toggle(void);
#endif