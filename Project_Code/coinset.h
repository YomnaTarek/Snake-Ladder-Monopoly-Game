#pragma once

#include "GameObject.h"

class CoinSet :	public GameObject // inherited from GameObject
{
	int coinamount; // here is the amount of coins in the coinset
	int Type;
public:

	CoinSet(const CellPosition & CellPos,int); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a coinset in its cell position

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the coinset by rewarding the passing player with extra coins

	CellPosition GetPosition() const; // A getter for the position
	int getcoins() const;//A getter for the coinamount
	void setcoins(int amount);//A setter for the coinamount

	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);	// Saves the GameObject parameters to the file --> feel free to change this prototype as needed
	virtual void Load(ifstream& Infile, Grid* pGrid, int typ);	// Loads and Reads the GameObject parameters from the file --> feel free to change this prototype as needed

	virtual ~CoinSet(); // Virtual destructor
};

