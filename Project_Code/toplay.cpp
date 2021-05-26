#include"toplay.h"
#include"Input.h"
#include"Output.h"



toplay::toplay(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

toplay::~toplay()
{
}

void toplay::ReadActionParameters()  //there is no action parameters for this action 
{
	
}

void toplay::Execute()  // execution is asking the user if he/she wants to save the grid in a txt file then drawing the Play mode toolbar
{
	Grid* pgrid = pManager->GetGrid();
	Input* in = pgrid->GetInput();
	Output* out = pgrid->GetOutput();
	pgrid->PrintErrorMessage("Switching to play Mode Do You want to save the Grid in a Txt file ?? y,n click then enter your choice ....");
	string choice = in->GetSrting(out);
	out->ClearStatusBar();
	if (choice == "y")
	{
		pManager->ExecuteAction(SAVEGRID);   // if yes the savegrid action is called
		out->CreatePlayModeToolBar();
	}
	else
		out->CreatePlayModeToolBar();
	return;
	
}
