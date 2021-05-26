#include "SwitchToDesignMode.h"
#include<fstream>
#include"Player.h"

SwitchToDesignMode::SwitchToDesignMode(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pManager = pApp;
}

SwitchToDesignMode::~SwitchToDesignMode()
{
}


void SwitchToDesignMode::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the GameObjCell parameter
	 pGrid->PrintErrorMessage("Are you sure you want to end this game? click then enter y for yes, n for no...");
	 choice = pIn->GetSrting(pOut);
	

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void SwitchToDesignMode::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	int maxwallet = 0;//gets highest wallet value
	int AllWallets[4];//array of wallet values
	int dup = 0;//gets duplicates with max wallet value
	int maxstepcount = 1;//gets highest step count
	int finali = 0;//this is the index of the final winner 
	if (choice=="y")
	{
		//1-Get the wallet values in an array
		for (int i = 0;i < 4;i++)
		{
			AllWallets[i] = pGrid->getplayer(i)->GetWallet();

		}
		//2-Get the max wallet value
		for (int i = 0;i < 4;i++)
		{
			if (AllWallets[i] > maxwallet)
			{
				maxwallet = AllWallets[i];

			}
		}
		//3- check if more than one player has the same max wallet value
		for (int i = 0;i < 4;i++)
		{
			if (pGrid->getplayer(i)->GetWallet() == maxwallet)
			{
				dup++;
			}
		}
		if (dup == 0)
		{
			finali = pGrid->GetPlayerMax(maxwallet);//gets winner
			pOut->PrintMessage("Player " + to_string(finali) + " is the winner with wallet value " + to_string(maxwallet) + ",click to continue...");
			pIn->GetPointClicked(x, y);
			pOut->CreateDesignModeToolBar();
			pGrid->New();
		}
		else
		{
			for (int i = 0;i < 4;i++)
			{
				if (pGrid->getplayer(i)->GetWallet() == maxwallet)
				{
					if (pGrid->getplayer(i)->GetCell()->GetCellPosition().GetCellNum() > maxstepcount)
					{
						maxstepcount = pGrid->getplayer(i)->GetCell()->GetCellPosition().GetCellNum();
						finali = i;
					}
				}
			}
			pGrid->PrintErrorMessage("Player " + to_string(finali) + " is the winner with wallet value " + to_string(maxwallet) + ",click to continue...");
			pOut->CreateDesignModeToolBar();
			pGrid->New();

		}
	}
	else
	{
		return;
	}
}
