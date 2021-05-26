#pragma once
#include"Card.h"
class card4 :	public Card
{
	int prevent; 

public:
	card4(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of PreventCard_4 which is: the number of player who will be prevented

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of PreventCard_4
													  //the current player chooses one of the other players to prevent from rolling the next turn
	void reset();
	virtual ~card4(); // A Virtual Destructor
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual void Load(ifstream& InFile, Grid* pGrid, int typ);
};

