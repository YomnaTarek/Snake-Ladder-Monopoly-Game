#include "card15.h"
#include<fstream>
card15::card15(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 15;// set the inherited cardNumber data member with the card number (15 here)
    turns=0;
}

card15::~card15(void)
{
}

void card15::ReadCardParameters(Grid * pGrid)
{
	do{
	    pGrid->PrintErrorMessage("BenefitAll Card selected ,click and enter the number of POSITIVE turns....");
		turns=pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(turns<0);
}

void card15::Apply(Grid* pGrid, Player* pPlayer)
{  
	pGrid->PrintErrorMessage("Nice luck benefit all reached fees are yours for some turns ,click to proceed:):)");
	pPlayer->setturns(turns); //set  the benefit switch to this turns +1 for a setting in roll dice note that if two players got the benefit card the player with smaller player number take as first come first serve
	pGrid->GetOutput()->ClearStatusBar();
}



void card15::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	Card::Save(OutFile, pGrid, typ);
	OutFile << turns << endl;
}
void card15::Load(ifstream& InFile, Grid* pGrid, int typ)
{
	
	InFile >> turns;

}