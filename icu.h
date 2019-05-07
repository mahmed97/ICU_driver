 /*-------------------------------------------------------------------------------
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Header file for the ICU driver
 *
 * Author: Mahmoud Ahmed
 *
 -------------------------------------------------------------------------------*/

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*--------------------------------------------------------------------------
 *                            TYPES DECLARATION
 --------------------------------------------------------------------------*/
typedef enum {
	NO_CLOCK,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_Clock;

typedef enum {
	FALLING,RISING
}Icu_Edge;

typedef struct
{
	Icu_Clock clock;
	Icu_Edge edge;
}Icu_ConfigType;


/*-----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPES
 -----------------------------------------------------------------------------*/
void ICU_init(const Icu_ConfigType * Config_Ptr);
void ICU_setCallBack(void (*a_Ptr)(void));
uint16 ICU_getInputCaptureValue(void);
void ICU_setEdgeDetectionType(const Icu_Edge edge_type);
void ICU_clearTimer(void);
void ICU_disable(void);

#endif /* ICU_H_ */
