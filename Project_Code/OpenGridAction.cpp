#include "OpenGridAction.h"
#include<fstream>
#include"Ladder.h"
#include"snake.h"
#include"coinset.h"
#include"Card.h"

OpenGridAction::OpenGridAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pManager = pApp;
}

OpenGridAction::~OpenGridAction()
{
}

void OpenGridAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->ClearGridArea();
	pGrid->RemoveAllObjects();
	// Read the filename parameter
	pOut->PrintMessage("Loading the grid: Please enter the filename...");
	Filename = pIn->GetSrting(pOut);
	
	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void OpenGridAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	Output* pOut = pGrid->GetOutput();
	ifstream InFile(Filename,ios::in);
	int cl, cs, ccs, cc;
	CellPosition startpos, endpos;
	int amount=0;

	if (InFile.is_open())
	{
		InFile >> cl;
		for (int i = 0;i < cl;i++)
		{
			Ladder L1(startpos, endpos);
			L1.Load(InFile, pGrid, 1);
			Ladder* pLad = &L1;
			pGrid->AddObjectToCell(pLad);
		}


		InFile >> cs;
		for (int i = 0;i < cs;i++)
		{
			Snake S1(startpos, endpos);
			S1.Load(InFile, pGrid, 2);
			Snake* pSnake = &S1;
			pGrid->AddObjectToCell(pSnake);
			
		}


		InFile >> ccs;
		for (int i = 0;i < ccs;i++)
		{

			CoinSet CS1(startpos, amount);
			CS1.Load(InFile, pGrid, 3);
			CoinSet* pCoinSet = &CS1;
			 pGrid->AddObjectToCell(pCoinSet);
			
		}

	InFile >> cc;
	for (int i = 0;i < cc;i++)
	{
		Card C1(startpos);
		C1.Load(InFile, pGrid, 4);
		Card* poCard = &C1;
		pGrid->AddObjectToCell(poCard);

	}
		
		InFile.close();
	}
	// Here, the grid is successfull loaded , so we finished executing the OpenGridAction
	pGrid->UpdateInterface();
}
