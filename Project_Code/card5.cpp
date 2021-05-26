#include "card5.h"
#include<fstream>

card5::card5(const CellPosition & position ) :Card(position)
{
	cardNumber=5;// set the inherited cardNumber data member with the card number (5 here)
}
void card5::ReadCardParameters(Grid * pGrid)
{
}


void card5::Apply(Grid* pGrid, Player* pPlayer)
{
	pGrid->PrintErrorMessage("Fire Card reached, you are lucky!");

	int v= pPlayer->GetCell()->GetCellPosition().VCell();
	int h=pPlayer->GetCell()->GetCellPosition().HCell();
	for(int i=0;i<4;i++)
	{
		if(pPlayer->getpnum()==i) //if the player on the card do nothing
		{}
		else
		{
			if(pGrid->fire(i,v,h))   //fire is grid function that loops over playerlist and check if Vcell or Hcell of that player(i) match that of pPlayer ,return true or false
			{
				Player* play=pGrid->getplayer(i);
				CellPosition tem(1);
				pGrid->UpdatePlayerCell(play,tem);
				play->SetWallet(play->GetWallet()/2);
			}
		}
	}
}
void card5::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	Card::Save(OutFile, pGrid, typ);
	OutFile << endl;

}
void card5::Load(ifstream&InFile, Grid* pGrid, int typ)
{
	

}


card5::~card5(void)
{
}
