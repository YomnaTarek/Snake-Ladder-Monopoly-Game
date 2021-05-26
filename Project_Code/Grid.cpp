#include "Grid.h"
#include"CellPosition.h"
#include"Cell.h"
#include"GameObject.h"
#include"Ladder.h"
#include"Card.h"
#include"Player.h"
#include"snake.h"
#include"coinset.h"




Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
	cutorcopy=2;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed (no i will not need it here )
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
		pOut->DrawCell(pos,-1);
	}
}

void Grid::RemoveGrid() // this function makes all the cleanups needed
{
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			if (CellList[i][j]->GetGameObject() != NULL)
			{
				delete CellList[i][j]->GetGameObject();
				CellList[i][j]->SetGameObject(NULL);
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		delete PlayerList[i];
		PlayerList[i] = NULL;
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}


GameObject * Grid::GetClipboard() const // to be used in paste to get wheter a paste from a copy or cut
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{ 
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
   
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

GameObject* Grid::GetNextGame(const CellPosition &position ,int object) // instead of next ladder thiis fun. gets the next of any GO giving the second parameter (1-4)
{
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			
			if(CellList[i][j]->HasLadder() && object==1)
				return CellList[i][j]->HasLadder();
			else if(CellList[i][j]->HasSnake() && object==2)
				return CellList[i][j]->HasSnake();
			else if(CellList[i][j]->HasCoinSet() && object==3)
				return CellList[i][j]->HasCoinSet();
			else if(CellList[i][j]->HasCard() && object==4)
			return CellList[i][j]->HasCard();
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Player* Grid::getplayer(int c)   //give it player numbe rreturns his player * same as getcurrent but more general
{
	for(int i=0;i<4;i++)
	{
		if(i==c)
			return PlayerList[i]; // this does not violate Grid Responsibilites as it is the same as get current but gets another player (giving that the PlayerList is an array so returning the current could make all the list avalible )
	}
	return NULL;
}
Player* Grid::isbenefit()  // loops over the player that is has the benefit switch on and returns the first one in a first come first serve model
{
	for(int i=0;i<4;i++)
	{
		if(PlayerList[i]->getturns()!=0)  // if two players got the card the player with lower Pnumber takes it first 
			return PlayerList[i];
	}
	return NULL;
}
int Grid::getplayeri(const int &cellnum)   //send to it a cell number and returns the palyer number in it (used in prevent )
{
	for(int i=0;i<4;i++)
	{
		int x=(PlayerList[i]->GetCell()->GetCellPosition()).GetCellNum();
		if(x==cellnum)
			return  i; // gets the player number in the cell clicked on 
	}
	return 4;
}
void Grid::setmonopoly(int x,int y) //x is the city number (7-11) and y is the player that city should belong to him 
{
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL)
		  {
			if(x==CellList[i][j]->HasCard()->GetCardNumber())
			{
				CellList[i][j]->HasCard()->settaken(y);  // taken is the monoply card data member that indicates who ownes the city 
			}
		  }
		}
    }
}
void Grid::setmorta(int x,int y) // x is the city number and y is the player that the city should be mortaged to 
{
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL)
		  {
			if(x==CellList[i][j]->HasCard()->GetCardNumber())
			{
				CellList[i][j]->HasCard()->setmor(y);  //mor is the data memebr in MC that indicates the 
			}
		  }
		}
    }
}
bool Grid::checkmortgage(int card,int p)//p the player and card is the card number, this fun. is used in accept.cpp to check that the city is not mortgaged to any one and that it exits 
{
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL)
		  {
			  if(card==CellList[i][j]->HasCard()->GetCardNumber() && CellList[i][j]->HasCard()->getmor()!=5 && CellList[i][j]->HasCard()->gettaken()==p)
			    return true;
		  }
		}
    }
	return false; // means that the city is either not on the grid or is not mortgaged or the player calling the function iis not its owner
}
int Grid::getmaxcity(int y,int & h)  //used in card returnmaxcity //y is the player that i want to check that a certain city is his and h is set in the card to be 5 an sent by refrence to change if this city is mortgaged 
{
	int max=0; int x; int z=20;
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL)
		  {
			  x=CellList[i][j]->HasCard()->GetCardNumber();
			 if(x==7||x==8||x==9||x==10||x==11)
			{
			   if(CellList[i][j]->HasCard()->gettaken()==y)
			   {
				   if(CellList[i][j]->HasCard()->getprice()>max)
				   {
                       max=CellList[i][j]->HasCard()->getprice();
					   z=CellList[i][j]->HasCard()->GetCardNumber();
					   if(CellList[i][j]->HasCard()->getmor()!=5)
						   h=CellList[i][j]->HasCard()->getmor();
					   else 
						   h=5;
				   }
			   }

			}
		  }
		}
    }
	return z;
}
int Grid::morta(int y)  //gets the min of mortgaged cities returns card number
{
	int min=10000; int x; int z=20;
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL)
		  {
			  x=CellList[i][j]->HasCard()->GetCardNumber();
			 if(x==7||x==8||x==9||x==10||x==11)
			{
			   if(CellList[i][j]->HasCard()->gettaken()==y)
			   {
				   if(CellList[i][j]->HasCard()->getprice()<min && CellList[i][j]->HasCard()->getmor()!=5)
				   {
                       min=CellList[i][j]->HasCard()->getprice();
					   z=CellList[i][j]->HasCard()->GetCardNumber();
				   }
			   }

			}
		  }
		}
    }
	return z;
}
bool Grid::fire(int player,int v,int h)  //fire takes a player number and v(vcell),h(hcell) check if this player is tn either the coulmn or row of this a certain cell(return true of yes)
{
	Player* temp=getplayer(player);
	if((temp->GetCell()->GetCellPosition()).HCell()==h||(temp->GetCell()->GetCellPosition()).VCell()==v)
		return true;
	else
		return false;
}
bool Grid::evenorodd(int x,int y)   //takes x(player number(0-3)) and check if he is in y(even or odd ) and return true accordingly
{
	if((PlayerList[x]->GetCell()->GetCellPosition().GetCellNum())%2==y)
		return true;
	else
		return false;
}
GameObject * Grid::getobject(const CellPosition & pos) //gets the gameobject in this cellposition
{
	int v= pos.VCell();
	int h =pos.HCell();
	if(CellList[v][h]->GetGameObject())
		return CellList[v][h]->GetGameObject();
	else
		return NULL;
}
Card* Grid::check(int card)//used in AddCard when a city is added for the second+ time  // loops over the cel list and checks that the city fees and price given are not set used for addcard action
{
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL )
		  {
			  Card* temp= CellList[i][j]->HasCard();
			if(card==temp->GetCardNumber())
			{
				if(temp->getprice()!=0)
					return temp;
			}
		  }
		}
    }
	return NULL;
}

