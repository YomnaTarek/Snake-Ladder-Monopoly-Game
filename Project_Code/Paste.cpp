#include "Paste.h"

#include "Input.h"
#include "Output.h"
#include "CoinSet.h"
#include"Card.h"

Paste::Paste(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pManager = pApp;
}

Paste::~Paste()
{
}

void Paste::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// Read the CardOrCoinCell parameter
	pGrid->PrintErrorMessage("Pasting a card or coinset: Double Click on the destination cell ...");
	CardOrCoinDestCell = pIn->GetCellClicked();


	///Make the needed validations on the read parameters
	if (CardOrCoinDestCell.IsValidCell() == 0)
	{
		pGrid->PrintErrorMessage("Error: Invalid Cell!!");
		return;
	}

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void Paste::Execute()
{
	//1-The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	//2- Call GetClipboard function
	GameObject*GameObj= pGrid->GetClipboard();
	if (GameObj == NULL)
	{
		pGrid->PrintErrorMessage("There is no card/coinset to paste...");
		return;
	}
	if(pGrid->getcopyorcut()==0)   // checks if the pasting action is from copy or cut so as if cut change the cellposition 
	{
		bool added=pGrid->Paste(GameObj, CardOrCoinDestCell);
	
	if (!added)
	{
		pGrid->PrintErrorMessage("A game object already exists...click to return");
		return;
	}
	}
	else if(pGrid->getcopyorcut()==1)
	{
		bool added=pGrid->Paste(GameObj, CardOrCoinDestCell);
		GameObj->SetPosition(CardOrCoinDestCell);
		if (!added)
	{
		pGrid->PrintErrorMessage("A game object already exists...click to return");
		return;
	}
	}
	

	// Here, the Card/CoinSet is pasted to the destination cell, so we finished executing the Paste action
	pGrid->UpdateInterface();
}
