#include "usb.h"
#include "usb_device.h"
#include "HardwareProfile.h"
#include "usb_function_hid.h"

#define SIE_TX_READY() (HIDTxHandleBusy(lastTransmission)==0) // Serial Interface Engine Ready?
#define MODIFIER_KEYS_ENT hid_report_in[0]
#define RESERVED_ENT      hid_report_in[1]
#define KEYCODE1_ENT      hid_report_in[2]
#define KEYCODE2_ENT      hid_report_in[3]
#define KEYCODE3_ENT      hid_report_in[4]
#define KEYCODE4_ENT      hid_report_in[5]
#define KEYCODE5_ENT      hid_report_in[6]
#define KEYCODE6_ENT      hid_report_in[7]
#define SEND_HID_REPORT()  lastTransmission = HIDTxPacket(HID_EP,(BYTE*)hid_report_in, 0x08)


extern USB_HANDLE lastTransmission;
void Keyboard(void);
void InitializeSystem(void);
void ProcessIO(void);
void UserInit(void);