GameObject* Grid::GetCardOrCoins(const CellPosition & position) // used for copy and paste to get the coin or card in thhid cell
{
	int v = position.VCell();
	int h = position.HCell();
     if(CellList[v][h]->HasCard()!=NULL)
	{
		 return CellList[v][h]->HasCard();
	}
	else if (CellList[v][h]->HasCoinSet() != NULL)
	{
		 return CellList[v][h]->HasCoinSet();
	}
	else
	{
		 return NULL;
	}
}
void Grid::SetClipboard(GameObject* GameObj,int copyORcut) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	int h = GameObj->GetPosition().HCell();
	int v = GameObj->GetPosition().VCell();
	cutorcopy=copyORcut;
	if (CellList[v][h]->HasCard() != NULL)
	{
		Clipboard = GameObj;

	}
	else if (CellList[v][h]->HasCoinSet() != NULL)
	{
		Clipboard = GameObj;
	}

}
int Grid::getcopyorcut()
{
	return cutorcopy;
}
bool Grid::Paste(GameObject* pNewObject, CellPosition position) // add the pasteed object to its cell
{
	int h = position.HCell();
	int v = position.VCell();
	
	// Get the cell position of pNewObject
	CellPosition pos = position;
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		GameObject* temp=CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if(dynamic_cast<CoinSet*>(temp))
		{
			pOut->DrawCoinSet( position);
			return true;
		}
		else if(dynamic_cast<Card*>(temp))
		{
			Card* tem=dynamic_cast<Card*>(temp);
			pOut->DrawCell(position,tem->GetCardNumber());
			return true;
		}
		 // indicating that addition is done
	}
	return false; // if not a valid position
}
void Grid::offer(int x,int p) // offer is used in Offer action to set the offer data memebr of the cities to true,x is the city numbe rand p is the owner player to check that the player offering is the owner
{
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL )
		  {
			  Card* temp= CellList[i][j]->HasCard();
			if(x==temp->GetCardNumber())
			{
				if(temp->gettaken()==p && temp->getmor()==5 &&temp->getoffer()==false)
				{
					temp->setoffer(true);
				}
			}
		  }
		}
    }
}
bool Grid::checkoffer(int x,int p)// checks that the offer process is done (cannot be done in the upper function as return value will only set one city not all of them
{
   for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL )
		  {
			  Card* temp= CellList[i][j]->HasCard();
			if(x==temp->GetCardNumber())
			{
				if(temp->gettaken()==p)
				{
				if(temp->getoffer())
					return true;
				}
			}
		  }
		}
    }
   return false;
}
bool Grid::checkaccept(int x,int p)// checks if the player passed is not the owener and that th e card is already there 
{
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL )
		  {
			  Card* temp= CellList[i][j]->HasCard();
			if(x==temp->GetCardNumber())
			{
				if(temp->gettaken()!=p)
				{
				if(temp->getoffer()==true)
					return true;
				}
			}
		  }
		}
    }
   return false;
}
void Grid::accept(int x,int p)
{
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL )
		  {
			  Card* temp= CellList[i][j]->HasCard();
			if(x==temp->GetCardNumber())
			{
				if(temp->gettaken()!=p)
				{
				if(temp->getoffer()==true)
				{
					temp->setmor(p);
					temp->setoffer(false);
				}

				}
			}
		  }
		}
    }
}
Card * Grid::getcity(int x)// gets the first city with the passed number (used to get the fees and price and other data memebrs in other classes)
{
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL )
		  {
			 if(CellList[i][j]->HasCard()->GetCardNumber()==x)
				 return CellList[i][j]->HasCard();
		  }
        }
    }
	return NULL;
}
void Grid::New()// calls the reset functions in all the classes used in New game action 
{
	for (int i = 8; i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = 0; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
		  if(CellList[i][j]->HasCard()!=NULL )
		  {
			  CellList[i][j]->HasCard()->reset();
		  }
        }
    }
	for(int i=0;i<4;i++)
	{
		CellPosition tem(1);
		UpdatePlayerCell(PlayerList[i],tem);
		PlayerList[i]->resetp();
	}
	currPlayerNumber=0;
	UpdateInterface();
}
int Grid::HowManyGameObj(int Type)// used in loading
{
	int count = 0;
	CellPosition position = position.GetCellPositionFromNum(1);
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	if (Type == 1)
	{
		for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
		{
			for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
			{
				if (CellList[i][j]->HasLadder() != NULL)
				{
					count++;
				}
			}
			startH = 0;
		}
		return count;
	}
	else if (Type == 2)
	{
		for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
		{
			for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
			{
				if (CellList[i][j]->HasSnake() != NULL)
				{
					count++;
				}
			}
			startH = 0;
		}
		return count;
	}
	else if (Type == 3)
	{
		for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
		{
			for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
			{
				if (CellList[i][j]->HasCoinSet() != NULL)
				{
					count++;
				}
			}
			startH = 0;
		}
		return count;
	}
	else if (Type == 4)
	{
		for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
		{
			for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
			{
				if (CellList[i][j]->HasCard() != NULL)
				{
					count++;
				}
			}
			startH = 0;
		}
		return count;
	}
	
		return count;
}
void Grid::SaveAll(ofstream& OutFile,Grid*pGrid, int Type)
{
	CellPosition position = position.GetCellPositionFromNum(1);
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	if (Type == 1)
	{
		for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
		{
			for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
			{
				if (CellList[i][j]->HasLadder() != NULL)
				{
					CellList[i][j]->HasLadder()->Save(OutFile, pGrid,Type);
				}
			}
			startH = 0;
		}
	}
	else if (Type == 2)
	{
		for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
		{
			for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
			{
				if (CellList[i][j]->HasSnake() != NULL)
				{
					CellList[i][j]->HasSnake()->Save(OutFile, pGrid, Type);
				}
			}
			startH = 0;
		}
	}
	else if (Type == 3)
	{
		for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
		{
			for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
			{
				if (CellList[i][j]->HasCoinSet() != NULL)
				{
					CellList[i][j]->HasCoinSet()->Save(OutFile, pGrid, Type);
				}
			}
			startH = 0;
		}
	}
	else if (Type == 4)
	{
		for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
		{
			for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
			{
				if (CellList[i][j]->HasCard() != NULL)
				{
					CellList[i][j]->HasCard()->Save(OutFile, pGrid, Type);
				}
			}
			startH = 0;
		}
	}
}

