// Ydle.cpp
//
// Ydle implementation for Arduino
// See the README file in this directory for documentation
// For changes, look at Ydle.h
//
// Authors:
// Fabrice Scheider AKA Denia,
// Manuel Esteban AKA Yaug
// Matthieu Desgardin AKA Zescientist
// Yargol AKA Yargol
//
// WebPage: http://www.ydle.fr/index.php
// Contact: http://forum.ydle.fr/index.php
// Licence: CC by sa (http://creativecommons.org/licenses/by-sa/3.0/fr/)
//
// Pll function inspired on VirtualWire library
/// \Mainpage Ydle library for Arduino
///
/// \Installation
/// To install, unzip the library into the libraries sub-directory of your
/// Arduino application directory. Then launch the Arduino environment; you
/// should see the library in the Sketch->Import Library menu, and example
/// code in File->Sketchbook->Examples->Ydle menu.
///
///
/// \Revision History:
/// \version 0.1
///     - Original release of the Node code
///
/// \version 0.2 2013-08-20
/// 	- Creation of the library
///
/// \version 0.5 2013-09-24
/// 	- Now use Pll function to receive signal
/// 	- Partial asynchronous rewrite of the code
///		- Parity bit
/// 	- Variable frame length for more informations
/// \version 0.5.1 2014-01-17
/// 	- Partial rewriting of code
/// 	- Using timer interrupt for call the pll function
///     - Add callback function to handle user command
///     - Rename all #define to avoid confusion with other lib
/// To use the Ydle library, you must have:
///     #include <Ydle.h>
/// At the top of your sketch.
///

#ifndef Ydle_h
#define Ydle_h

#include <stdlib.h>
#include <Arduino.h>
#if defined(ARDUINO)
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <wiring.h>
#endif
#else // error
#error Platform not defined
#endif

#define _YDLE_DEBUG

#define YDLE_MAX_FRAME 2

//FETS	#define YDLE_MAX_SIZE_FRAME 64
#define YDLE_MAX_SIZE_FRAME 36
// 1 sec timeout for ack
#define YDLE_ACK_TIMEOUT 250
#define YDLE_TYPE_ACK  			3 // Acquit last command
#define YDLE_TYPE_STATE_ACK 	4 // Node send data and want ACK


// Défini un type de structure Frame_t
struct Frame_t
{
	uint8_t receptor; // 8 bytes
	uint8_t sender; // 8 bytes
	uint8_t type; // 2 bytes
	uint8_t taille;	// 3 bytes data len + crc in BYTES
	uint8_t data[30];
	uint8_t crc; // 8 bytes
};

// Défini un type de structure Config_t
struct Config_t
{
	uint8_t IdMaster;
	uint8_t IdNode;
	uint8_t type;
};

extern "C" {
	// callback function
	typedef void (*ydleCallbackFunction)(Frame_t *frame);
}

void timerInterrupt();
void pll();

volatile static Config_t m_Config;

class ydle
{
private:
public:

	// Le constructeur qui lance une instance avec les numéros des pins de l'émetteur, du récepteur et du boutton
	// Par défaut, le récepteur est en 2, l'émetteur en 10 et le boutton en 13
	ydle();
	
	// Envoie des verrous et des bits formant une trame
	void send(Frame_t *frame);
	
	// Ecoute le récepteur pour l'arrivée d'un signal
	void listenSignal();
	
	// Crée une trame avec le type
	void dataToFrame(Frame_t *frame, unsigned long type, uint8_t this_receptor);

	// Affiche le contenue des trames reéues
	void printFrame();

	int isSignal();
	bool isDone();
	
	// CRC calculation
	unsigned char computeCrc(Frame_t *frame);
	// Launch the timer for the receive function
	void init_timer();
	// New function need to be called by the main function in order to handle the new received frame
	Frame_t * receive();
	void	CancelLastReceive() ;
	
	static void requestEvent();
	
	static void receiveEvent(int howMany);

private:

	// Fonctions de débogage
	void log(String msg);
	void log(String msg,int i);
	void printFrame(Frame_t *trame);
	
	// Do something with a received Command
	void handleReceivedFrame(Frame_t *frame);

	// Compare le signal reçu au signal de référence
	bool checkSignal(Frame_t *frame);

	uint8_t crc8(const uint8_t* buf, uint8_t length);
	uint32_t		mReadFrame ; // compteur sur frame reçus
};

#endif

