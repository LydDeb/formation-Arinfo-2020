/* ************************************************************************** */
/** Descriptive File Name
  @ Author
    Richard Wall
 
  @ Date:       April 30, 2016
    Revised:    December 12, 2016
    Verified:   May 20, 2017

  @Company
    Digilent Inc.      

  @File Name
    hardware.h

  @Development Environment
    MPLAB X IDE x3.61 - http://www.microchip.com/mplab/mplab-x-ide 
	XC32 1.43 - http://www.microchip.com/mplab/compilers
	PLIB 3/7/20162 - http://www.microchip.com/SWLibraryWeb/product.aspx?product=PIC32%20Peripheral%20Library

  @Summary
    Definition of constants and macro routines for the Basys MX3 processor board 

  @Description
    The #define statements and macro C code provides high level access to the 
    Basys MX3 trainer boards switches, push buttons, and LEDs.
    
 */
/* ************************************************************************** */
/* Conditional inclusion prevents multiple definition errors */
#ifndef _HARDWARE_H_   
    #define	_HARDWARE_H_

    #ifndef _SUPPRESS_PLIB_WARNING	/* Suppress plib obsolesce warnings */
        #define _SUPPRESS_PLIB_WARNING
    #endif

    #ifndef _DISABLE_OPENADC10_CONFIGPORT_WARNING
        #define  _DISABLE_OPENADC10_CONFIGPORT_WARNING
    #endif

/* Comment out the following define statement when programmer is NOT used to 
 * allow using BTNL and BTNU as user inputs. Inputs from push buttons BTNL and 
 * BRNU are not functional unless compiled and programmed for stand alone 
 * operation */

    #define DEBUG_MODE  

/* This included file provides access to the peripheral library functions and
   must be installed after the XC32 compiler. See
http://ww1.microchip.com/downloads/en/DeviceDoc/32bitPeripheralLibraryGuide.pdf and
http://www.microchip.com/SWLibraryWeb/product.aspx?product=PIC32%20Peripheral%20Library */

   #include <plib.h>
   
/* The following definitions are for IO assigned on the Digilent Basys MX3
   processor board. */

/* The ANSELx register has a default value of 0xFFFF; therefore, all pins that
 * share analog functions are analog (not digital) by default. All pins are 
 * initially set be digital followed be setting A_POT for the ANALOG INPUT 
 * CONTROL and A_MIC for the microphone input back to being analog input pins.*/
    #define ALL_DIGITAL_IO() (ANSELA=0,ANSELB=0,ANSELC=0,ANSELD=0,ANSELE=0,ANSELF=0,ANSELG = 0)
    #define SET_MIC_ANALOG()  ANSELBbits.ANSB4 = 1
    #define SET_POT_ANALOG()  ANSELBbits.ANSB2 = 1

/* Macros to configure PIC pins as inputs to sense switch settings */

/* The following macro instruction seta the processor pins for all 8 switch inputs */

// Configure slide switches
    #define SW0cfg()    TRISFbits.TRISF3 = 1 
    #define SW1cfg()    TRISFbits.TRISF5 = 1 
    #define SW2cfg()    TRISFbits.TRISF4 = 1 
    #define SW3cfg()    TRISDbits.TRISD15 = 1
    #define SW4cfg()    TRISDbits.TRISD14 = 1
    #define SW5cfg()    TRISBbits.TRISB11 = 1
    #define SW6cfg()    TRISBbits.TRISB10 = 1
    #define SW7cfg()    TRISBbits.TRISB9 = 1
    #define SWcfg()     (SW0cfg(), SW1cfg(), SW2cfg(), SW3cfg(), SW4cfg(),\
                         SW5cfg(), SW6cfg(), SW7cfg())

