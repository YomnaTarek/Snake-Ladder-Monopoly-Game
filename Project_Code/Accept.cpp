#include "Accept.h"

#include "Input.h"
#include "Output.h"
#include"Player.h"
#include"Card.h"


Accept::Accept(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

Accept::~Accept()
{
}

void Accept::ReadActionParameters() 
{	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	int x=0;int y=0;
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Output* pout=pManager->GetGrid()->GetOutput();
	Input* pin=pManager->GetGrid()->GetInput();
	do{
	     pout->PrintMessage("Enter the card number 7-11 you want to accept its offer,click ");
	     pin->GetPointClicked(x,y);
	     cardNumber=pin->GetInteger(pout);
	}while(cardNumber<7||cardNumber>11);
	pout->ClearStatusBar();
	// 5- Clear status bar
}

void Accept::Execute() 
{
	Grid* pgrid=pManager->GetGrid();
	Output* pout = pManager->GetGrid()->GetOutput();
	Input* pin = pManager->GetGrid()->GetInput();
	int pplayer;
	string choice;
	if(pgrid->GetCurrentPlayer()->getpnum()-1<0)  // as in the document the player that offer or Accept must be th eone that just rolled the dice and as roll dice advance the player after each roll so the player that uses this action is current -1
		pplayer=3; // a corner case if the player that just rolled the dice is player 3 so advance player will make the current to be 0 so 0-1 means 3 
	else
		pplayer=pgrid->GetCurrentPlayer()->getpnum()-1;
	do {
		ReadActionParameters();
		if (pgrid->getplayer(pplayer)->GetWallet() < pgrid->getcity(cardNumber)->getprice() * (70 / 100)) //checks first if the player do have in his wallet the 70%  not to waste useless if conditions if not 
		{
			pgrid->PrintErrorMessage("You don't have money to pay the owner 70% of city price");
			return;
		}
		if (pgrid->checkaccept(cardNumber, pplayer)) //checkaccept checks on the grid if the city is already there and if it is already offered for mortgage 
		{
			Player* owner = pgrid->getplayer(pgrid->getcity(cardNumber)->gettaken()); //get the owner player 
			Player* about_to_mortgage = pgrid->getplayer(pplayer);  // gets the player that pressed the action 
			pgrid->accept(cardNumber, pplayer);   // mark this city as accepted 
			int minus = about_to_mortgage->GetWallet() - (pgrid->getcity(cardNumber)->getprice() / 100) * (70); // decrents the walllet of the accepting player by the 70%
			about_to_mortgage->SetWallet(minus);
			int plus = owner->GetWallet() + (pgrid->getcity(cardNumber)->getprice() / 100) * (70);  //giving them to the owner player 
			owner->SetWallet(plus);
		}
		else
		{
			pgrid->PrintErrorMessage("Card not offered for mortgage or not there,click to return");
			return;
		}
		pgrid->PrintErrorMessage("do you want to accept other offers ??? y/n click then enter your choice ");
		choice = pin->GetSrting(pout);
	} while (choice=="y");
		pgrid->UpdateInterface();
}
