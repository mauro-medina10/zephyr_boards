/*
 * Copyright (c) 2022 Mauro Medina Serangeli
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nrf52833dk_bsp.h"
#include <zephyr/logging/log.h>

#define LOG_LEVEL 3

LOG_MODULE_REGISTER(bsp);

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
//LEDS
static const struct gpio_dt_spec led_0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led_1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led_2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led_3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

//BUTTONS
static const struct gpio_dt_spec sw_0 = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static const struct gpio_dt_spec sw_1 = GPIO_DT_SPEC_GET(SW1_NODE, gpios);
static const struct gpio_dt_spec sw_2 = GPIO_DT_SPEC_GET(SW2_NODE, gpios);
static const struct gpio_dt_spec sw_3 = GPIO_DT_SPEC_GET(SW3_NODE, gpios);

static struct gpio_callback button_cb_data;
static struct gpio_callback button1_cb_data;
static struct gpio_callback button2_cb_data;
static struct gpio_callback button3_cb_data;

void bsp_init(gpio_callback_handler_t btn1, 
                    gpio_callback_handler_t btn2, 
                    gpio_callback_handler_t btn3, 
                    gpio_callback_handler_t btn4){

	int32_t ret = 0;

	//LED checks
	if (!device_is_ready(led_0.port)
		|| !device_is_ready(led_1.port)	 
		|| !device_is_ready(led_2.port)
		|| !device_is_ready(led_3.port))
    {
		LOG_ERR("Led error.");
		return;
	}
	//Button checks
	if(!device_is_ready(sw_0.port) 
		|| !device_is_ready(sw_1.port) 	
		|| !device_is_ready(sw_2.port) 
		|| !device_is_ready(sw_3.port))
    {
		LOG_ERR("Button error.");
		return;
	}
	ret = gpio_pin_configure_dt(&led_0, GPIO_OUTPUT_INACTIVE);
	ret |= gpio_pin_configure_dt(&led_1, GPIO_OUTPUT_ACTIVE);
	ret |= gpio_pin_configure_dt(&led_2, GPIO_OUTPUT_INACTIVE);
	ret |= gpio_pin_configure_dt(&led_3, GPIO_OUTPUT_INACTIVE);	
	if (ret < 0)
    {
		return;
	}

	ret = gpio_pin_configure_dt(&sw_0, GPIO_INPUT);
	ret |= gpio_pin_configure_dt(&sw_1, GPIO_INPUT);
	ret |= gpio_pin_configure_dt(&sw_2, GPIO_INPUT);
	ret |= gpio_pin_configure_dt(&sw_3, GPIO_INPUT);

	if(ret != 0){

		LOG_ERR("Button init error: %d.", ret);
		return;
	}
	ret = gpio_pin_interrupt_configure_dt(&sw_0, GPIO_INT_EDGE_TO_ACTIVE);
	ret |= gpio_pin_interrupt_configure_dt(&sw_1, GPIO_INT_EDGE_TO_ACTIVE);
	ret |= gpio_pin_interrupt_configure_dt(&sw_2, GPIO_INT_EDGE_TO_ACTIVE);
	ret |= gpio_pin_interrupt_configure_dt(&sw_3, GPIO_INT_EDGE_TO_ACTIVE);

	if (ret != 0) {
		LOG_ERR("Error %d", ret);
		return;
	}
    if(btn1 != NULL)
    {
        gpio_init_callback(&button_cb_data, btn1, BIT(sw_0.pin));
	    gpio_add_callback(sw_0.port, &button_cb_data);
    }
    if(btn2 != NULL)
    {
        gpio_init_callback(&button1_cb_data, btn2, BIT(sw_1.pin));
	    gpio_add_callback(sw_1.port, &button1_cb_data);
    }
    if(btn3 != NULL)
    {
        gpio_init_callback(&button2_cb_data, btn3, BIT(sw_2.pin));
	    gpio_add_callback(sw_2.port, &button2_cb_data);
    }
    if(btn4 != NULL)
    {
        gpio_init_callback(&button3_cb_data, btn4, BIT(sw_3.pin));
	    gpio_add_callback(sw_3.port, &button3_cb_data);
    }
}

void bsp_led0_toggle(void)
{
    gpio_pin_toggle_dt(&led_0);
}
void bsp_led1_toggle(void)
{
    gpio_pin_toggle_dt(&led_1);
}
void bsp_led2_toggle(void)
{
    gpio_pin_toggle_dt(&led_2);
}
void bsp_led3_toggle(void)
{
    gpio_pin_toggle_dt(&led_3);
}
