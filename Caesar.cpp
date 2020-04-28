// Title: Caesar.cpp
//Author: Nicholas Perry
//Date: 4/20/2020
//Description: This is the Caesar cipher class file

#include "Cipher.h"
#include "Caesar.h"
#include <istream>
#include <string>
#include <sstream>
using namespace std;

// Name: Caesar (Default Constructor)
// Desc: Constructor to build an empty Caesar Cipher (Defaults to shift 3)
// Preconditions - None
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar() : Cipher() {
	m_shift = 3;
}
// Name: Caesar (Overloaded Constructor)
// Desc: Constructor to build a populated Caesar Cipher (Defaults to shift 3)
// Preconditions - Pass it the message, isEncrypted, and shift (any integer)
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar(string message, bool isEncrypted, int shift) : Cipher(message, isEncrypted) {
	m_shift = shift;
}
// Name: Caesar (Destructor)
// Desc: Destructor - Anything specific to Caesar to delete?
// Preconditions - ~Caesar exists
// Postconditions - Caesar destroyed
Caesar::~Caesar() {
	m_shift = 0;
}
// Name: Encrypt
// Desc: Shifts characters right based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "right".
void Caesar::Encrypt() {
	string message = GetMessage();
	int currentASCII;

	ToggleEncrypted();
	for (unsigned int i = 0; i < message.length(); i++) {
		currentASCII = (int)message[i];

		//for lower case
		if (currentASCII > (LOWER_A - 1) && currentASCII < (LOWER_Z + 1)) {
			currentASCII += (m_shift % NUM_ALPHABET_LETTERS);
			//if values are beyond the last possible then wrap around
			if (currentASCII > LOWER_Z) {
				currentASCII -= NUM_ALPHABET_LETTERS;
			}
			//replace the values
			message[i] = (char)currentASCII;
		}

		//for upper case
		if (currentASCII > (CAPS_A - 1) && currentASCII < (CAPS_Z + 1)) {
			currentASCII += (m_shift % NUM_ALPHABET_LETTERS);
			//if values are beyond the last possible then wrap around
			if (currentASCII > CAPS_Z) {
				currentASCII -= NUM_ALPHABET_LETTERS;
			}
			//replace the values
			message[i] = (char)currentASCII;
		}
	}
	SetMessage(message);
}
// Name: Decrypt
// Desc: Shifts characters left based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "left".
void Caesar::Decrypt() {
	string message = GetMessage();
	int currentASCII;

	ToggleEncrypted();
	for (unsigned int i = 0; i < message.length(); i++) {
		currentASCII = (int)message[i];

		//for lower case
		if (currentASCII > (LOWER_A - 1) && currentASCII < (LOWER_Z + 1)) {
			currentASCII -= (m_shift % NUM_ALPHABET_LETTERS);
			//if values are beyond the last possible then wrap around
			if (currentASCII < LOWER_A) {
				currentASCII += NUM_ALPHABET_LETTERS;
			}
			//replace the values
			message[i] = (char)currentASCII;
		}

		//for upper case
		if (currentASCII > (CAPS_A - 1) && currentASCII < (CAPS_Z + 1)) {
			currentASCII -= (m_shift % NUM_ALPHABET_LETTERS);
			//if values are beyond the last possible then wrap around
			if (currentASCII < CAPS_A) {
				currentASCII += NUM_ALPHABET_LETTERS;
			}
			//replace the values
			message[i] = (char)currentASCII;
		}
	}
	SetMessage(message);
}
// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Caesar in this case)
string Caesar::ToString() {
	return "Caesar";
}
// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_shift are returned for output
string Caesar::FormatOutput() {
	stringstream ss;
	ss << "c|" << GetIsEncrypted() << "|" << GetMessage() << "|" << m_shift << endl;
	return ss.str();
}
