#include "Player.h"

#include "GameObject.h"
#include"Ladder.h"
#include"snake.h"
#include"Card.h"
#include"DecWalletCard_1.h"
#include"Nextcard.h"
#include"card3.h"
#include"card4.h"
#include"card5.h"
#include"card6.h"
#include"card7.h"
#include"card8.h"
#include"card9.h"
#include"card10.h"
#include"card11.h"
#include"card12.h"
#include"card13.h"
#include"card14.h"
#include"card15.h"



Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	turns=0;
	prevented=false;
	freeze=0;
	// Make all the needed initialization or validations
}
void Player::resetp()   // reset the player is a function for new gameaction to make the players data to the first values 
{
	 wallet=100;	      
	 justRolledDiceNum=0;
	 turnCount=0;    
	 turns=0;
	 prevented=0;
	 freeze=0;
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations // negative is valid according to the document so any value is accepted 
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];

	pOut->DrawPlayer(pCell->GetCellPosition(),playerNum,playerColor);
	///TODO: use the appropriate output function to draw the player with "playerColor"

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	
	pOut->DrawPlayer(pCell->GetCellPosition(),playerNum,cellColor);
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)

}
int Player::getjust() const 
{
	return justRolledDiceNum;
}
int Player::getpnum() const 
{
	return playerNum;
}
void Player::setturns(int x)
{
	if(x<0)
		turns=0;
	else
	turns=x;
}
int Player::getturns()
{
	return turns;
}

void Player::setprevented(bool x) //those two functions are used for freeze card(**) and prevent card
{
	prevented=x;
}
void Player::setfreeze(int x)// **
{
	if(x<0)
	freeze=0;
	else
	freeze=x;
}
int Player::getfreeze()
{
	return freeze;
}
bool Player::getprevented()
{
	return prevented;
}
// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	int x;int y;
	turnCount++;
	justRolledDiceNum=diceNumber;
	if(this->turnCount==3)    //  this if condition is made to ensure that if the turn count reached 3(2-->3)then set the wallet value and dont move 
	{
		this->SetWallet(this->GetWallet()+(10*diceNumber));
		turnCount=0;
	    return;
	}

	if(this->GetWallet()<=0||diceNumber==0)  // this if is for the corner case when the player have zero money ||OR|| his got his wallet to be zero(in the prevented card action) so that he might get his recharge 
	{
		if(this->turnCount==3)
		{
		this->SetWallet(this->GetWallet()+(10*diceNumber));
		turnCount=0;
		}
		   return;
	}
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	
	// 3- Set the justRolledDiceNum with the passed diceNumber

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	CellPosition pos=this->GetCell()->GetCellPosition();
	pos.AddCellNum(diceNumber);
	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(this,pos);
	if (pos.GetCellNum() >= 99)
	{
		pGrid->SetEndGame(true);
		pGrid->PrintErrorMessage("player number|| " + to_string(playerNum) + " ||congrats you are the first one to make it to the last cell Game Over");// when the player reaches the max cell num he/she is the winner I put at the end because there might be a ladder or any other game object that lead to the end cell after takink it(ex ladder at 11->99)

	}
	if(this->GetCell()->HasLadder()!=NULL)
	{
		this->GetCell()->HasLadder()->Apply(pGrid,this);
	}
	else if(this->GetCell()->HasSnake()!=NULL)
	{
		this->GetCell()->HasSnake()->Apply(pGrid,this);
	}
	else if(this->GetCell()->HasCoinSet()!=NULL)
	{
		this->GetCell()->HasCoinSet()->Apply(pGrid,this);
	}
	else if(this->GetCell()->HasCard()!=NULL)
	{
		if (this->GetCell()->HasCard()->GetCardNumber()==4||this->GetCell()->HasCard()->GetCardNumber()==12)
		{
			this->GetCell()->HasCard()->ReadCardParameters(pGrid);
		}
			this->GetCell()->HasCard()->Apply(pGrid,this);
	}
	
    
	pGrid->UpdateInterface();
	pGrid->GetOutput()->ClearStatusBar();
	// 6- Apply() the game object of the reached cell (if any)
	
	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)

}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}