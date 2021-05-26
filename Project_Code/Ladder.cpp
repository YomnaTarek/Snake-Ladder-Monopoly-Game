#include "Ladder.h"
#include<fstream>
Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	if(startCellPos.HCell()!=endCellPos.HCell() || startCellPos.GetCellNum()>endCellPos.GetCellNum())
		return;
	else
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
	Type = 1;
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position,endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	if(endCellPos.IsValidCell()){
		pGrid->PrintErrorMessage("You have reached a ladder.click to continue");
      	pGrid->UpdatePlayerCell(pPlayer,endCellPos);
		if(pGrid->getobject(endCellPos))
		{
			pGrid->getobject(endCellPos)->Apply(pGrid,pPlayer);
		}
	    pGrid->UpdateInterface();}
	else
		return;

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

Ladder::~Ladder()
{
}

void Ladder::Save(ofstream& OutFile, Grid* pGrid, int typ)
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
		int start = GetPosition().GetCellNum();
		int end = GetEndPosition().GetCellNum();
		OutFile << start << "  " << end << endl;
	}
}
void Ladder::Load(ifstream& InFile, Grid* pGrid, int typ)
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
			int start;
			int end;
			InFile >> start >> end;
			CellPosition startpos(start);
			CellPosition endpos(end);
			Ladder*pLadder = new Ladder(startpos, endpos);
			pGrid->AddObjectToCell(pLadder);
		
	//	position = position.GetCellPositionFromNum(start);
	//	endCellPos = endCellPos.GetCellPositionFromNum(end);
		
	}
}