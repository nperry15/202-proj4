// Title: Ong.cpp
//Author: Nicholas Perry
//Date: 4/20/2020
//Description: This is the Ong cipher class file

#include "Cipher.h"
#include "Ong.h"
#include <istream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Name: Ong (Default Constructor)
// Desc: Constructor to build an empty Ong Cipher
// Preconditions - None
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(): Cipher() {
}
// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(string message, bool isEncrypted): Cipher(message, isEncrypted) {
}
// Name: Ong (Destructor)
// Desc: Destructor - Anything unique to Ong to delete?
// Preconditions - ~Ong exists
// Postconditions - Ong destroyed
Ong::~Ong() {
}

// Name: IsVowel (Helper function)
// Desc: Returns true if vowel, space, or punctuation
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsVowel(char val) {
	//loop through vowel list
	for (long unsigned int i = 0; i < (sizeof(VOWELS) / sizeof((VOWELS)[0])); i++) {
		if (val == VOWELS[i]) {
			return true;
		}
	}
	return false;
}

// Name: Encrypt
// Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
// If consonant then consonant and ong and dash displayed.
// Preconditions - Message exists
// Postconditions - Encrypts as above
void Ong::Encrypt() {
	ToggleEncrypted();

	string message = GetMessage();
	string newMessage = "";
	//loops through and stops before last char
	for (unsigned int i = 0; i < message.length() - 1; i++) {
		//grabs next ascii value
		int nextASCII = (int)message[i + 1];
		int currASCII = (int)message[i];
		//checks if it is a letter
		bool isNextLetter = (nextASCII > (CAPS_A - 1) && nextASCII < (CAPS_Z + 1)) || (nextASCII > (LOWER_A - 1) && nextASCII < (LOWER_Z + 1));
		bool isCurrLetter = (currASCII > (CAPS_A - 1) && currASCII < (CAPS_Z + 1)) || (currASCII > (LOWER_A - 1) && currASCII < (LOWER_Z + 1));

		newMessage += message[i];
		//if not a vowel but still a letter add ong
		if (!IsVowel(message[i]) && isCurrLetter) {
			newMessage += "ong";
		}

		//checks to see if next char is a letter
		if (isNextLetter && isCurrLetter) {
			newMessage += "-";
		}
	}
	newMessage += message[message.length() - 1];
	SetMessage(newMessage);
}

// Name: Decrypt
// Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
// Preconditions - Message exists
// Postconditions - Original message is displayed
void Ong::Decrypt() {
	ToggleEncrypted();

	string message = GetMessage();
	string newMessage = "";
	//loops through and stops before last char
	for (unsigned int i = 0; i < message.length() - 1; i++) {
		int currASCII = (int)message[i];
		//checks if it is a letter
		bool isCurrLetter = (currASCII > (CAPS_A - 1) && currASCII < (CAPS_Z + 1)) || (currASCII > (LOWER_A - 1) && currASCII < (LOWER_Z + 1));

		newMessage += message[i];
		//if not a vowel but still a letter skip the ong
		if (!IsVowel(message[i]) && isCurrLetter) {
			i += ONG_LENGTH;
		}

	}
	message = "";

	//loops through to delete dashes
	for (unsigned int i = 0; i < newMessage.length(); i++) {
		int currASCII = (int)newMessage[i];
		//if a dash is found skip over that index
		if (currASCII != DASH_ASCII) {
			message += newMessage[i];
		}
	}

	SetMessage(message);
}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Ong in this case)
string Ong::ToString() {
	return "Ong";
}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - o, delimiter, isencrypted, delimiter,
//                  message, delimiter, blank are output
string Ong::FormatOutput() {
	stringstream ss;
	ss << "o|" << GetIsEncrypted() << "|" << GetMessage() << "|" << endl;
	return ss.str();
}
