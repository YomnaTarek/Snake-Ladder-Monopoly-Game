#include "card12.h"
#include<fstream>
card12::card12(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 12;// set the inherited cardNumber data member with the card number (12 here)
	name="000";
}

card12::~card12(void)
{
}

void card12::ReadCardParameters(Grid * pGrid)
{
	pGrid->PrintErrorMessage("wooow Take any city enter its name,click to continue :)");
	name=pGrid->GetInput()->GetSrting(pGrid->GetOutput());
	pGrid->GetOutput()->ClearStatusBar();
}

void card12::Apply(Grid* pGrid, Player* pPlayer)
{    
	if(name=="Cairo")
		        pGrid->setmonopoly(7,pPlayer->getpnum());
	else if(name=="Alexandria")
				pGrid->setmonopoly(8,pPlayer->getpnum());
	else if(name=="Aswan")
				pGrid->setmonopoly(9,pPlayer->getpnum());
	else if(name=="Luxor")
				pGrid->setmonopoly(10,pPlayer->getpnum());
	else if(name=="Hurghada")
				pGrid->setmonopoly(7,pPlayer->getpnum());
	else
		pGrid->PrintErrorMessage("INVALID CITY NAME");
}


void card12::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	Card::Save(OutFile, pGrid, typ);
	OutFile << name << endl;
}
void card12::Load(ifstream& InFile, Grid* pGrid, int typ)
{
	
	InFile >> name;

}