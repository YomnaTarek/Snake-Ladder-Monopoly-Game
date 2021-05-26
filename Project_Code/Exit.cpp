#include "Exit.h"
#include"Input.h"
#include"Output.h"



Exit::Exit(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

Exit::~Exit()
{
}

void Exit::ReadActionParameters()
{

}

void Exit::Execute()
{
	Grid* pgrid = pManager->GetGrid();
	Input* in = pgrid->GetInput();
	Output* out = pgrid->GetOutput();
	pgrid->PrintErrorMessage("are you sure you want to exit the game ?? y/n");
	string choice = in->GetSrting(out);
	if (choice == "y")
		pgrid->RemoveGrid();    // this function make any needed cleanups for all the grid gameobjects and/or cells and/or players if any
	else
		return;
}
