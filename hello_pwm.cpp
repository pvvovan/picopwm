#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/cyw43_arch.h"

#include "dhcpserver.h"

// #define BLINK_PIN	PICO_DEFAULT_LED_PIN
#define BLINK_PIN	15

int main()
{
	stdio_init_all();
	if (cyw43_arch_init()) {
		printf("WiFi init failed");
		return -1;
	}
	const char *ap_name = "picow_test";
	const char *password = "password";
	cyw43_arch_enable_ap_mode(ap_name, password, CYW43_AUTH_WPA2_AES_PSK);

	// Start the dhcp server
	ip4_addr_t gw, mask;
	IP4_ADDR(&gw, 192, 168, 4, 1);
	IP4_ADDR(&mask, 255, 255, 255, 0);
	dhcp_server_t dhcp_server;
	dhcp_server_init(&dhcp_server, &gw, &mask);

	// Tell the LED pin that the PWM is in charge of its value.
	::gpio_set_function(BLINK_PIN, GPIO_FUNC_PWM);
	// Figure out which slice we just connected to the LED pin
	uint slice_num = ::pwm_gpio_to_slice_num(BLINK_PIN);

	// Get some sensible defaults for the slice configuration. By default, the
	// counter is allowed to wrap over its maximum range (0 to 2**16-1)
	pwm_config config = ::pwm_get_default_config();
	// Set divider, reduces counter clock to sysclock/this value
	::pwm_config_set_clkdiv(&config, 4.f);
	// Load the configuration into our PWM slice, and set it running.
	::pwm_init(slice_num, &config, true);

	while (true) {
		static absolute_time_t led_time;
		static bool led_on = true;

		if (absolute_time_diff_us(get_absolute_time(), led_time) < 0) {
			led_on = !led_on;
			if (led_on) {
				::pwm_set_gpio_level(BLINK_PIN, 255 * 5);
				cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
			} else {
				::pwm_set_gpio_level(BLINK_PIN, 0);
				cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
			}
			led_time = make_timeout_time_ms(500);
		}

		cyw43_arch_poll();
		sleep_ms(1);
	}
}
