#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "user_interface.h"

/*
 * This program blinks an LED.
 *
 * It uses the software timer instead of a loop to prevent the watchdog from
 * resetting the processor.
 */

static volatile os_timer_t timer;
static const int pin[2] = {4,5};

void timer_func(void * arg)
{
	uint32 signal = GPIO_INPUT_GET(pin[1]);
	GPIO_OUTPUT_SET(pin[0], signal);
	GPIO_OUTPUT_SET(pin[1], ~signal);
}

void ICACHE_FLASH_ATTR user_init(void)
{
	gpio_init();

	os_timer_disarm(&timer);
	os_timer_setfn(&timer, (os_timer_func_t *)timer_func, (void *)NULL);
	os_timer_arm(&timer, 250, 1);
}
