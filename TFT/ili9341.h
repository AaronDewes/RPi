#ifndef ILI9341_H
#define ILI9341_H

#include "gpio.h"
#include <unistd.h>

// Control pin
#define TFT_CS		PIN(7)		// Chip-select (0)
#define TFT_BLC		PIN(11)		// Background light control (0)
#define TFT_RST		PIN(13)		// Reset (0)
#define TFT_WR		PIN(15)		// Parallel data write strobe (Rising)
#define TFT_RS		PIN(19)		// Data(1) / Command(0) selection
#define TFT_RD		PIN(21)		// Parallel data read strobe (Rising)

// Control pin masks
#define TFT_MCS		PINM(7)		// Chip-select (0)
#define TFT_MBLC	PINM(11)	// Background light control (0)
#define TFT_MRST	PINM(13)	// Reset (0)
#define TFT_MWR		PINM(15)	// Parallel data write strobe (Rising)
#define TFT_MRS		PINM(19)	// Data(1) / Command(0) selection
#define TFT_MRD		PINM(21)	// Parallel data read strobe (Rising)

// Data pin
#define TFT_D0		PIN(12)		// Data pin 0
#define TFT_D1		PIN(16)		// Data pin 1
#define TFT_D2		PIN(18)		// Data pin 2
#define TFT_D3		PIN(22)		// Data pin 3
#define TFT_D4		PIN(24)		// Data pin 4
#define TFT_D5		PIN(26)		// Data pin 5
#define TFT_D6		PIN(3)		// Data pin 6
#define TFT_D7		PIN(5)		// Data pin 7

// Data pin masks
#define TFT_MD0		PINM(12)	// Data pin 0
#define TFT_MD1		PINM(16)	// Data pin 1
#define TFT_MD2		PINM(18)	// Data pin 2
#define TFT_MD3		PINM(22)	// Data pin 3
#define TFT_MD4		PINM(24)	// Data pin 4
#define TFT_MD5		PINM(26)	// Data pin 5
#define TFT_MD6		PINM(3)		// Data pin 6
#define TFT_MD7		PINM(5)		// Data pin 7

// 8-bit parallel interface I

class ili9341
{
public:
	enum Orientation {Landscape, Portrait, \
		FlipLandscape, FlipPortrait, \
		BMPLandscape, BMPPortrait, \
		BMPFlipLandscape, BMPFlipPortrait};

	static inline void init(void);
	/**
	 *Enabled/disable idle mode
	 * 
	 * @param e True if idle mode should be enabled, false otherwise
	 */
	static inline void idle(bool e) {cmd(0x38 + e);}
	/**
	 *Enabled/disable sleep mode
	 * 
	 * @param e True if sleep mode should be enabled, false otherwise
	 */
	static inline void sleep(bool e) {cmd(0x10 + e);}
	/**
	 *Enabled/disable inversion mode
	 * 
	 * @param e True if inversion mode should be enabled, false otherwise
	 */
	static inline void inversion(bool e) {cmd(0x20 + e);}

protected:
	static inline void cmd(uint8_t dat);
	static inline void data(uint8_t dat);
	static inline void send(bool c, uint8_t dat);
	static inline uint8_t recv(void);
	static inline void mode(bool _recv);
	static inline void _setBGLight(bool enabled);
	static inline void _setOrient(Orientation o);
};

// Functions defined as inline to excute faster


/**
 * Sets the screen orientation
 * 
 * @param o The orientation to be used
 */
inline void ili9341::_setOrient(Orientation o)
{
	cmd(0x36);			// Memory Access Control
	switch (o) {
	case Landscape:
		data(0x28);		// Column Address Order, BGR
		break;
	case Portrait:
		data(0x48);		// Column Address Order, BGR
		break;
	case FlipLandscape:
		data(0xE8);		// Column Address Order, BGR
		break;
	case FlipPortrait:
		data(0x88);		// Column Address Order, BGR
		break;
	case BMPLandscape:
		data(0x68);		// Column Address Order, BGR
		break;
	case BMPFlipLandscape:
		data(0xA8);		// Column Address Order, BGR
		break;
	case BMPPortrait:
		data(0xD8);		// Column Address Order, BGR
		break;
	case BMPFlipPortrait:
		data(0x18);		// Column Address Order, BGR
		break;
	}
}

