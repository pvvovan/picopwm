#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main()
{
	// Tell the LED pin that the PWM is in charge of its value.
	::gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);
	// Figure out which slice we just connected to the LED pin
	uint slice_num = ::pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN);

	// Get some sensible defaults for the slice configuration. By default, the
	// counter is allowed to wrap over its maximum range (0 to 2**16-1)
	pwm_config config = ::pwm_get_default_config();
	// Set divider, reduces counter clock to sysclock/this value
	::pwm_config_set_clkdiv(&config, 4.f);
	// Load the configuration into our PWM slice, and set it running.
	::pwm_init(slice_num, &config, true);

	::pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, 255 * 3);

	// we can twiddle our thumbs
	while (true) {
		::tight_loop_contents();
	}
}
