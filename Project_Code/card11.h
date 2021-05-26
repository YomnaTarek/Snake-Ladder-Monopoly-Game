#pragma once

#include "Card.h"



class card11 :	public Card
{
	// card11 Parameters:
	int price;
	int fees;
	int taken;
	int mor;
	bool offer;
	bool made;
public:
	card11(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of card11 which is: price and fees

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of card11 on the passed Player
	void settaken(int);                              //By asking the player whether he wants to buy the city and decrementing his wallet is he wanted to buy the city
	int gettaken();
	void reset();
	void setmor(int x);
	int getmor();
		int getprice();
	int getfee();
	void setfees(int);
	void setprice(int);
	void setoffer(bool);
	bool getoffer();
	void setmade(bool m);
	bool getmade();
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual void Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual ~card11(); // A Virtual Destructor
};

