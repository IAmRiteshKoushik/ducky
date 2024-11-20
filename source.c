#include "stm32f4xx.h"

// HID key codes
#define KEY_A 0x04
#define KEY_B 0x05
#define KEY_C 0x06
#define KEY_D 0x07
#define KEY_E 0x08
#define KEY_F 0x09
#define KEY_G 0x0A
#define KEY_H 0x0B
#define KEY_I 0x0C
#define KEY_J 0x0D
#define KEY_K 0x0E
#define KEY_L 0x0F
#define KEY_M 0x10
#define KEY_N 0x11
#define KEY_O 0x12
#define KEY_P 0x13
#define KEY_Q 0x14
#define KEY_R 0x15
#define KEY_S 0x16
#define KEY_T 0x17
#define KEY_U 0x18
#define KEY_V 0x19
#define KEY_W 0x1A
#define KEY_X 0x1B
#define KEY_Y 0x1C
#define KEY_Z 0x1D
#define KEY_1 0x1E
#define KEY_2 0x1F
#define KEY_3 0x20
#define KEY_4 0x21
#define KEY_5 0x22
#define KEY_6 0x23
#define KEY_7 0x24
#define KEY_8 0x25
#define KEY_9 0x26
#define KEY_0 0x27
#define KEY_ENTER 0x28
#define KEY_SPACE 0x2C
#define KEY_SHIFT 0x02
#define KEY_CTRL 0x01

void initializeUSBHID();
void sendHIDReport(uint8_t modifier, uint8_t key);
void releaseHIDReport();
void initializeUSART1();
void USART1_Write(char c);
char USART1_Read();
void processInput(char input);

uint8_t remapTable[128] = {
    ['a'] = KEY_Q,     ['b'] = KEY_W, ['c'] = KEY_E, ['d'] = KEY_R,
    ['e'] = KEY_T,     ['f'] = KEY_Y, ['g'] = KEY_U, ['h'] = KEY_I,
    ['i'] = KEY_O,     ['j'] = KEY_P, ['k'] = KEY_A, ['l'] = KEY_S,
    ['m'] = KEY_D,     ['n'] = KEY_F, ['o'] = KEY_G, ['p'] = KEY_H,
    ['q'] = KEY_J,     ['r'] = KEY_K, ['s'] = KEY_L, ['t'] = KEY_Z,
    ['u'] = KEY_X,     ['v'] = KEY_C, ['w'] = KEY_V, ['x'] = KEY_B,
    ['y'] = KEY_N,     ['z'] = KEY_M, ['1'] = KEY_9, ['2'] = KEY_8,
    ['3'] = KEY_7,     ['4'] = KEY_6, ['5'] = KEY_5, ['6'] = KEY_4,
    ['7'] = KEY_3,     ['8'] = KEY_2, ['9'] = KEY_1, ['0'] = KEY_0,
    [' '] = KEY_ENTER, // Map space to Enter as an example
    ['\n'] = KEY_SPACE // Map Enter keypress to Spacebar
};

// Main loop
int main(void) {
  // Initialize USB HID
  initializeUSBHID();

  sendHIDReport(0, KEY_Q);
  releaseHIDReport();

  while (1) {
    char received = USART1_Read();
    processInput(received);
  }
}

void initializeUSBHID() {
  RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  // PA11 (USB D-) and PA12 (USB D+)
  GPIOA->MODER |= (2 << 22) | (2 << 24);
  GPIOA->AFR[1] |= (10 << 12) | (10 << 16);

  // USB device initialization
  USB_OTG_FS->GAHBCFG |= USB_OTG_GAHBCFG_GINT;
  USB_OTG_FS->GUSBCFG |= USB_OTG_GUSBCFG_FDMOD; // Force device mode
  USB_OTG_FS->GUSBCFG |= (6 << 10);             // Set turnaround time
  USB_OTG_FS->DCFG |= USB_OTG_DCFG_DSPD;        // Full-speed mode
  USB_OTG_FS->DCTL &= ~USB_OTG_DCTL_SDIS;       // Enable USB device

  USB_OTG_FS->DAINTMSK |= USB_OTG_DAINTMSK_IEPM; // Enable IN endpoint interrupt
  USB_OTG_FS->DOEPMSK |= USB_OTG_DOEPMSK_STUPM; // Enable setup packet interrupt
  USB_OTG_FS->DIEPCTL[1] =
      USB_OTG_DIEPCTL_USBAEP | (3 << 18) | 64; // Configure endpoint 1
  USB_OTG_FS->DIEPCTL[1] |=
      USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA; // Enable endpoint 1
  USB_OTG_FS->GINTMSK |= USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_USBRST |
                         USB_OTG_GINTMSK_ENUMDNEM;
}

void sendHIDReport(uint8_t modifier, uint8_t key) {
  uint8_t report[8] = {modifier, 0, key, 0, 0, 0, 0, 0};
}

void releaseHIDReport() { uint8_t report[8] = {0, 0, 0, 0, 0, 0, 0, 0}; }

void initializeUSART1() {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

  GPIOA->MODER |=
      (2 << 18) | (2 << 20); // Set PA9 and PA10 as alternate function
  GPIOA->AFR[1] |= (7 << 4) | (7 << 8); // Set AF7 for USART1

  USART1->BRR = 0x683;               // Baud rate 9600
  USART1->CR1 |= 0x8 | 0x4 | 0x2000; // Enable receiver, transmitter, and USART1
}

void USART1_Write(char c) {
  while (!(USART1->SR & 0x80))
    ; // Wait until TXE flag is set
  USART1->DR = c;
}

char USART1_Read() {
  while (!(USART1->SR & 0x20))
    ; // Wait until RXNE flag is set
  return USART1->DR;
}

void processInput(char input) {
  if (input < 128 && remapTable[input] != 0) {
    sendHIDReport(0, remapTable[input]);
    releaseHIDReport();
  }
}