/* The following macro instructions provide for reading the position of the 8 switches. */
    #define SW0()           PORTFbits.RF3
    #define SW1()           PORTFbits.RF5
    #define SW2()           PORTFbits.RF4
    #define SW3()           PORTDbits.RD15
    #define SW4()           PORTDbits.RD14
    #define SW5()           PORTBbits.RB11
    #define SW6()           PORTBbits.RB10
    #define SW7()           PORTBbits.RB9

    #define Switch2Binary() ((((int) SW0()) << 0) + (((int) SW1()) <<1 ) +\
                             (((int) SW2()) << 2) + (((int) SW3()) <<3 ) +\
                             (((int) SW4()) << 4) + (((int) SW5()) <<5 ) +\
                             (((int) SW6()) << 6) + (((int) SW7()) <<7 ))


/* See http://umassamherstm5.org/tech-tutorials/pic32-tutorials/pic32mx220-tutorials/internal-pull-updown-resistors */
/* Macro instructions to set the push buttons as inputs */
    #ifndef DEBUG_MODE
/* Include BTNL and BTNU only if NOT in debug mode */
        #define Set_BTNL_in()  (TRISBbits.TRISB0 = 1, CNPDBbits.CNPDB0 = 1)
        #define Set_BTNU_in()  (TRISBbits.TRISB1 = 1, CNPDBbits.CNPDB1 = 1) 
    #endif
    #define Set_BTNR_in()   TRISBbits.TRISB8 = 1
    #define Set_BTNR_out()  TRISBbits.TRISB8 = 0    // use for Servo J1
    #define Set_BTND_in()   TRISAbits.TRISA15 = 1
    #define Set_BTND_out()  TRISAbits.TRISA15 = 0   // use for Servo J2
    #define Set_BTNC_in()   TRISFbits.TRISF0 = 1

/* Single macro instruction to configure all 5 push buttons */	
    #ifndef DEBUG_MODE
/* Allow use of BTNL and BTNU */
        #define Set_All_PBs_Input()( Set_BTNL_in(),Set_BTNR_in(),\
                                     Set_BTNU_in(),Set_BTND_in(),Set_BTNC_in() )    
    #else
/* Allow use of BTNL and BTNU */
        #define Set_All_PBs_Input()( Set_BTNR_in(),Set_BTND_in(),Set_BTNC_in() )
    #endif

/* Macro instructions to read the button position values. 1 = button pressed */ 
    #ifndef DEBUG_MODE
/* Include BTNL and BTNU only if NOT in debug mode */
        #define BNTL()      PORTBbits.RB0  
        #define BNTU()      PORTBbits.RB1  
    #endif
    #define BNTR()          PORTBbits.RB8  
    #define BNTD()          PORTAbits.RA15 
    #define BNTC()          PORTFbits.RF0 

/* Macros to define the PIC pin values for the board LEDs */
    #define LED0_bit        0x01
    #define LED1_bit        0x02
    #define LED2_bit        0x04
    #define LED3_bit        0x08
    #define LED4_bit        0x10
    #define LED5_bit        0x20
    #define LED6_bit        0x40
    #define LED7_bit        0x80
    #define All_LED_bits    0xFF	// Set all LEDs off  

/* Macros to configure PIC pins as outputs for board LEDs */
    #define Set_LED0_out()  TRISAbits.TRISA0 = 0
    #define Set_LED1_out()  TRISAbits.TRISA1 = 0
    #define Set_LED2_out()  TRISAbits.TRISA2 = 0
    #define Set_LED3_out()  TRISAbits.TRISA3 = 0
    #define Set_LED4_out()  TRISAbits.TRISA4 = 0
    #define Set_LED5_out()  TRISAbits.TRISA5 = 0
    #define Set_LED6_out()  TRISAbits.TRISA6 = 0
    #define Set_LED7_out()  TRISAbits.TRISA7 = 0
	
/* Macro instruction to configure all 8 LED pins for outputs */
    #define Set_All_LEDs_Output()  TRISACLR = All_LED_bits

