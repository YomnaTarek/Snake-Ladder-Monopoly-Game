#include "card14.h"
#include<fstream>
card14::card14(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 14;// set the inherited cardNumber data member with the card number (14 here)
}

card14::~card14(void)
{
}

void card14::ReadCardParameters(Grid * pGrid)
{
	
}

void card14::Apply(Grid* pGrid, Player* pPlayer)
{  
	int x=pGrid->morta(pPlayer->getpnum());  //morta grid function loops over the celllist and check if the passed player cards and gets the min of the mortaged cities(returns its cardnumber)
	if(x>=7&&x<=11)
	{
		pGrid->setmorta(x,5);   // this lines make this city become mortaged free from the owner player 
		pGrid->PrintErrorMessage("City retaken for free :),click to contineu");
	}
	else
		pGrid->PrintErrorMessage("You have no mortaged cities,click to return");
}
void card14::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	Card::Save(OutFile, pGrid, typ);
	OutFile << endl;
}
void card14::Load(ifstream& InFile, Grid* pGrid, int  typ)
{

}