/**
 * Sends a command to the screen
 * 
 * Used by send()
 * @param dat the command to be sent
 */
inline void ili9341::cmd(uint8_t dat)
{
	uint32_t value = ((dat & (1 << 0)) ? TFT_MD0 : 0) | \
			((dat & (1 << 1)) ? TFT_MD1 : 0) | \
			((dat & (1 << 2)) ? TFT_MD2 : 0) | \
			((dat & (1 << 3)) ? TFT_MD3 : 0) | \
			((dat & (1 << 4)) ? TFT_MD4 : 0) | \
			((dat & (1 << 5)) ? TFT_MD5 : 0) | \
			((dat & (1 << 6)) ? TFT_MD6 : 0) | \
			((dat & (1 << 7)) ? TFT_MD7 : 0);
	GPIO_WRITE_MULTI(value, TFT_MD0 | TFT_MD1 | TFT_MD2 | TFT_MD3 | TFT_MD4 | TFT_MD5 | TFT_MD6 | TFT_MD7 | TFT_MRS | TFT_MWR);
	GPIO_SET_MULTI(TFT_MWR | TFT_MRS);
}

/**
 * Sends data to the screen
 * 
 * Used by send()
 * @param dat the data to be sent
 */
inline void ili9341::data(uint8_t dat)
{
	uint32_t value = ((dat & (1 << 0)) ? TFT_MD0 : 0) | \
			((dat & (1 << 1)) ? TFT_MD1 : 0) | \
			((dat & (1 << 2)) ? TFT_MD2 : 0) | \
			((dat & (1 << 3)) ? TFT_MD3 : 0) | \
			((dat & (1 << 4)) ? TFT_MD4 : 0) | \
			((dat & (1 << 5)) ? TFT_MD5 : 0) | \
			((dat & (1 << 6)) ? TFT_MD6 : 0) | \
			((dat & (1 << 7)) ? TFT_MD7 : 0);
	GPIO_WRITE_MULTI(value, TFT_MD0 | TFT_MD1 | TFT_MD2 | TFT_MD3 | TFT_MD4 | TFT_MD5 | TFT_MD6 | TFT_MD7 | TFT_MWR);
	GPIO_SET(TFT_WR);
}

/**
 * Internal function to switch between receive and send mode
 * 
 * @param _recv Set this to true if you want to receive data, otherwise false
 */
inline void ili9341::mode(bool _recv)
{
	if (_recv) {
		GPIO_INPUT(TFT_D0);
		GPIO_INPUT(TFT_D1);
		GPIO_INPUT(TFT_D2);
		GPIO_INPUT(TFT_D3);
		GPIO_INPUT(TFT_D4);
		GPIO_INPUT(TFT_D5);
		GPIO_INPUT(TFT_D6);
		GPIO_INPUT(TFT_D7);
		GPIO_PUD_UP(TFT_D0);
		GPIO_PUD_UP(TFT_D1);
		GPIO_PUD_UP(TFT_D2);
		GPIO_PUD_UP(TFT_D3);
		GPIO_PUD_UP(TFT_D4);
		GPIO_PUD_UP(TFT_D5);
		GPIO_PUD_UP(TFT_D6);
		GPIO_PUD_UP(TFT_D7);
	} else {
		GPIO_PUD_OFF(TFT_D0);
		GPIO_PUD_OFF(TFT_D1);
		GPIO_PUD_OFF(TFT_D2);
		GPIO_PUD_OFF(TFT_D3);
		GPIO_PUD_OFF(TFT_D4);
		GPIO_PUD_OFF(TFT_D5);
		GPIO_PUD_OFF(TFT_D6);
		GPIO_PUD_OFF(TFT_D7);
		GPIO_OUTPUT(TFT_D0);
		GPIO_OUTPUT(TFT_D1);
		GPIO_OUTPUT(TFT_D2);
		GPIO_OUTPUT(TFT_D3);
		GPIO_OUTPUT(TFT_D4);
		GPIO_OUTPUT(TFT_D5);
		GPIO_OUTPUT(TFT_D6);
		GPIO_OUTPUT(TFT_D7);
	}
}

