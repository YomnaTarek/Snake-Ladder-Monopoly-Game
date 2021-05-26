#include "card6.h"
#include<fstream>

card6::card6(const CellPosition & position ) :Card(position)
{
	cardNumber=6;// set the inherited cardNumber data member with the card number (6 here)
	eo=-1;
	turns=0;
}
void card6::ReadCardParameters(Grid * pGrid)
{
	do{                                                                                 
		pGrid->PrintErrorMessage("Enter odd or even cells to freeze 1 for odd 0 for even");   //get the bool 1 for odd 0 for even
	    eo=pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(eo>1&&eo<0);

	do{
		pGrid->PrintErrorMessage("Enter the number of turns to freeze");           // get the number of turns to freeze the player 
	    turns=pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(turns<=0);
}


void card6::Apply(Grid* pGrid, Player* pPlayer)
{
	pGrid->PrintErrorMessage("Freeze card reached you are lucky click!");
	for(int i=0;i<4;i++)
	{
		if(pPlayer->getpnum()==i)
		{
		}
		else
		{
			Player* temp=pGrid->getplayer(i);
			if(pGrid->evenorodd(i,eo)==true)   //even or odd is a grid function that loops over player list taking the player's number and eo(even or odd)and if player is there it returns true else false
			{
				temp->setfreeze(turns);    //freeze a player data memebr that indicates the number of turns a player is frozen in it and +1 as the roll dice action decrements it at the start of any call(chek roll dice action to understand more
			}
		}
	}
	pGrid->GetOutput()->ClearStatusBar();
}


void card6::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	Card::Save(OutFile, pGrid, typ);
	OutFile << eo<<" "<<turns << endl;
}
void card6::Load(ifstream& InFile, Grid* pGrid, int typ)
{
	
	InFile >> eo;
	InFile >> turns;
}
card6::~card6(void)
{
}
