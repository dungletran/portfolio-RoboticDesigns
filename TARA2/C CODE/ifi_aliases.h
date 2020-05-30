/********************************************************************************
* FILE NAME: ifi_aliases.h <EDU VERSION>
*
* DESCRIPTION: 
*  This file contains common macros (known as aliases in PBASIC) for the 
*  I/O pins of the Robot Controller and elements in the data sent between the 
*  User processor and the Master processor.
*  
*  If you want to create your own macros, do so in the designated section of 
*  the user_routines.h file.
*  
*  DO NOT EDIT THIS FILE!
********************************************************************************/

#ifndef __ifi_aliases_h_
#define __ifi_aliases_h_

#include <adc.h>

/* PWM Control Definitions used in Setup_Who_Controls_Pwms(...) */
#define USER      0     /* User controls PWM outputs. */
#define MASTER    1     /* Master controls PWM outputs. */

/* PWM Type Definitions used in Setup_PWM_Output_Type(...) */
#define IFI_PWM   0     /* Standard IFI PWM output generated with Generate_PWM(...) */
#define USER_CCP  1     /* User can use PWM pin as digital I/O or CCP pin. */

/*
 *-------------------------------------------------------------------------------
 *---------- Aliases for R/C PWM IN connectors ----------------------------------
 *-------------------------------------------------------------------------------
 *  Below are aliases for the PWM inputs received from the radio-control receiver.
 */
#define PWM_in1         rxdata.oi_analog01
#define PWM_in2         rxdata.oi_analog02
#define PWM_in3         rxdata.oi_analog03
#define PWM_in4         rxdata.oi_analog04
#define PWM_in5         rxdata.oi_analog05
#define PWM_in6         rxdata.oi_analog06
#define PWM_in7         rxdata.oi_analog07
#define PWM_in8         rxdata.oi_analog08

/*
 *-------------------------------------------------------------------------------
 *---------- Aliases for PWM OUT connectors -------------------------------------
 *-------------------------------------------------------------------------------
 *  Below are aliases for the PWM output values located on the Robot Controller.  
 */
#define pwm01           txdata.rc_pwm01		//left wheel
#define pwm02           txdata.rc_pwm02		//right wheel
#define pwm03           txdata.rc_pwm03		//scoop servo
#define pwm04           txdata.rc_pwm04		//basket servo
#define pwm05           txdata.rc_pwm05
#define pwm06           txdata.rc_pwm06
#define pwm07           txdata.rc_pwm07
#define pwm08           txdata.rc_pwm08

/*
 *-------------------------------------------------------------------------------
 *---------- Aliases for DIGITAL IN/OUT - ANALOG IN connectors ------------------
 *-------------------------------------------------------------------------------
 */
#define INPUT   1
#define OUTPUT  0

/* Used in User_Initialization routine in user_routines.c file. */
/* Used to set pins as INPUTS (analog or digital) or OUTPUTS (digital only). */
#define IO1             TRISAbits.TRISA0
#define IO2             TRISAbits.TRISA1
#define IO3             TRISAbits.TRISA2
#define IO4             TRISAbits.TRISA3
#define IO5             TRISAbits.TRISA5
#define IO6             TRISFbits.TRISF0
#define IO7             TRISFbits.TRISF1
#define IO8             TRISFbits.TRISF2
#define IO9             TRISFbits.TRISF3
#define IO10            TRISFbits.TRISF4
#define IO11            TRISFbits.TRISF5
#define IO12            TRISFbits.TRISF6
#define IO13            TRISHbits.TRISH4
#define IO14            TRISHbits.TRISH5
#define IO15            TRISHbits.TRISH6
#define IO16            TRISHbits.TRISH7

