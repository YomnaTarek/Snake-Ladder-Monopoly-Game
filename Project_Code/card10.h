#pragma once

#include "Card.h"



class card10 :	public Card
{
	// card10 Parameters:
	int price;
	int fees;
	int taken;
	int mor;
	bool offer;
	bool made;
public:
	card10(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of card10 which is: price and fees

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of card10 on the passed Player
	void settaken(int);                               //By asking the player whether he wants to buy the city and decrementing his wallet is he wanted to buy the city
	int gettaken();
	int getmor();
	void setmor(int);
	int getprice();
	int getfee();
	void setfees(int);
	void setprice(int);
	void setoffer(bool);
	bool getoffer();
	void reset();
	void setmade(bool m);
	bool getmade();
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual void Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual ~card10(); // A Virtual Destructor
};

