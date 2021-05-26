#pragma once
#include"Card.h"
class Nextcard : public Card
{
	// NextCard_2 Parameters:
	int GameNum; // the number that represents the game object

public:
	Nextcard(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of NextCard_2 which is: game
	void SetObjectNum(int Obj);//a setter for object
	int GetObjectNum();//a getter for object
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of NextCard_2 on the passed Player
	                                                  //by moving the current player to the next chosen gameobject
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual void Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual ~Nextcard(); // A Virtual Destructor
};

