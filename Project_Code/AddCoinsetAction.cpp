
#include "Input.h"
#include "Output.h"
#include "AddCoinsetAction.h"
#include"coinset.h"

AddCoinsetAction::AddCoinsetAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCoinsetAction::~AddCoinsetAction()
{
}

void AddCoinsetAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x=0;int y=0;
	// Read the wallet value parameter
	do{
		pGrid->GetOutput()->PrintMessage("Enter a positive value of the coinset,click to continue");
		pGrid->GetInput()->GetPointClicked(x,y);
		wallet=pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(wallet<0);
    
	do{
		pGrid->GetOutput()->PrintMessage("Click on a cell to add the coinset");
		pos=pGrid->GetInput()->GetCellClicked();
	}while(pos.IsValidCell()==false);

	///TODO: Make the needed validations on the read parameters

	

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddCoinsetAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	CoinSet * pcoin = new CoinSet(pos,wallet);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pcoin);

	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the coinset is created and added to the GameObject of its Cell, so we finished executing the AddCoinSetAction

}
