#include "card13.h"
#include<fstream>
card13::card13(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 13;// set the inherited cardNumber data member with the card number (13 here)
}

card13::~card13(void)
{
}

void card13::ReadCardParameters(Grid * pGrid)
{
	
}

void card13::Apply(Grid* pGrid, Player* pPlayer)
{    int h=5;  // intialize with 5 to change to(0-3) in function as it is sent by refrence 
	int x=pGrid->getmaxcity(pPlayer->getpnum(),h);     //get max city is  grid function that loops over all cities and if the city belongs to (this player) check if it is mortaged and return the mortaged to player(h)
	if(x>=7&&x<=11 &&   h==5)
		pGrid->setmonopoly(x,5);   //h=5 means that the max city is not mortgaged so call set monobly and make this city(x) free for anybody

	else if(x>=7&&x<=11&&  h!=5)
		pGrid->setmonopoly(x,h);   //h!=5 means that the max city is mortgaged to anothe playe rso set the taken of this city to motgaged and here the city taken and mor values are the same but don't worry check the last case in any city card apply
	else
		pGrid->PrintErrorMessage("You have no cities,click to return "); 
}

void card13::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	Card::Save(OutFile, pGrid, typ);
	OutFile << endl;
}
void card13::Load(ifstream& InFile, Grid* pGrid, int  typ)
{
	

}