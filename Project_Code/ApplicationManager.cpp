#include "ApplicationManager.h"


#include "AddLadderAction.h"
#include "AddCardAction.h"
#include"AddSnakeAction.h"
#include "RollDiceAction.h"
#include"AddCoinsetAction.h"
#include"CopyCardorCoin.h"
#include"CutCardorCoin.h"
#include"Paste.h"
#include"DiceValue.h"
#include"Delete.h"
#include"Offer.h"
#include"Accept.h"
#include"Return.h"
#include"Sell.h"
#include"NewGame.h"
#include"SaveGrid.h"
#include"OpenGridAction.h"
#include"SwitchToDesignMode.h"
#include"Exit.h"
#include"toplay.h"

///TODO: Add #include for all action types

ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid * ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_LADDER:
		pAct = new AddLadderAction(this);
		break;

	case ADD_SNAKE:
		pAct = new AddSnakeAction(this);
		break;

	case ADD_COINSET:
		pAct = new AddCoinsetAction(this);
		break;

	case ADD_CARD:
		// create an object of AddCardAction here
		pAct = new AddCardAction(this);
		break;

	case COPY:
	    pAct =new CopyCardorCoin(this);
		break;

	case CUT:
		pAct = new CutCardorCoin(this);
		break;

	case PASTE:
		pAct = new Paste(this);
		break;

	case DELETES:
		pAct = new Delete(this);
		break;

	case SAVEGRID:
		pAct = new SaveGrid(this);
	break;

	case OPENGRID:
		pAct = new OpenGridAction(this);
		break;

	case TO_PLAY_MODE:
		pAct = new toplay(this);
		break;

	case EXIT:
		pAct = new Exit(this);
		break;
	
/////////////////////////////////////////////////////////////////
	case ROLL_DICE:
		// create an object of RollDiceAction here
		pAct = new RollDiceAction(this);
		break;
   
	case Dice_value:
		pAct = new DiceValue(this);
		break;

	case OMOR:
		pAct = new Offer(this);
		break;

	case AMOR:
		pAct = new Accept(this);
		break;//Accept mortgage

	case RMOR:
		pAct = new Return(this);
		break;

	case SELL:
		pAct = new Sell(this);
		break;

	case NEWGAME:
		pAct = new NewGame(this);
		break;

	case TO_DESIGN_MODE:
	pAct = new SwitchToDesignMode(this);
	break;

	

		

		///TODO: Add a case for EACH Action type in the Design mode or Play mode



	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
