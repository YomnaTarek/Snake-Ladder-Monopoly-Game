#include "DiceValue.h"

#include "Grid.h"
#include "Player.h"
#include"Ladder.h"
#include"Card.h"
#include <time.h> // used to in srand to generate random numbers with different seed

DiceValue::DiceValue(ApplicationManager *pApp) : Action(pApp)
{
}

void DiceValue::ReadActionParameters()
{
	// no parameters to read from user
}

void DiceValue::Execute()
{
	 Player * current=pManager->GetGrid()->GetCurrentPlayer();	
	
	 if(current->getfreeze()!=0)    //decremetns the freeze count if the player turn reacehd and prevent him from taking his turn 
	{
		current->setfreeze(current->getfreeze()-1);
		pManager->GetGrid()->GetOutput()->PrintMessage("You are frozen wait for some turns :(");
		pManager->GetGrid()->AdvanceCurrentPlayer();
		return;
	}


	 if(current->getturns()!=0) //  decrements the player turns count(brnfit switch counter if the palyer turn is reached
	 {
		 current->setturns(current->getturns()-1);
	 }

	if(current->getprevented())    //same thing but in prevented i just remove thr prevented check to false 
	{
		pManager->GetGrid()->AdvanceCurrentPlayer();
		pManager->GetGrid()->GetOutput()->PrintMessage("you are prevented wait for your next turn :(");
		current->setprevented(false);
		return;
	}
	

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	// -- If not ended, do the following --:
	int diceNumber; 
	do{
	pManager->GetGrid()->PrintErrorMessage("enter the POSITIVE value of dicenumber manually,click and enter");
	diceNumber=pManager->GetGrid()->GetInput()->GetInteger(pManager->GetGrid()->GetOutput());
	}while(diceNumber<=0);  // this is a testing action so no need to limit the dice value to 6 for testing needs ..
	
	// 3- Get the "current" player from pGrid
	// all the rest of the action is the same as roll dice
	 current->Move(pManager->GetGrid(),diceNumber);
	 if(pManager->GetGrid()->GetEndGame()==true)
	 {
		 pManager->ExecuteAction(EXIT);
	 }
	 pManager->GetGrid()->AdvanceCurrentPlayer();
	 pManager->GetGrid()->GetOutput()->ClearStatusBar();
	 pManager->GetGrid()->UpdateInterface();
	 
	// 4- Move the currentPlayer using function Move of class player
     
	// 5- Advance the current player number of pGrid
     
	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).

}

DiceValue::~DiceValue()
{

}