/* Macros to set board each LED on (1) or off (0) */
    #define setLED0(a);  {if(a) LATASET = LED0_bit; else LATACLR = LED0_bit;}
    #define setLED1(a);  {if(a) LATASET = LED1_bit; else LATACLR = LED1_bit;}
    #define setLED2(a);  {if(a) LATASET = LED2_bit; else LATACLR = LED2_bit;}
    #define setLED3(a);  {if(a) LATASET = LED3_bit; else LATACLR = LED3_bit;}
    #define setLED4(a);  {if(a) LATASET = LED4_bit; else LATACLR = LED4_bit;}
    #define setLED5(a);  {if(a) LATASET = LED5_bit; else LATACLR = LED5_bit;}
    #define setLED6(a);  {if(a) LATASET = LED6_bit; else LATACLR = LED6_bit;}
    #define setLED7(a);  {if(a) LATASET = LED7_bit; else LATACLR = LED7_bit;}
    #define Set_All_LEDs_On()   LATASET = All_LED_bits  // Set all LEDs on
    #define Set_All_LEDs_Off()  LATACLR = All_LED_bits  // Set all LEDs off

/* Macros to invert the output to the board LEDs */
    #define invLED0()   LATAINV = LED0_bit    
    #define invLED1()   LATAINV = LED1_bit
    #define invLED2()   LATAINV = LED2_bit
    #define invLED3()   LATAINV = LED3_bit
    #define invLED4()   LATAINV = LED4_bit
    #define invLED5()   LATAINV = LED5_bit
    #define invLED6()   LATAINV = LED6_bit
    #define invLED7()   LATAINV = LED7_bit

/* Configure RGB LED outputs */
	#define Set_LED8_R_Out()	TRISDbits.TRISD2 = 0		
	#define Set_LED8_G_Out()	TRISDbits.TRISD12 = 0		
	#define Set_LED8_B_Out()	TRISDbits.TRISD3 = 0		
    #define Set_RGB_Output()    ( Set_LED8_R_Out(), Set_LED8_G_Out(), Set_LED8_B_Out() )

    #define Set_LED8_R(a)       LATDbits.LATD2 = a
    #define Set_LED8_G(a)       LATDbits.LATD12 = a
    #define Set_LED8_B(a)       LATDbits.LATD3 = a

    #define Set_LED8_RGB(a)     (LATDbits.LATD2 = a, LATDbits.LATD12 = a, LATDbits.LATD3 = a)             

// Set Motor Control drive inputs
	#define AIN1cfg()   (TRISBbits.TRISB3 = 0, ANSELBbits.ANSB3 = 0, LATBbits.LATB3 = 0)
	#define AIN2cfg()   (TRISEbits.TRISE8 = 0, LATEbits.LATE8 = 0)
	#define BIN1cfg()   (TRISEbits.TRISE9 = 0, LATEbits.LATE9 = 0)
	#define BIN2cfg()   (TRISBbits.TRISB5 = 0, ANSELBbits.ANSB5 = 0, LATBbits.LATB5 = 0)
	#define MCMODEcfg() (TRISFbits.TRISF1 = 0, LATFbits.LATF1 = 0)
	#define MCInit()	(AIN1cfg(), AIN2cfg(), BIN1cfg(), BIN2cfg(), MCMODEcfg())

	#define AIN1(a);    {if(a) LATBbits.LATB3 = 1; else LATBbits.LATB3 = 0;}
	#define AIN2(a);    {if(a) LATEbits.LATE8 = 1; else LATEbits.LATE8 = 0;}
	#define BIN1(a);    {if(a) LATEbits.LATE9 = 1; else LATEbits.LATE9 = 0;}
	#define BIN2(a);    {if(a) LATBbits.LATB5 = 1; else LATBbits.LATB5 = 0;}
	#define MCMODE(a);  {if(a) LATFbits.LATF1 = 1; else LATFbits.LATF1 = 0;}

	#define AIN1toggle();    LATBINV = BIT_3
	#define AIN2toggle();    LATEINV = BIT_8
	#define BIN1toggle();    LATEINV = BIT_9
	#define BIN2toggle();    LATBINV = BIT_5

