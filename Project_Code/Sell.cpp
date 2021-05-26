#include "Sell.h"

#include "Input.h"
#include "Output.h"
#include"Player.h"
#include"Card.h"

Sell::Sell(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

Sell::~Sell()
{
}

void Sell::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// Read the wallet value parameter
	do{
		pGrid->PrintErrorMessage("Enter the value of the city you want to sell(((7-11))) if there,click and enter");
		cardNumber=pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(cardNumber<7||cardNumber>11);
	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void Sell::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	Grid* pgrid = pManager->GetGrid();
	int pplayer;
	string yesno;
	if(pgrid->GetCurrentPlayer()->getpnum()-1<0)
		pplayer=3;
	else
		pplayer=pgrid->GetCurrentPlayer()->getpnum()-1;
	
    
	do
	{
      ReadActionParameters();
	  if (pgrid->getcity(cardNumber) == NULL)
	  {
		  pgrid->PrintErrorMessage("City is not on the grid,click to return...");
		  return;
	  }
	  Card* cards = pgrid->getcity(cardNumber);
	  if(cards->gettaken()==pplayer && cards->getmor()==5) // check that it is not mortaged  check cards(7-11) for further details 
	  {
		  Player* owner = pgrid->getplayer(pplayer);
		  owner->SetWallet(owner->GetWallet() + (cards->getprice()/100)*90); // return 90% of the city price 
		  pgrid->setmonopoly(cardNumber,5);// 5 is the default value of a non taken city 
	  }
	  else
	  {
		  pgrid->PrintErrorMessage("ERROR....City may not yours or mortaged return mortage to sell it ,click to return");
		  return;
	  }
	  pgrid->PrintErrorMessage("Do you want to sell another city?? click then enter y/n");
	  yesno = pgrid->GetInput()->GetSrting(pgrid->GetOutput());
	  pgrid->UpdateInterface();
	}while(yesno =="y");
}
