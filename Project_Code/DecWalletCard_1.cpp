#include "DecWalletCard_1.h"
#include<fstream>
DecWalletCard_1::DecWalletCard_1(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1;// set the inherited cardNumber data member with the card number (1 here)
	walletAmount=0;
}

DecWalletCard_1::~DecWalletCard_1(void)
{
}

void DecWalletCard_1::ReadCardParameters(Grid * pGrid)
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	pGrid->GetOutput()->PrintMessage("New DecWalletCard_1:enter its wallet amount....");
	int x=0; int y=0;
	pGrid->GetInput()->GetPointClicked(x,y);
	 walletAmount=pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	 pGrid->GetOutput()->ClearStatusBar();
	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New DecWalletCard_1: Enter its wallet amount ..."
	

	// [ Note ]:
	// In DecWalletCard_1, the only parameter of DecWalletCard_1 is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar

}

void DecWalletCard_1::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
    Card::Apply(pGrid,pPlayer);
	if(pPlayer)
	{
		int c=pPlayer->GetWallet();
		c=c-walletAmount;
		pPlayer->SetWallet(c);
	}
	// 2- Decrement the wallet of pPlayer by the walletAmount data member of DecWalletCard_1

}

void DecWalletCard_1::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	Card::Save(OutFile,pGrid, typ);
	OutFile << walletAmount << endl;
}
void DecWalletCard_1::Load(ifstream& InFile, Grid* pGrid, int typ)
{ 
	InFile >> walletAmount;


}