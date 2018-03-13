// TI File $Revision: /main/2 $
// Checkin $Date: March 1, 2007   15:57:02 $
//###########################################################################
//
// FILE:	DSP2833x_Sci.h
//
// TITLE:	DSP2833x Device SCI Register Definitions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#ifndef _SBUS_H
#define _SBUS_H


#ifdef __cplusplus
extern "C" {
#endif



void scib_init();
void scib_xmit(Uint16 a);
Uint16 scib_rx(void);
void scib_fifo_init();
void update_servos(void);
void update_channels(void);
void feedLine();
void loop();
void Process(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2833x_SCI_H definition

//===========================================================================
// End of file.
//===========================================================================

