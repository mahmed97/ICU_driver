/*-------------------------------------------------------------------------------
 *
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: Source file for the ICU driver
 *
 * Author: Mahmoud Ahmed
 *
 -------------------------------------------------------------------------------*/

#include "icu.h"

/* global variable holds the address of the call back function */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

ISR (TIMER1_CAPT_vect) {
	if (g_callBackPtr != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}
}

/*-----------------------------------------------------------------------------
 *                           FUNCTIONS DEFINITIONS
 -----------------------------------------------------------------------------*/

/* ICU_init FUNCTION
 * Description : Function to initialize the ICU driver
 * 1.Configure Pin (ICP1/PD6) as input pin
 * 2.Timer1 in Normal Mode
 * 3.Insert the required clock value
 * 4.Insert the required edge in ICES1 in TCCR1B reg
 * 5.Timer1 initial value
 * 6.Input Capture Register initial value
 * 7.Enable Input Capture Interrupt
 */
void ICU_init(const Icu_ConfigType * Config_Ptr) {
	CLEAR_BIT(DDRD, PD6);
	TCCR1A = (1 << FOC1A) | (1 << FOC1B);
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge) << 6);
	ICR1 = 0;
	TIMSK = (1 << TICIE1);
}

void ICU_setCallBack(void (*a_Ptr)(void)) {
	/* Save the address of call back function in a global value */
	g_callBackPtr = a_Ptr;
}

uint16 ICU_getInputCaptureValue(void) {
	/* Return the Timer1 value when the input is captured */
	return ICR1;
}
void ICU_setEdgeDetectionType(const Icu_Edge edge_type) {
	/* Insert the required edge in ICES1 in TCCR1B reg */
	TCCR1B = (TCCR1B & 0xBF) | ((edge_type) << 6);
}

void ICU_clearTimer(void) {
	/* Clear Timer1 value and start from ZERO */
	TCNT1 = 0;
}
void ICU_disable(void) {
	/* Clear all Timer1 registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	/* Disable Input Capture Interrupt */
	CLEAR_BIT(TIMSK, TICIE1);
}
