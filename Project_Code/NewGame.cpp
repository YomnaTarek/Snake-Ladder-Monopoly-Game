#include "NewGame.h"

#include "Input.h"
#include "Output.h"
#include"Player.h"
#include"Card.h"

NewGame::NewGame(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

NewGame::~NewGame()
{
}

void NewGame::ReadActionParameters() 
{	
	
}


// Execute the action
void NewGame::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	Grid* pgrid = pManager->GetGrid();
	pgrid->New();   // this functions calls the reset of all the gameobjects (including cards )and the reset of players (check player.cpp reset func.) 
	pgrid->UpdateInterface();
}
