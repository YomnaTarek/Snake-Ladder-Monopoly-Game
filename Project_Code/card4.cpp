#include "card4.h"
#include<fstream>

card4::card4(const CellPosition & position ) :Card(position)
{
	cardNumber=4;// set the inherited cardNumber data member with the card number (4 here)
	prevent=4;
}
void card4::ReadCardParameters(Grid * pGrid)
{
	int z; int n;
		pGrid->PrintErrorMessage("Prevent Card reached, DOUBLE CLICK on the player that you want to prevent...");
		do{
	                n=(pGrid->GetInput()->GetCellClicked()).GetCellNum();
	                z=pGrid->getplayeri(n);    //get player i  is a grid function that loops over all the palyers and  check if their cell num is the passed one and returns their int (0-3) or 4 if not found
	         if(z==4)
		            pGrid->PrintErrorMessage("CELL HAS NO PLAYERS reclick");
	         else
	       {
		     prevent=z;
			 pGrid->GetOutput()->ClearStatusBar();
	       	return;
	       }
		}while(prevent==4);   //retry if empty cell clicked
	
}
void card4::reset()
{
	prevent=4;
}


void card4::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);
	pGrid->getplayer(prevent)->Move(pGrid,0);   // this line simply calls the move function with o diceroll to increment the turncount when prevented 	
	pGrid->getplayer(prevent)->setprevented(true);  // setting the prevented bool to true to prevent the player from rolling the dice in action rolldice but as i just said his turncount is incremented in the above line
}
void card4::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	Card::Save(OutFile, pGrid, typ);
	OutFile << endl;
}
void card4::Load(ifstream& InFile, Grid* pGrid, int typ)
{
	
}


card4::~card4(void)
{
}
