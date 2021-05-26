#include "Nextcard.h"
#include<fstream>

Nextcard::Nextcard(const CellPosition & position ) :Card(position)
{
	cardNumber=2;//set the inherited cardNumber data member with the card number (2 here)
	GameNum =-1;
}
void Nextcard::ReadCardParameters(Grid * pGrid)
{ int x=0;int y=0;
	do{
		pGrid->GetOutput()->PrintMessage("Next card reached ,Where u want to go?? Enter 1-4 for objects");
		pGrid->GetInput()->GetPointClicked(x,y);
		GameNum =pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}
	while(GameNum <1|| GameNum>4);
		 pGrid->GetOutput()->ClearStatusBar();
}
void Nextcard::SetObjectNum(int Obj)
{
	if (Obj > 0 && Obj < 5)
	{
		GameNum = Obj;
	}
	else
	{
		return;
	}
}
int Nextcard::GetObjectNum()
{
	return GameNum;
}

void Nextcard::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
    Card::Apply(pGrid,pPlayer);
	if(pPlayer)
	{
		 GameObject* ptr= pGrid->GetNextGame(position, GameNum);   // object found so go to it ,,,,down if not found
		 if(ptr)
		 {
		 pGrid->UpdatePlayerCell(pPlayer,ptr->GetPosition());
		 ptr->Apply(pGrid,pPlayer);
		 }
		 else
		 {
			 CellPosition tem(1);
			 ptr=pGrid->GetNextGame(tem, GameNum);    // function in grid that have a start loop cell position and a gameobject int 1-4 it thrn returns a pointer to that object
			 if(ptr)
			 {
				 pGrid->UpdatePlayerCell(pPlayer,ptr->GetPosition());
				 ptr->Apply(pGrid,pPlayer);
			 }
			 else
			 {
				 pGrid->PrintErrorMessage("Game object not found");
				 return;
			 }
		 }
	}
}

Nextcard::~Nextcard(void)
{
}

void Nextcard::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	Card::Save(OutFile, pGrid,typ);
	OutFile << GameNum << endl;
}
void Nextcard::Load(ifstream& InFile, Grid* pGrid, int typ)
{
	
	InFile >> GameNum;

}