// define setup parameters for OpenADC10
                    // Turn module on | output integer  | trigger mode auto | enable auto sample
    #define ADC_PARAM1  ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON

// define setup parameters for OpenADC10
                // ADC ref external    | disable offset test    | disable scan mode | perform 2 samples | use dual buffers | use alternate mode
    #define ADC_PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_2 | ADC_ALT_BUF_ON | ADC_ALT_INPUT_ON

// define setup parameters for OpenADC10
    //                use ADC internal clock | set sample time
    #define ADC_PARAM3  ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15
 
// define setup parameters for OpenADC10
                // set AN2 and AN4 as analog inputs
    #define ADC_PARAM4    ENABLE_AN2_ANA | ENABLE_AN4_ANA

// define setup parameters for OpenADC10
    // do not assign channels to scan
    #define ADC_PARAM5    SKIP_SCAN_ALL

	// maximum ADC value of 10 bits
    #define ADCMAX        1023

/* Based upon setting in config_bits.h These directly influence timed
 * events using the Tick module.  They also are used for UART I2C, and SPI
 * baud rate generation. */

    #define XTAL                 (8000000UL)     /* 8 MHz Xtal on Basys MX3A */
    #define GetSystemClock()     (80000000UL)    /* Instruction frequency */
    #define SYSTEM_FREQ          (GetSystemClock())
    #define GetCoreClock()       (GetSystemClock()/2) /* Core clock frequency */
    #define GetPeripheralClock() (GetSystemClock()/8) /* PCLK set for 80 MHz */

/* Used in core timer software delay */
    #define CORE_MS_TICK_RATE	 (unsigned int) (GetCoreClock()/1000UL)

/* Seven Segment Display */
#define SSD_ON 0
#define SSD_OFF 1
#define SSD_set_AN0_off() LATBbits.LATB12 = 1 // Anode 0
#define SSD_set_AN1_off() LATBbits.LATB13 = 1 // Anode 1
#define SSD_set_AN2_off() LATAbits.LATA9 = 1 // Anode 2
#define SSD_set_AN3_off() LATAbits.LATA10 = 1 // Anode 3
#define SSD_set_AN0_on() LATBbits.LATB12 = 0 // Anode 0
#define SSD_set_AN1_on() LATBbits.LATB13 = 0 // Anode 1
#define SSD_set_AN2_on() LATAbits.LATA9 = 0 // Anode 2
#define SSD_set_AN3_on() LATAbits.LATA10 = 0 // Anode 3
#define SSD_set_ANs_off() (SSD_set_AN0_off(),SSD_set_AN1_off(),\
    SSD_set_AN2_off(),SSD_set_AN3_off())

#define SSD_set_CA_on() LATGbits.LATG12 = 0 // Cathode A
#define SSD_set_CB_on() LATAbits.LATA14 = 0 // Cathode B
#define SSD_set_CC_on() LATDbits.LATD6 = 0 // Cathode C
#define SSD_set_CD_on() LATGbits.LATG13 = 0 // Cathode D
#define SSD_set_CE_on() LATGbits.LATG15 = 0// Cathode E
#define SSD_set_CF_on() LATDbits.LATD7 = 0 // Cathode F
#define SSD_set_CG_on() LATDbits.LATD13 = 0 // Cathode G
#define SSD_set_CDP_on() LATGbits.LATG14 = 0 // Cathode DP
#define SSD_set_CA_off() LATGbits.LATG12 = 1 // Cathode A
#define SSD_set_CB_off() LATAbits.LATA14 = 1 // Cathode B
#define SSD_set_CC_off() LATDbits.LATD6 = 1 // Cathode C
#define SSD_set_CD_off() LATGbits.LATG13 = 1 // Cathode D
#define SSD_set_CE_off() LATGbits.LATG15 = 1 // Cathode E
#define SSD_set_CF_off() LATDbits.LATD7 = 1 // Cathode F
#define SSD_set_CG_off() LATDbits.LATD13 = 1 // Cathode G
#define SSD_set_CDP_off() LATGbits.LATG14 = 1 // Cathode DP

