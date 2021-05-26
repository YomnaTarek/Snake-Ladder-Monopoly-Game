#include "CopyCardOrCoin.h"

#include "Input.h"
#include "Output.h"
#include "CoinSet.h"
#include"Card.h"

CopyCardorCoin::CopyCardorCoin(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pManager = pApp;
}

CopyCardorCoin::~CopyCardorCoin()
{
}

void CopyCardorCoin::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// Read the CardOrCoinCell parameter
	pGrid->PrintErrorMessage("Copying a card or coinset: Double Click on the source cell you wish to copy ...");
	CardOrCoinCell = pIn->GetCellClicked();
	

	///Make the needed validations on the read parameters
	if (CardOrCoinCell.IsValidCell() == 0)
	{
		pGrid->PrintErrorMessage("Error: Invalid Cell!!");
		return;
	}

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void CopyCardorCoin::Execute()
{
	//1-The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	Grid*pGrid=pManager->GetGrid();
	//2-make sure CardOrCoinCell does not have ladder or snake , if it does, return and print error message
	//3-SetClipboard
	GameObject* GameObj = pGrid->GetCardOrCoins(CardOrCoinCell);

	 if (GameObj!=NULL)
	 { 
		 pGrid->SetClipboard(GameObj,0);  // set the clipboard value by the selected one 
	 }
	 else 
	 {
		 pGrid->PrintErrorMessage("Error:This cell cannot be copied...click to return ");
		 return;
	 }
	
	// Here, the Card/CoinSet is copied and added to the Clipboard, so we finished executing the CopyCardOrCoinsAction
	pGrid->UpdateInterface();
}
