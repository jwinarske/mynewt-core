/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#include "syscfg/syscfg.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * COMMON CONFIGURATION
 */

#include <tusb_hw.h>

/* defined by compiler flags for flexibility */
#ifndef CFG_TUSB_MCU
#error CFG_TUSB_MCU must be defined
#endif

#define CFG_TUSB_RHPORT0_MODE       ((OPT_MODE_DEVICE) | (CFG_TUSB_RHPORT0_SPEED))

#if MYNEWT_VAL(BOOT_LOADER)
#define CFG_TUSB_OS                 OPT_OS_NONE
#else
#define CFG_TUSB_OS                 OPT_OS_MYNEWT
#endif
#define CFG_TUSB_DEBUG              MYNEWT_VAL(CFG_TUSB_DEBUG)

/* USB DMA on some MCUs can only access a specific SRAM region with restriction on alignment.
 * Tinyusb use follows macros to declare transferring memory so that they can be put
 * into those specific section.
 * e.g
 * - CFG_TUSB_MEM SECTION : __attribute__ (( section(".usb_ram") ))
 * - CFG_TUSB_MEM_ALIGN   : __attribute__ ((aligned(4)))
 */
#ifndef CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_SECTION
#endif

#ifndef CFG_TUSB_MEM_ALIGN
#define CFG_TUSB_MEM_ALIGN          __attribute__ ((aligned(4)))
#endif

/**
 * DEVICE CONFIGURATION
 */
#define CFG_TUD_ENDPOINT0_SIZE   MYNEWT_VAL(USBD_EP0_SIZE)

/* ------------- CLASS ------------- */
#if MYNEWT_VAL(USBD_CDC)
#define CFG_TUD_CDC              MYNEWT_VAL(USBD_CDC)
#else
#define CFG_TUD_CDC              0
#endif
#if MYNEWT_VAL(USBD_HID)
#define CFG_TUD_HID              MYNEWT_VAL(USBD_HID)
#else
#define CFG_TUD_HID              0
#endif
#if MYNEWT_VAL(USBD_MSC)
#define CFG_TUD_MSC              MYNEWT_VAL(USBD_MSC)
#else
#define CFG_TUD_MSC              0
#endif
#define CFG_TUD_MIDI             0
#define CFG_TUD_VENDOR           0
#define CFG_TUD_USBTMC           0
#define CFG_TUD_DFU_RT           0
#if MYNEWT_VAL(USBD_DFU)
#define CFG_TUD_DFU              MYNEWT_VAL(USBD_DFU)
#else
#define CFG_TUD_DFU              0
#endif
#if MYNEWT_VAL(USBD_BTH)
#define CFG_TUD_BTH              MYNEWT_VAL(USBD_BTH)
#else
#define CFG_TUD_BTH              0
#endif

/* Minimal number for alternative interfaces that is recognized by Windows as Bluetooth radio controller */
#define CFG_TUD_BTH_ISO_ALT_COUNT 2

#if MYNEWT_VAL(USBD_CDC_RX_BUFSIZE)
#define CFG_TUD_CDC_RX_BUFSIZE   MYNEWT_VAL(USBD_CDC_RX_BUFSIZE)
#else
#define CFG_TUD_CDC_RX_BUFSIZE   (TUD_OPT_HIGH_SPEED ? 512 : 64)
#endif

#if MYNEWT_VAL(USBD_CDC_TX_BUFSIZE)
#define CFG_TUD_CDC_TX_BUFSIZE   MYNEWT_VAL(USBD_CDC_TX_BUFSIZE)
#else
#define CFG_TUD_CDC_TX_BUFSIZE   (TUD_OPT_HIGH_SPEED ? 512 : 64)
#endif

/* HID buffer size Should be sufficient to hold ID (if any) + Data */
#define CFG_TUD_HID_BUFSIZE      16

/* MSC Buffer size of Device Mass storage */
#if MYNEWT_VAL(USBD_MSC_EP_BUFSIZE)
#define CFG_TUD_MSC_EP_BUFSIZE   MYNEWT_VAL(USBD_MSC_EP_BUFSIZE)
#else
#define CFG_TUD_MSC_EP_BUFSIZE   512
#endif

#ifndef CFG_TUD_DFU_XFER_BUFSIZE
#define CFG_TUD_DFU_XFER_BUFSIZE    256
#endif

#if MYNEWT_VAL(USBD_DFU_DETACH_TIMEOUT)
#define CFG_TUD_DFU_DETACH_TIMEOUT  MYNEWT_VAL(USBD_DFU_DETACH_TIMEOUT)
#else
#define CFG_TUD_DFU_DETACH_TIMEOUT  1000
#endif

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_CONFIG_H_ */