/**
 * Sends data to the screen
 * 
 * @param command Set this to true if you want to send a command, not data that should be displayed
 * @param dat the data to be sent
 */
inline void ili9341::send(bool command, uint8_t dat)
{
	if (command)
		cmd(dat);
	else
		data(dat);
}


/**
 * Receives data from the screen
 * 
 * Mostly used internally and should not be called directly in higher-level code
 */
inline uint8_t ili9341::recv(void)
{
	unsigned char dat;
	GPIO_CLR(TFT_RD);
	//_NOP();
	dat = GPIO_READ(TFT_D0) ? (1 << 0) : 0;
	dat |= GPIO_READ(TFT_D1) ? (1 << 1) : 0;
	dat |= GPIO_READ(TFT_D2) ? (1 << 2) : 0;
	dat |= GPIO_READ(TFT_D3) ? (1 << 3) : 0;
	dat |= GPIO_READ(TFT_D4) ? (1 << 4) : 0;
	dat |= GPIO_READ(TFT_D5) ? (1 << 5) : 0;
	dat |= GPIO_READ(TFT_D6) ? (1 << 6) : 0;
	dat |= GPIO_READ(TFT_D7) ? (1 << 7) : 0;
	GPIO_SET(TFT_RD);
	return dat;
}

/**
 * Enables or disables the screen background light
 * 
 * @param enabled If this is set to true, the light gets turned on, otherwise it gets turned off
 */
inline void ili9341::_setBGLight(bool enabled)
{
	if (enabled)
		GPIO_SET(TFT_BLC);
	else
		GPIO_CLR(TFT_BLC);
}

/**
 * Initializes or resets the screen
 * 
 * Internally, this
 * 1. Resets the hardware
 * 2. Turns the display off
 * 3. Sets a few useful meta properties used later in rendering
 * 4. Turns the screen black
 * 5. Turns the screen on
 */
inline void ili9341::init(void)
{
	uint8_t c;
	uint16_t r;

	GPIO_OUTPUT(TFT_CS);
	GPIO_OUTPUT(TFT_BLC);
	GPIO_OUTPUT(TFT_RST);
	GPIO_OUTPUT(TFT_WR);
	GPIO_OUTPUT(TFT_RS);
	GPIO_OUTPUT(TFT_RD);
	GPIO_SET(TFT_CS);
	GPIO_SET(TFT_BLC);
	GPIO_SET(TFT_RST);
	GPIO_SET(TFT_WR);
	GPIO_SET(TFT_RS);
	GPIO_SET(TFT_RD);
	mode(true);
	GPIO_CLR(TFT_RST);		// Hardware reset
	GPIO_CLR(TFT_CS);
	GPIO_SET(TFT_WR);
	GPIO_SET(TFT_RD);
	GPIO_SET(TFT_RS);
	usleep(10);			// Min: 10us
	GPIO_SET(TFT_RST);
	usleep(120000);
	mode(false);
	cmd(0x28);		// Display OFF
	cmd(0x11);		// Sleep Out
	usleep(120000);
	cmd(0x34);		// Tearing Effect Line OFF
	cmd(0x38);		// Idle Mode OFF
	cmd(0x13);		// Normal Display Mode ON
	cmd(0x20);		// Display Inversion OFF
	cmd(0x3A);		// COLMOD: Pixel Format Set
	data(0x55);		// 16 bits/pixel
	cmd(0x36);		// Memory Access Control
	data(0x48);		// Column Adress Order, BGR
	cmd(0x2C);		// Memory Write
	for (r = 0; r < 320; r++)	// Black screen
		for (c = 0; c < 240; c++) {
			data(0x00);
			data(0x00);
		}
	cmd(0xB1);		// Frame Rate control, normal
	data(0x00);		// Faster
	data(0x18);
	cmd(0xB3);		// Frame Rate control, partial
	data(0x00);		// Faster
	data(0x18);
	cmd(0x29);		// Display On
}

#endif
