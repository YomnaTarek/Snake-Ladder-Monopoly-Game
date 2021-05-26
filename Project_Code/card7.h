#pragma once

#include "Card.h"


class card7 :	public Card
{
	// Card7 Parameters:
	int price;//the price of the city
	int fees;// the amount of money that will be paid by the passing player to the city's owner 
	int taken; // new data memebers that indicate who owns the city 
	int mor; // indicates who mortgage the city
	bool offer; // offer the city for mortgage
	bool made;//whether it's first time to create the card or not

public:
	card7(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of card7 which are: price and fees

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of card7 on the passed Player
													  //By asking the player whether he wants to buy the city and decrementing his wallet is he wanted to buy the city
	void settaken(int); //A setter for taken                                                
	int gettaken();//A getter for taken
	void setmor(int);// A setter for mor
	int getmor();//A getter for mor
	int getprice();//A getter for price
	int getfee();//A getter for fees
	void setfees(int);// A setter for fees
	void setprice(int);// A setter for price
	void setoffer(bool);//A setter for offer
	bool getoffer();//A getter for offer
	void reset();// For New Game
	void setmade(bool m);//A setter for made
	bool getmade();// A getter for made
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual void Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual ~card7(); // A Virtual Destructor
};