/* Aliases used to read the pins when used as INPUTS. */
#define rc_dig_in01     PORTAbits.RA0		 
#define rc_dig_in02     PORTAbits.RA1		
#define rc_dig_in03     PORTAbits.RA2		
#define rc_dig_in04     PORTAbits.RA3		//left reflective sensor
#define rc_dig_in05     PORTAbits.RA5		//right reflective sensor
#define rc_dig_in06     PORTFbits.RF0		//back refelective sensor
#define rc_dig_in07     PORTFbits.RF1		//on off switch
#define rc_dig_in08     PORTFbits.RF2		//back limit switch1
#define rc_dig_in09     PORTFbits.RF3		//back limit switch2
#define rc_dig_in10     PORTFbits.RF4		//frond limit switch1
#define rc_dig_in11     PORTFbits.RF5		//frond limit switch2
#define rc_dig_in12     PORTFbits.RF6		//basket limit switch
#define rc_dig_in13     PORTHbits.RH4		//north compass
#define rc_dig_in14     PORTHbits.RH5		//east compass
#define rc_dig_in15     PORTHbits.RH6		//south compass
#define rc_dig_in16     PORTHbits.RH7		//west compass

/* Aliases used to drive the pins when used as OUTPUTS. */
#define rc_dig_out01    LATAbits.LATA0
#define rc_dig_out02    LATAbits.LATA1
#define rc_dig_out03    LATAbits.LATA2
#define rc_dig_out04    LATAbits.LATA3
#define rc_dig_out05    LATAbits.LATA5
#define rc_dig_out06    LATFbits.LATF0
#define rc_dig_out07    LATFbits.LATF1
#define rc_dig_out08    LATFbits.LATF2
#define rc_dig_out09    LATFbits.LATF3
#define rc_dig_out10    LATFbits.LATF4
#define rc_dig_out11    LATFbits.LATF5
#define rc_dig_out12    LATFbits.LATF6
#define rc_dig_out13    LATHbits.LATH4
#define rc_dig_out14    LATHbits.LATH5
#define rc_dig_out15    LATHbits.LATH6
#define rc_dig_out16    LATHbits.LATH7

/*
 *-------------------------------------------------------------------------------
 *---------- Aliases for INTERRUPTS connectors (inputs) -------------------------
 *-------------------------------------------------------------------------------
 *  Below are aliases for the input pins labelled INTERRUPTS on the EDU Robot Controller.
 *  These pins are connected to PULL-UPS, meaning they are normally HIGH (1).
 */
#define rc_dig_int1     PORTBbits.RB2
#define rc_dig_int2     PORTBbits.RB3
#define rc_dig_int3     PORTBbits.RB4
#define rc_dig_int4     PORTBbits.RB5
#define rc_dig_int5     PORTBbits.RB6
#define rc_dig_int6     PORTBbits.RB7

/*
 *-------------------------------------------------------------------------------
 *---------- Aliases for SOLENOID OUT connectors (outputs) ----------------------
 *-------------------------------------------------------------------------------
 *  Below are aliases for the solenoid outputs located on the Robot Controller.  
 */
#define solenoid1       LATDbits.LATD0
#define solenoid2       LATDbits.LATD1
#define solenoid3       LATDbits.LATD2
#define solenoid4       LATDbits.LATD3
#define solenoid5       LATDbits.LATD4
#define solenoid6       LATDbits.LATD5

/*
 *-------------------------------------------------------------------------------
 *---------- Aliases for each RC analog input -----------------------------------
 *-------------------------------------------------------------------------------
 *  Below are aliases for the analog input channels of the 18F8520.
 *  They correspond to the DIGITAL IN/OUT - ANALOG IN pins on the Robot Controller.
 */
/* Used in Get_Analog_Value(...) routine. */
#define rc_ana_in01     ADC_CH0			//left sharp sensor
#define rc_ana_in02     ADC_CH1			//right sharp sensor
#define rc_ana_in03     ADC_CH2			//scoop sharp sensor
#define rc_ana_in04     ADC_CH3
#define rc_ana_in05     ADC_CH4
#define rc_ana_in06     ADC_CH5
#define rc_ana_in07     ADC_CH6
#define rc_ana_in08     ADC_CH7
#define rc_ana_in09     ADC_CH8
#define rc_ana_in10     ADC_CH9
#define rc_ana_in11     ADC_CH10
#define rc_ana_in12     ADC_CH11
#define rc_ana_in13     ADC_CH12
#define rc_ana_in14     ADC_CH13
#define rc_ana_in15     ADC_CH14
#define rc_ana_in16     ADC_CH15

