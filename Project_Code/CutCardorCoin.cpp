#include "CutCardorCoin.h"

#include "Input.h"
#include "Output.h"
#include "CoinSet.h"
#include"Card.h"

CutCardorCoin::CutCardorCoin(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pManager = pApp;
}

CutCardorCoin::~CutCardorCoin()
{
}

void CutCardorCoin::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// Read the CardOrCoinCell parameter
	pGrid->PrintErrorMessage("Cutting a card or coinset: Double Click on the source cell you wish to cut ...");
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
void CutCardorCoin::Execute()
{
	//1-The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	//2-make sure CardOrCoinCell does not have ladder or snake , if it does, return and print error message
	//3-SetClipboard and remove the object from the source cell
	GameObject* GameObj = pGrid->GetCardOrCoins(CardOrCoinCell);
	if (GameObj)
	{
		pGrid->SetClipboard(GameObj,1);
		pGrid->RemoveObjectFromCell(CardOrCoinCell);
	}
	else
	{
		pGrid->PrintErrorMessage("Error:This cell cannot be cut...");
		return;
	}

	// Here, the Card/CoinSet is cut and added to the Clipboard, so we finished executing the CutCardOrCoinsAction
	pGrid->UpdateInterface();
}