#define SSD_configure() (TRISBbits.TRISB12 = 0, \
                        ANSELBbits.ANSB12 = 0, \
                        TRISBbits.TRISB13 = 0, \
                        ANSELBbits.ANSB13 = 0, \
                        TRISAbits.TRISA9 = 0, \
                        TRISAbits.TRISA10 = 0,\
                        TRISGbits.TRISG12 = 0,\
                        TRISAbits.TRISA14 = 0,\
                        TRISDbits.TRISD6 = 0, \
                        TRISGbits.TRISG13 = 0,\
                        TRISGbits.TRISG15 = 0,\
                        TRISDbits.TRISD7 = 0, \
                        TRISDbits.TRISD13 = 0,\
                        TRISGbits.TRISG14 = 0\
                        )
#define SSD_all_AN_off() (SSD_set_AN0_off(),SSD_set_AN1_off(),\
                        SSD_set_AN2_off(),SSD_set_AN3_off())
#define SSD_all_AN_on() (SSD_set_AN0_on(),SSD_set_AN1_on(),\
                        SSD_set_AN2_on(),SSD_set_AN3_on())
#define SSD_all_C_off() (SSD_set_CA_off(),SSD_set_CB_off(),\
                        SSD_set_CC_off(),SSD_set_CD_off(),\
                        SSD_set_CE_off(),SSD_set_CF_off(),\
                        SSD_set_CG_off(),SSD_set_CDP_off())
#define SSD_all_C_on() (SSD_set_CA_on(),SSD_set_CB_on(),\
                        SSD_set_CC_on(),SSD_set_CD_on(),\
                        SSD_set_CE_on(),SSD_set_CF_on(),\
                        SSD_set_CG_on(),SSD_set_CDP_on())
#define SSD_all_off() (SSD_all_AN_off(),SSD_all_C_off())
#define SSD_all_on() (SSD_all_AN_on(),SSD_all_C_on())

/* Switches */
#define SW_configure() (TRISFbits.TRISF3 = 1,\
                        TRISFbits.TRISF5 = 1,\
                        TRISFbits.TRISF4 = 1,\
                        TRISDbits.TRISD15 = 1,\
                        TRISDbits.TRISD14 = 1,\
                        TRISBbits.TRISB11 = 1,\
                        ANSELBbits.ANSB11 = 0,\
                        TRISBbits.TRISB10 = 1,\
                        ANSELBbits.ANSB10 = 0)

/* Buttons */
#define BTN_configure() (TRISBbits.TRISB1 = 1,\
                        ANSELBbits.ANSB1 = 0,\
                        TRISBbits.TRISB0 = 1,\
                        ANSELBbits.ANSB0 = 0,\
                        TRISFbits.TRISF4 = 1,\
                        TRISBbits.TRISB8 = 1,\
                        ANSELBbits.ANSB8 = 0,\
                        TRISAbits.TRISA15 = 1)

#define BTN_U() PORTBbits.RB1  // read BTNU 
#define BTN_L() PORTBbits.RB0  // read BTNL 
#define BTN_C() PORTFbits.RF0  // read BTNC 
#define BTN_R() PORTBbits.RB8  // read BTNR 
#define BTN_D() PORTAbits.RA15  // read BTND 
//#pragma config JTAGEN = OFF

#endif	/* End of _HARDWARE_H_ */

// *****************************************************************************
/**
  @Function
    void hardware(void);

  @Summary
    Initializes PIC32 pins commonly used for IO on the Basys MX3 Trainer 
    processor board.

  @Description
    Initializes PIC32 digital IO pins to provide functionality for the 
    slide switches, push buttons, and LEDs

  @Parameters
    None

  @Returns
    None
***************************************************************************** */    
void Hardware_Setup(void);

// End of hardware.h 
