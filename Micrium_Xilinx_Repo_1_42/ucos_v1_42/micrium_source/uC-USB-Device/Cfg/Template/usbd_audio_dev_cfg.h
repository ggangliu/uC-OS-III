/*
*********************************************************************************************************
*                                            uC/USB-Device
*                                       The Embedded USB Stack
*
*                         (c) Copyright 2004-2014; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/USB-Device is provided in source form to registered licensees ONLY.  It is
*                  illegal to distribute this source code to any third party unless you receive
*                  written permission by an authorized Micrium representative.  Knowledge of
*                  the source code may NOT be used to develop a similar product.
*
*                  Please help us continue to provide the Embedded community with the finest
*                  software available.  Your honesty is greatly appreciated.
*
*                  You can find our product's user manual, API reference, release notes and
*                  more information at: https://doc.micrium.com
*
*                  You can contact us at: http://www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                   USB AUDIO DEVICE CONFIGURATION FILE
*
* File          : usbd_audio_dev_cfg.h
* Version       : V4.05.00
* Programmer(s) : CM
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  USBD_AUDIO_DEV_CFG_MODULE_PRESENT                            /* See Note #1.                                         */
#define  USBD_AUDIO_DEV_CFG_MODULE_PRESENT


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  <app_usbd_cfg.h>
#include  <Class/Audio/usbd_audio.h>


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*********************************************************************************************************
*/

#define  APP_CFG_USBD_AUDIO_RECORD_NBR_BUF                 USBD_AUDIO_STREAM_NBR_BUF_18

#if (APP_CFG_USBD_AUDIO_SIMULATION_LOOP_EN == DEF_ENABLED)
#define  APP_CFG_USBD_AUDIO_PLAYBACK_NBR_BUF               USBD_AUDIO_STREAM_NBR_BUF_18
#endif


/*
*********************************************************************************************************
*                            USB AUDIO FUNCTION TOPOLOGY 1 CONFIGURATION
*********************************************************************************************************
*/

                                                                /* -------------- TERMINAL AND UNIT IDS --------------- */
extern         CPU_INT08U             Mic_IT_ID;
extern         CPU_INT08U             Mic_OT_USB_IN_ID;
extern         CPU_INT08U             Mic_FU_ID;
#if (APP_CFG_USBD_AUDIO_SIMULATION_LOOP_EN == DEF_ENABLED)
extern         CPU_INT08U             Speaker_IT_USB_OUT_ID;
extern         CPU_INT08U             Speaker_OT_ID;
extern         CPU_INT08U             Speaker_FU_ID;
#endif


                                                                /* ----------- TERMINAL, UNIT AND AS IF CFG ----------- */
extern  const  USBD_AUDIO_IT_CFG      USBD_IT_MIC_Cfg;
extern  const  USBD_AUDIO_OT_CFG      USBD_OT_USB_IN_Cfg;
extern  const  USBD_AUDIO_FU_CFG      USBD_FU_MIC_Cfg;
extern  const  USBD_AUDIO_STREAM_CFG  USBD_MicStreamCfg;
extern  const  USBD_AUDIO_AS_IF_CFG   USBD_AS_IF2_MicCfg;
#if (APP_CFG_USBD_AUDIO_SIMULATION_LOOP_EN == DEF_ENABLED)
extern  const  USBD_AUDIO_IT_CFG      USBD_IT_USB_OUT_Cfg;
extern  const  USBD_AUDIO_OT_CFG      USBD_OT_SPEAKER_Cfg;
extern  const  USBD_AUDIO_FU_CFG      USBD_FU_SPEAKER_Cfg;
extern  const  USBD_AUDIO_STREAM_CFG  USBD_SpeakerStreamCfg;
extern  const  USBD_AUDIO_AS_IF_CFG   USBD_AS_IF1_SpeakerCfg;
#endif


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*********************************************************************************************************
*/

#endif
