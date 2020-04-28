// Title: CipherTool.cpp
//Author: Nicholas Perry
//Date: 4/20/2020
//Description: This is the tool used to run all the ciphers

#include "Cipher.h"
#include "Caesar.h"
#include "Vigenere.h"
#include "Ong.h"
#include "CipherTool.h"

#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
// Preconditions - Input file passed and populated with Cipher
// Postconditions - CipherTool created
CipherTool::CipherTool(string fileName) {
	m_filename = fileName;
}

// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
// Preconditions - m_ciphers is populated
// Postconditions - m_ciphers emptied
CipherTool::~CipherTool() {
	for (auto& element : m_ciphers) {
		delete element;
	}
	m_filename = "";
}

// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers
// Preconditions - Input file passed and populated with Ciphers
// Postconditions - m_ciphers populated with Ciphers
void CipherTool::LoadFile() {
	ifstream file;

	string type;
	bool encryption;
	string message;

	string key = "";
	string numSpaces;
	string nullString;
	
	file.open(m_filename);
	Cipher* cipherPtr;

	//loops til there are no ciphers left
	while (getline(file, type, DELIMITER)) {
		//find encryption type and stop at DELIMITER and adds message
		file >> encryption;
		file.ignore(256, DELIMITER);
		getline(file, message, DELIMITER);
		
		//makes a new specific cipher type with cipher pointer
		if (type == CHAR_C) {
			getline(file, numSpaces);
			cipherPtr = new Caesar(message, encryption, stoi(numSpaces));
		}
		else if (type == CHAR_V) {
			getline(file, key);
			cipherPtr = new Vigenere(message, encryption, key);
		}
		else if (type == CHAR_O) {
			getline(file, nullString);
			cipherPtr = new Ong(message, encryption);
		}
		//add the cipher pointer to the box
		m_ciphers.push_back(cipherPtr);
	}

	file.close();

}

// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Displays ciphers
void CipherTool::DisplayCiphers() {
	string type;

	//loops through and display each cipher in the vector
	for (unsigned int i = 0; i < m_ciphers.size(); i++) {
		cout << (i + 1) << ". " << m_ciphers[i]->GetMessage();
		type = GetType(m_ciphers[i]);

		//displays each specific cipher type at the end
		if (type == CHAR_C) {
			cout << "(Caesar)" << endl;
		}
		else if (type == CHAR_V) {
			cout << "(Vigenere)" << endl;
		}
		else {
			cout << "(Ong)" << endl;
		}

		cout << endl;
	}
}

// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
void CipherTool::EncryptDecrypt(bool shouldEncrypted) {
	int changeCounter = 0;

	//true encrypted
	if (shouldEncrypted) {
		//loops through the vector and counts number of ciphers that have been encrypted
		for (long unsigned int i = 0; i < m_ciphers.size(); i++) {
			bool isEncrypted = m_ciphers[i]->GetIsEncrypted();
			if (!isEncrypted) {
				changeCounter++;
				m_ciphers[i]->Encrypt();
			}
		}
		cout << changeCounter << " ciphers Encrypted" << endl;

	}
	else {
		//loops through the vector and counts number of ciphers that have been decrypted
		for (long unsigned int i = 0; i < m_ciphers.size(); i++) {
			bool isEncrypted = m_ciphers[i]->GetIsEncrypted();
			if (isEncrypted) {
				changeCounter++;
				m_ciphers[i]->Decrypt();
			}
		}
		cout << changeCounter << " ciphers Decrypted" << endl;
	}
}

// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - All ciphers exported
void CipherTool::Export() {
	ofstream file;
	string name;
	int counter = 0;

	//ask user and opens file
	cout << "What would you like to call the export file?" << endl;
	cin >> name;
	file.open(name);

	//writes the vector to the file
	for (auto& element : m_ciphers) {
		file << element->FormatOutput();
		counter++;
	}

	//close the file and prompt user
	cout << counter << " Ciphers Exported" << endl;
	file.close();
}

// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_ciphers all populated
// Postconditions - Returns choice
int CipherTool::Menu() {
	int user;
	cout << "What would you like to do ?\n1. Display All Ciphers\n2. Encrypt All Ciphers\n";
	cout << "3. Decrypt All Ciphers\n4. Export All Ciphers\n5. Quit" << endl;
	cin >> user;
	//if the input is not valid
	while (user < SEL_ONE || user > SEL_FIVE) {
		cout << "Invalid input" << endl;
		cout << "What would you like to do ?\n1. Display All Ciphers\n2. Encrypt All Ciphers\n";
		cout << "3. Decrypt All Ciphers\n4. Export All Ciphers\n5. Quit" << endl;
		cin >> user;
	}
	return user;
}

// Name: GetType
// Desc - Pass it a cipher and it returns the char of the subtype
// Returns c for Caesar, v for Vigenere, and o for Ong
// Preconditions - m_ciphers all populated
// Postconditions - Returns char of type
char CipherTool::GetType(Cipher* cipherPtr) {
	if (cipherPtr->ToString() == "Caesar") {
		return CHAR_C[0];
	}
	else if (cipherPtr->ToString() == "Vigenere") {
		return CHAR_V[0];
	}
	return CHAR_O[0];
}

// Name: Start
// Desc - Loads input file, allows user to choose what to do
// Preconditions - m_ciphers populated with ciphers
// Postconditions - none
void CipherTool::Start() {
	int menu;
	LoadFile();

	//loops while 5 is not selected
	do {
		menu = Menu();
		//gets the selection and runs based off of it
		switch (menu) {
			case SEL_ONE:
				DisplayCiphers();
				break;
			case SEL_TWO:
				EncryptDecrypt(true);
				break;
			case SEL_THREE:
				EncryptDecrypt(false);
				break;
			case SEL_FOUR:
				Export();
				break;
			default:
				cout << "Thanks for using UMBC Encryption" << endl;
				break;
		}
	}while (menu != SEL_FIVE);

}

