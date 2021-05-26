#include "Offer.h"

#include "Input.h"
#include "Output.h"
#include"Player.h"


Offer::Offer(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

Offer::~Offer()
{
}

void Offer::ReadActionParameters() 
{	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	int x=0;int y=0;
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Output* pout=pManager->GetGrid()->GetOutput();
	Input* pin=pManager->GetGrid()->GetInput();
	do{
	     pout->PrintMessage("Enter the card number 7-11,click ");
	     pin->GetPointClicked(x,y);
	     cardNumber=pin->GetInteger(pout);
	}while(cardNumber<7||cardNumber>11);
	pout->ClearStatusBar();
	// 5- Clear status bar
}

void Offer::Execute() 
{
	Grid* pgrid=pManager->GetGrid();
	string check;
	int pplayer;
	if(pgrid->GetCurrentPlayer()->getpnum()-1<0)  // same logic as in accept check Accept.cpp
		pplayer=3;
	else
		pplayer=pgrid->GetCurrentPlayer()->getpnum()-1;
	do{
		ReadActionParameters();
		pgrid->offer(cardNumber,pplayer); // make the city chosen offer value as true and in the procces calls other functions in monobly cards to check its state for further validations (check Cards 7-11)
		if(pgrid->checkoffer(cardNumber,pplayer)) // if the previous line was ok this function return true 
			pgrid->PrintErrorMessage("MORTGAGE set ,click to procced.....");
		else
			pgrid->PrintErrorMessage("ERROR city not on grid or not owned or already offered ,click to return.....");  // validations in line 48 func.
		pgrid->PrintErrorMessage("DO YOU WANT TO ENTER ANOTHER MORTGAGE?? Click then enter y/n");
		check=pgrid->GetInput()->GetSrting(pgrid->GetOutput());
	}while(check=="y");
	pgrid->UpdateInterface();
}
