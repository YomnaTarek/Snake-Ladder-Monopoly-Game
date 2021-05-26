#include "Card.h"
#include<fstream>
#include "DecWalletCard_1.h"
#include"Nextcard.h"
#include"card3.h"
#include"card4.h"
#include"card5.h"
#include"card6.h"
#include"card7.h"
#include"card8.h"
#include"card9.h"
#include"card10.h"
#include "card11.h"
#include"card12.h"
#include "card13.h"
#include "card14.h"
#include "card15.h"
Card::Card(const CellPosition & pos) : GameObject(pos) // sets the cell position of the GameObject
{
	Type = 4;
}

void Card::SetCardNumber(int cnum)
{
	if(cnum<1 || cnum>15)
		return;
	else
	cardNumber = cnum; // needs validation
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{
	
    pOut->DrawCell(position,cardNumber);
	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"


}

void Card::ReadCardParameters(Grid * pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer) 
{
	
	// The following line is to print the following message if a player reaches a card of any type

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
	int x=0; int y=0;
	pGrid->GetInput()->GetPointClicked(x,y);
}
void Card::settaken(int x)
{
}
int Card::gettaken()
{
	return 5;
}
void Card::setmor(int x)
{
}
int Card::getmor()
{
	return 5;
}
int Card::getfee()
{
	return 0;
}
int Card::getprice()
{
	return 0;
}
void Card::setprice(int x)
{
}
void Card::setfees(int x)
{
}
void Card::setoffer(bool x)
{
	
}
bool Card::getoffer()
{
	return false;
}
void Card::reset()
{

}
void Card::setmade(bool x)
{

}
void Card::setload(bool x)
{

}
Card::~Card()
{
}

void Card::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	if (typ != Type)
	{
		return;
	}
	if (!OutFile.is_open())
	{
		return;
	}
	else
	{

		OutFile << GetCardNumber()  << "  " << GetPosition().GetCellNum() << " ";
	}
}
void Card::Load(ifstream& InFile,Grid* pGrid, int typ)
{
	if (typ != Type)
	{
		return;
	}
	if (!InFile.is_open())
	{
		return;
	}
	else
	{
		CellPosition pos;
		
			int CellNum;
			int cardNum;
			InFile >> cardNum;
			InFile >> CellNum;
			Card* pCard = NULL;
			switch (cardNum)
			{
			case 1:
				pos = pos.GetCellPositionFromNum(CellNum);
				pCard = new DecWalletCard_1(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 2:
				pos = pos.GetCellPositionFromNum(CellNum);
				pCard = new Nextcard(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 3:
					pos = pos.GetCellPositionFromNum(CellNum);
					pCard = new card3(pos);
					pCard->Load(InFile, pGrid, 4);
					break;
			case 4:
			pos = pos.GetCellPositionFromNum(CellNum);	
			pCard = new card4(pos);
			pCard->Load(InFile, pGrid, 4);
			break;
			case 5:
				pos = pos.GetCellPositionFromNum(CellNum);
				pCard = new card5(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 6:
				pos = pos.GetCellPositionFromNum(CellNum);
				pCard = new card6(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 7:
				pos = pos.GetCellPositionFromNum(CellNum);
				pCard = new card7(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 8:
				pos = pos.GetCellPositionFromNum(CellNum);
				SetCardNumber(cardNum);
				SetPosition(pos);
				pCard = new card8(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 9:
				pos = pos.GetCellPositionFromNum(CellNum);
				SetCardNumber(cardNum);
				SetPosition(pos);
				pCard = new card9(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 10:
				pos = pos.GetCellPositionFromNum(CellNum);
				SetCardNumber(cardNum);
				SetPosition(pos);
				pCard = new card10(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 11:
				pos = pos.GetCellPositionFromNum(CellNum);
				SetCardNumber(cardNum);
				SetPosition(pos);
				pCard = new card11(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 12:
				pos = pos.GetCellPositionFromNum(CellNum);
				pCard = new card12(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 13:
				pos = pos.GetCellPositionFromNum(CellNum);
				pCard = new card13(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 14:
				pos = pos.GetCellPositionFromNum(CellNum);
				pCard = new card14(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			case 15:
				pos = pos.GetCellPositionFromNum(CellNum);
				pCard = new card15(pos);
				pCard->Load(InFile, pGrid, 4);
				break;
			}
			if (pCard)
			{
				pGrid->AddObjectToCell(pCard);
			}


		}

		
		
	}
