#include "Return.h"

#include "Input.h"
#include "Output.h"
#include"Player.h"
#include"Card.h"

Return::Return(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

Return::~Return()
{
}

void Return::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// Read the wallet value parameter
	do{
		pGrid->PrintErrorMessage("Enter the value of the city you want to return its mortgage (((7-11))) if there,click and enter");
		cardNumber=pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(cardNumber<7||cardNumber>11);
	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void Return::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	Grid* pgrid = pManager->GetGrid();
	int pplayer;
	string yesno;
	if(pgrid->GetCurrentPlayer()->getpnum()-1<0)// check Accept.cpp execute for further details on the logic of this line 
		pplayer=3;
	else
		pplayer=pgrid->GetCurrentPlayer()->getpnum()-1;
    
	do
	{
      ReadActionParameters();
	  if(pgrid->checkmortgage(cardNumber,pplayer))
	  {
		  Card* cards = pgrid->getcity(cardNumber);
		  int mortgaged= cards->getmor();
		  Player* morta = pgrid->getplayer(mortgaged);
		  Player* owner = pgrid->getplayer(pplayer);
		  morta->SetWallet(morta->GetWallet() + (cards->getprice()/100)*70);  // return the 70% mortgage value to the accepting player 
		  owner->SetWallet(owner->GetWallet() - (cards->getprice()/100)*70);
		  pgrid->setmorta(cardNumber,5);// 5 is the default value of a non mortgaged city  // make this city not mortgaged 
	  }
	  else
	  {
		  pgrid->PrintErrorMessage("ERROR....City may not be on grid or not mortgaged or not even yours,click to return");
		  return;
	  }
	  pgrid->PrintErrorMessage("Do you want to return another city from its mortgage?? click then enter y/n");
	  yesno = pgrid->GetInput()->GetSrting(pgrid->GetOutput());
	  pgrid->UpdateInterface();
	}while(yesno =="n");
}
