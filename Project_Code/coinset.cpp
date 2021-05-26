#include "coinset.h"
#include "Player.h"
#include<fstream>
CoinSet::CoinSet(const CellPosition & CellPos, int coins ) : GameObject(CellPos)
{
	if(CellPos.IsValidCell()==true)
	{
		if(coins>0)
			coinamount=coins;
		else
			coinamount=0;
	}
	else
	{
		coinamount = 0;
	}
	Type = 3;

}
void CoinSet::setcoins(int amnt)
{
	if (amnt < 0)
	{
		amnt = 0;
		coinamount = amnt;
	}
	else
	{
		coinamount = amnt;
	}// needs validation
}

void CoinSet::Draw(Output* pOut) const
{
	pOut->DrawCoinSet(position);
}

void CoinSet::Apply(Grid* pGrid, Player* pPlayer) 
{
	if(position.IsValidCell()==true)
	{
	    pGrid->PrintErrorMessage("Congrats! You have reached a coinset of value "+ to_string(coinamount)+" .Click to take it...");
		pPlayer->SetWallet(pPlayer->GetWallet()+coinamount);
	    pGrid->UpdateInterface();
	}
	else
		return;
}

CellPosition CoinSet::GetPosition() const
{
	return position;
}
int CoinSet::getcoins() const
{
	return coinamount;
}

CoinSet::~CoinSet()
{
}

void CoinSet::Save(ofstream& OutFile, Grid* pGrid, int typ)
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
		int CoinSetCellNum = GetPosition().GetCellNum();

		OutFile << CoinSetCellNum << "  " << getcoins() << endl;

	}

}
void CoinSet::Load(ifstream& InFile, Grid* pGrid, int typ)
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
		int pos;
		int coin;
		InFile >> pos;
		InFile>> coin;
		CellPosition startpos(pos);
		CoinSet*pcoin = new CoinSet(startpos, coin);
		pGrid->AddObjectToCell(pcoin);


	}
}