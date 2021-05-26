#include "SaveGrid.h"
#include<fstream>


SaveGrid::SaveGrid(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pManager = pApp;
}

SaveGrid::~SaveGrid()
{
}

void SaveGrid::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the GameObjCell parameter
	pOut->PrintMessage("Saving the grid: Please enter the filename...");
	Filename = pIn->GetSrting(pOut);

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void SaveGrid::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	int Ladders, Snakes, CoinSet, Cards;
	ofstream OutFile(Filename,ios:: trunc);
	
	if (OutFile.is_open())
	{
		Ladders = pGrid->HowManyGameObj(1);
		OutFile << Ladders << endl;
		pGrid->SaveAll(OutFile, pGrid, 1);
		
		Snakes = pGrid->HowManyGameObj(2);
		OutFile << Snakes << endl;
		pGrid->SaveAll(OutFile, pGrid, 2);
		
		CoinSet = pGrid->HowManyGameObj(3);
		OutFile << CoinSet << endl;
		pGrid->SaveAll(OutFile, pGrid, 3);
		
		Cards = pGrid->HowManyGameObj(4);
		OutFile << Cards << endl;
		pGrid->SaveAll(OutFile, pGrid, 4);
		OutFile.close();
	}
	else
	{
		return;
	}

	// Here, the grid is successfull saved , so we finished executing the SaveGridAction
	pGrid->UpdateInterface();
}
