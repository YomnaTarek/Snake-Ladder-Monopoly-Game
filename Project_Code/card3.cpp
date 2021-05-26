#include "card3.h"
#include<fstream>
card3::card3(const CellPosition & position ) :Card(position)
{
	cardNumber=3;//set the inherited cardNumber data member with the card number(3 here)
}
void card3::ReadCardParameters(Grid * pGrid)
{
	int x=0; int y=0;
	pGrid->GetOutput()->PrintMessage("Backward card chosen, place it wisely");
	pGrid->GetInput()->GetPointClicked(x,y);
	pGrid->GetOutput()->ClearStatusBar();

}


void card3::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
    Card::Apply(pGrid,pPlayer);
	int c=pPlayer->getjust();
	for(int i=0;i<4;i++)
	{
		if(pPlayer->getpnum()==i)
		{}
		else
		{
			Player* playert=pGrid->getplayer(i);
			int cellnum=(playert->GetCell()->GetCellPosition()).GetCellNum();
			CellPosition tem(cellnum);
				tem.AddCellNum(-c);
				pGrid->UpdatePlayerCell(playert,tem);
				if(playert->GetCell()->GetGameObject()!=NULL)
					playert->GetCell()->GetGameObject()->Apply(pGrid,playert);
		}
	}
}

void card3::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	Card::Save( OutFile, pGrid, typ);
	OutFile << endl;

}
void card3::Load(ifstream& InFile, Grid* pGrid, int typ)
{
	
}
card3::~card3(void)
{
}
