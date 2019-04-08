#include "usb.h"
#include "usb_device.h"
#include "HardwareProfile.h"
#include "usb_function_hid.h"


extern USB_HANDLE lastTransmission;
void Keyboard(void);
void InitializeSystem(void);
void ProcessIO(void);
void UserInit(void);
