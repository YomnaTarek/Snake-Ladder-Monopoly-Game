#include "RollDiceAction.h"

#include "Grid.h"
#include "Player.h"
#include"Ladder.h"
#include"Card.h"
#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *pApp) : Action(pApp)
{
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{
	 Player * current=pManager->GetGrid()->GetCurrentPlayer();	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// for(int i=0;i<4;i++)     //in this step i count the turns that players are frozen in it a decrease them for every rolled dice 
	//	{   
	//		pManager->GetGrid()->getplayer(i)->setfreeze(current->getfreeze()-1);  // function set freeze is limited to a min of zero value so its okto make 0-1 ;)
	//	}
	// for(int i=0;i<4;i++)    //similar to the above loop this one decremetns the switch of the benefit all card
	//	{   
	//		pManager->GetGrid()->getplayer(i)->setturns(current->getturns()-1);   //also set turns is limited to zero so okay if card is not frozen
	//	}     //note that if u are worried that counts decrement before the coming if conditions this was tackled by increasig them by 1 :)
	 
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
		pManager->GetGrid()->GetOutput()->PrintMessage("You are prevented wait for your next turn :(");
		current->setprevented(false);
		return;
	}
	

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	// -- If not ended, do the following --:

	// 2- Generate a random number from 1 to 6 --> This step is done for you
	srand((int)time(NULL)); // time is for different seed each run
	int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed

	// 3- Get the "current" player from pGrid
	
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

RollDiceAction::~RollDiceAction()
{

}