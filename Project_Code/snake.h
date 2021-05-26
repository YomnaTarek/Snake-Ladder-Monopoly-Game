#pragma once

#include "GameObject.h"

class Snake :	public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the snake's "Start Cell Position"

	CellPosition endCellPos; // here is the snake's End Cell Position
	int Type;
public:

	Snake(const CellPosition & startCellPos, const CellPosition & endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a snake from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of the snake by moving player to snake's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member


	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);	// Saves the GameObject parameters to the file --> feel free to change this prototype as needed
	virtual void Load(ifstream& Infile, Grid* pGrid, int typ);	// Loads and Reads the GameObject parameters from the file --> feel free to change this prototype as needed

	virtual ~Snake(); // Virtual destructor
};