Card* Grid::CheckCardNumber(int CardNum)
{
	CellPosition position = position.GetCellPositionFromNum(1);
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			///TODO: Check if CellList[i][j] has a card,if yes return it,if not return NULL 
			if (CellList[i][j]->HasCard() != NULL)
			{
				return CellList[i][j]->HasCard();
			}
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}

	return NULL; // not found
}
void Grid::SetSave(int cardnum)
{
	CellPosition position = position.GetCellPositionFromNum(1);
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			///TODO: Check if CellList[i][j] has a card,if yes return it,if not return NULL 
			if (CellList[i][j]->HasCard() != NULL)
			{
				if (CellList[i][j]->HasCard()->GetCardNumber() == cardnum)
				{
					CellList[i][j]->HasCard()->setmade(1);
				}
			}
		}

	}

}

int Grid::GetPlayerMax(int walletmax) //gets the player with max wallet used for switch to design
{
	for (int i = 0;i < 4;i++)
	{
		if (getplayer(i)->GetWallet()== walletmax)
		{
			return i;
		}
	}
}

void Grid::RemoveAllObjects()
{

	CellPosition position = position.GetCellPositionFromNum(1);
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			if (CellList[i][j]->GetGameObject() != NULL)
				RemoveObjectFromCell(CellList[i][j]->GetGameObject()->GetPosition());
			
		}
		startH = 0;
	}
	
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);

			}
		}
		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		///TODO: Add the code that draws the CoinSet game objects

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}