/* Used in Set_Number_of_Analog_Channels(...) routine in user_routines.c file. */
#define NO_ANALOG       ADC_0ANA    /* All digital */
#define ONE_ANALOG      ADC_1ANA    /* analog: AN0      digital: AN1->15 */
#define TWO_ANALOG      ADC_2ANA    /* analog: AN0->1   digital: AN2->15 */
#define THREE_ANALOG    ADC_3ANA    /* analog: AN0->2   digital: AN3->15 */
#define FOUR_ANALOG     ADC_4ANA    /* analog: AN0->3   digital: AN4->15 */
#define FIVE_ANALOG     ADC_5ANA    /* analog: AN0->4   digital: AN5->15 */
#define SIX_ANALOG      ADC_6ANA    /* analog: AN0->5   digital: AN6->15 */
#define SEVEN_ANALOG    ADC_7ANA    /* analog: AN0->6   digital: AN7->15 */
#define EIGHT_ANALOG    ADC_8ANA    /* analog: AN0->7   digital: AN8->15 */
#define NINE_ANALOG     ADC_9ANA    /* analog: AN0->8   digital: AN9->15 */
#define TEN_ANALOG      ADC_10ANA   /* analog: AN0->9   digital: AN10->15 */
#define ELEVEN_ANALOG   ADC_11ANA   /* analog: AN0->10  digital: AN11->15 */
#define TWELVE_ANALOG   ADC_12ANA   /* analog: AN0->11  digital: AN12->15 */
#define THIRTEEN_ANALOG ADC_13ANA   /* analog: AN0->12  digital: AN13->15 */
#define FOURTEEN_ANALOG ADC_14ANA   /* analog: AN0->13  digital: AN14->15 */
/* There is no FIFTEEN_ANALOG! */
#define SIXTEEN_ANALOG  ADC_16ANA   /* All analog */

/*
 *-------------------------------------------------------------------------------
 *---------- Aliases for CCP pins (PWM OUT 1-4 connectors) ----------------------
 *-------------------------------------------------------------------------------
 *  Below are aliases for the four PWM OUT pins which can be configured for use
 *  as digital inputs or outputs.  They are CCP pins with special features as 
 *  detailed in the PIC18FXX20 Data Sheet on page 149.  
 *
 *   The pin mapping is as follows:
 *   PWM OUT 1 -> CCP2
 *   PWM OUT 2 -> CCP3
 *   PWM OUT 3 -> CCP4
 *   PWM OUT 4 -> CCP5 
 */
/* To set the direction (input or output) of the pins you use these aliases. */
#define IO_CCP2         TRISEbits.TRISE7
#define IO_CCP3         TRISGbits.TRISG0
#define IO_CCP4         TRISGbits.TRISG3
#define IO_CCP5         TRISGbits.TRISG4

/* When using them as inputs you read the values with these aliases. */
#define IN_CCP2         PORTEbits.RE7
#define IN_CCP3         PORTGbits.RG0
#define IN_CCP4         PORTGbits.RG3
#define IN_CCP5         PORTGbits.RG4

/* When using them as outputs you drive a value with these aliases. */
#define OUT_CCP2        LATEbits.LATE7
#define OUT_CCP3        LATGbits.LATG0
#define OUT_CCP4        LATGbits.LATG3
#define OUT_CCP5        LATGbits.LATG4

/*
 *-------------------------------------------------------------------------------
 *---------- Aliases for TTL connectors (serial port 2) -------------------------
 *-------------------------------------------------------------------------------
 *  Below are aliases for the second serial port (USART2) pins labeled TTL.
 */
#define usart2_TX       LATGbits.LATG1
#define usart2_RX       PORTGbits.RG2

/*
 *-------------------------------------------------------------------------------
 *---------- Alias for Battery Voltage  -----------------------------------------
 *-------------------------------------------------------------------------------
 * current voltage = battery_voltage * 0.038 + 0.05; 
 */
#define battery_voltage rxdata.rc_analog01

/*
 *-------------------------------------------------------------------------------
 *---------- Aliases for User Modes  --------------------------------------------
 *-------------------------------------------------------------------------------
 */
#define user_display_mode rxdata.rc_mode_byte.mode.user_display
#define autonomous_mode   rxdata.rc_mode_byte.mode.autonomous

#endif

/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
