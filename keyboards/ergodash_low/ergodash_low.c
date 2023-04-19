#include "ergodash_low.h"

void matrix_init_kb(void) {
	// set pins as output
	setPinOutput(D5);
    setPinOutput(B0);
	// set them high to turn OFF LEDs (default)
	writePinHigh(B0);
	writePinHigh(D5);

	matrix_init_user();
};

void shutdown_user(void) {

}
