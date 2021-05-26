#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	do{

	do
	{
	pOut->PrintMessage("New Snake: Click on its valid Start Cell ...");
	from = pIn->GetCellClicked();
	}while(from.IsValidCell()==false);

	// Read the endPos parameter
	do
	{
	pOut->PrintMessage("New Snake: Click on its Valid End Cell ...");
	to = pIn->GetCellClicked();
	}while(to.IsValidCell()==false);

	}while(to.HCell()!=from.HCell()  || to.GetCellNum()>=from.GetCellNum());

    

	///TODO: Make the needed validations on the read parameters

	

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddSnakeAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	Snake * pSnake = new Snake(from, to);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pSnake);

	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddSnakeAction

}
