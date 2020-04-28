// Title: Vigenere.cpp
//Author: Nicholas Perry
//Date: 4/20/2020
//Description: This is the Vigenere cipher class file

#include "Cipher.h"
#include "Vigenere.h"
#include <istream>
#include <string>
#include <sstream>
using namespace std;

// Name: Vigenere (Default Constructor)
// Desc: Constructor to build an empty Vigenere Cipher (Defaults key to "test")
// Preconditions - None
// Postconditions - Creates a Vigenere cipher to be encrypted
Vigenere::Vigenere(): Cipher() {
	m_key = "test";
}
// Name: Vigenere (Overloaded Constructor)
// Desc: Constructor to build a populated Vigenere Cipher
// Preconditions - Pass it the message, isEncrypted, and key
// Postconditions - Creates a Vigenere cipher to be encrypted
Vigenere::Vigenere(string message, bool isEncrypted, string key): Cipher(message, isEncrypted) {
	m_key = key;
}
// Name: Vigenere (Destructor)
// Desc: Destructor - Anything specific to delete in Vigenere?
// Preconditions - ~Vigenere exists
// Postconditions - Vigenere destroyed
Vigenere::~Vigenere() {
	m_key = "";
}
// Name: Encrypt
// Desc: Encrypts using key (See project document for details)
// Preconditions - Message exists
// Postconditions - Encrypts using key
void Vigenere::Encrypt() {
	ToggleEncrypted();

	string message = GetMessage();
	string filledKey = "";
	bool isLetter;
	bool isCaps;
	int encryptionIndex;
	int encryptedChar;
	int keyCounter = 0;

	//fill filledKey up with m_key
	int fullKeysInMessage = message.length() / m_key.length();
	int partialKeysLeft = message.length() % m_key.length();
	for (int i = 0; i < fullKeysInMessage; i++) {
		filledKey += m_key;
	}
	for (int i = 0; i < partialKeysLeft; i++) {
		filledKey += m_key[i];
	}

	//start encryption using filledKey
	for (unsigned int i = 0; i < message.length(); i++) {
		isLetter = ((int)message[i] > (CAPS_A - 1) && (int)message[i] < (CAPS_Z + 1)) || ((int)message[i] > (LOWER_A - 1) && (int)message[i] < (LOWER_Z + 1));
		isCaps = (int)message[i] > (CAPS_A - 1) && (int)message[i] < (CAPS_Z + 1);

		//only encrypt if char is a letter
		if (isLetter) {
			//check for a capital letter
			if (isCaps) {
				//encrypts with caps key
				filledKey[keyCounter] = toupper(filledKey[keyCounter]);
				encryptionIndex = (((int)message[i] - CAPS_A) + ((int)filledKey[keyCounter] - CAPS_A)) % NUM_ALPHABET_LETTERS;
			}else{
				//encrypts with lowercase key
				filledKey[keyCounter] = tolower(filledKey[keyCounter]);
				encryptionIndex = (((int)message[i] - LOWER_A) + ((int)filledKey[keyCounter] - LOWER_A)) % NUM_ALPHABET_LETTERS;
			}

			//adds the int values to get to the correct ASCII values
			if (isCaps) {
				encryptedChar = CAPS_A + encryptionIndex;
			}
			else {
				encryptedChar = LOWER_A + encryptionIndex;
			}

			//replaces the values
			message[i] = (char)encryptedChar;
			keyCounter++;
		}
	}

	SetMessage(message);
}
// Name: Decrypt
// Desc: Decrypts using key (See project document for details)
// Preconditions - Message exists
// Postconditions - Uses key to decrypt.
void Vigenere::Decrypt() {
	ToggleEncrypted();

	string message = GetMessage();
	string filledKey = "";
	bool isLetter;
	bool isCaps;
	int encryptionIndex;
	int encryptedChar;
	int keyCounter = 0;

	//fill filledKey up with m_key
	int fullKeysInMessage = message.length() / m_key.length();
	int partialKeysLeft = message.length() % m_key.length();
	for (int i = 0; i < fullKeysInMessage; i++) {
		filledKey += m_key;
	}
	for (int i = 0; i < partialKeysLeft; i++) {
		filledKey += m_key[i];
	}

	//start encryption using filledKey
	for (unsigned int i = 0; i < message.length(); i++) {
		isLetter = ((int)message[i] > (CAPS_A - 1) && (int)message[i] < (CAPS_Z + 1)) || ((int)message[i] > (LOWER_A - 1) && (int)message[i] < (LOWER_Z + 1));
		isCaps = (int)message[i] > (CAPS_A - 1) && (int)message[i] < (CAPS_Z + 1);

		//only decrypt if char is a letter
		if (isLetter) {
			//check for a capital letter
			if (isCaps) {
				//decrypts with caps key
				filledKey[keyCounter] = toupper(filledKey[keyCounter]);
				encryptionIndex = (((int)message[i] - CAPS_A) - ((int)filledKey[keyCounter] - CAPS_A)) % NUM_ALPHABET_LETTERS;
			}
			else {
				//decrypts with lowercase key
				filledKey[keyCounter] = tolower(filledKey[keyCounter]);
				encryptionIndex = (((int)message[i] - LOWER_A) - ((int)filledKey[keyCounter] - LOWER_A)) % NUM_ALPHABET_LETTERS;
			}

			//loops around if values are negative
			if (encryptionIndex < 0) {
				encryptionIndex += NUM_ALPHABET_LETTERS;
			}

			//adds the int values to get to the correct ASCII values
			if (isCaps) {
				encryptedChar = CAPS_A + encryptionIndex;
			}
			else {
				encryptedChar = LOWER_A + encryptionIndex;
			}

			//replaces the values
			message[i] = (char)encryptedChar;
			keyCounter++;
		}
	}

	SetMessage(message);
}
// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Vigenere in this case)
string Vigenere::ToString() {
	return "Vigenere";
}
// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - v, delimiter, isencrypted, delimiter,
//                  message, delimiter, key are returned for output
string Vigenere::FormatOutput() {
	stringstream ss;
	ss << "v|" << GetIsEncrypted() << "|" << GetMessage() << "|" << m_key << endl;
	return ss.str();
}
