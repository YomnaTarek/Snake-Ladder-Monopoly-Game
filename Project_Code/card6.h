#pragma once
#include"Card.h"
class card6 :	public Card
{
	int eo;// represents odd or even
	int turns;// number of turns to freeze
public:
	card6(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of FreezeCard_6 which is: eo and turns

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of FreezeCard_6 on the passed Player 
													  // Freezes the other players that are currently in odd/even cells for specific number of turns
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual void Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual ~card6(); // A Virtual Destructor
};

