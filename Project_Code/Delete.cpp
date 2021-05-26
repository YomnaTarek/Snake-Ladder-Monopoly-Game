#include "Delete.h"

#include "Input.h"
#include "Output.h"
#include "GameObject.h"

Delete::Delete(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pManager = pApp;
}

Delete::~Delete()
{
}

void Delete::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the GameObjCell parameter
	pOut->PrintMessage("Deleting GameObject: Click on its Cell ...");
	GameObjCell = pIn->GetCellClicked();
	bool HasGameObj = pGrid->getobject(GameObjCell);
	///Make the needed validations on the read parameters
	if (GameObjCell.IsValidCell() == 0 || HasGameObj==0)
	{
		pGrid->PrintErrorMessage("Error: Invalid Cell/ Cell does not have game object...");
		return;
	}
	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void Delete::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	//Remove the game object from the cell
	pGrid->RemoveObjectFromCell(GameObjCell);

	// Here, the gameobject is successfull removed from the cell, so we finished executing the DeleteGameObject
	pGrid->UpdateInterface();
}
