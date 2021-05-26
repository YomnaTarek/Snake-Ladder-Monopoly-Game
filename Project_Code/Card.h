#pragma once

#include "GameObject.h"
#include "Player.h"

// Base Class of All Types of Cards (DecWalletCard_1, ...etc.)
// Note: We will make each type of Card in a separate class because:
// it may have additional data members and functions like: Apply(), ...etc. which have different implementation depending on Card type
class Card : public GameObject
{
protected:
	int cardNumber; // an integer representing the card number
	int Type;
public:
	Card(const CellPosition & pos); // A Constructor for card that takes the cell position of it

	void SetCardNumber(int cnum);   // The setter of card number
	int GetCardNumber();            // The getter of card number

	void Draw(Output* pOut) const;  // Draws the card number in the cell position of the card
	                                // It has the same implementation for all Card Types (Non-Virtual)

	virtual void ReadCardParameters(Grid * pGrid); // It reads the parameters specific for each Card Type
	                                               // It is a virtual function (implementation depends on Card Type)

	virtual void Apply(Grid* pGrid, Player* pPlayer);  // It applies the effect of the Card Type on the passed player
	                                                   // It is a virtual function (implementation depends on Card Type)
    virtual void settaken(int);
	virtual int  gettaken();
	virtual void setmor(int);
	virtual int getmor();
	virtual int getfee();
	virtual int getprice();
	virtual void setprice(int);
	virtual void setfees(int);
	virtual void setoffer(bool);
	virtual  bool getoffer();
	virtual void reset();
	virtual void setmade(bool);
	virtual void setload(bool);
	virtual void Save(ofstream& OutFile, Grid* pGrid,int typ);	// Saves the GameObject parameters to the file --> feel free to change this prototype as needed
	virtual void Load(ifstream& Infile, Grid* pGrid, int typ);	// Loads and Reads the GameObject parameters from the file --> feel free to change this prototype as needed

	virtual ~Card(); // A Virtual Destructor
};

