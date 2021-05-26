#include "snake.h"
#include<fstream>
Snake::Snake(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	if(startCellPos.HCell()!=endCellPos.HCell()|| startCellPos.GetCellNum()<endCellPos.GetCellNum())
	{
		return;
	}
	else
	this->endCellPos = endCellPos;
	Type = 2;
	///TODO: Do the needed validation
}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position,endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer) 
{
	if(endCellPos.IsValidCell()){
		pGrid->PrintErrorMessage("You have reached a Snake.click to continue...");
      	pGrid->UpdatePlayerCell(pPlayer,endCellPos);
		if(pGrid->getobject(endCellPos))
		{
			pGrid->getobject(endCellPos)->Apply(pGrid,pPlayer);
		}
	    pGrid->UpdateInterface();}
	else
		return;
}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

Snake::~Snake()
{
}
void Snake::Save(ofstream& OutFile, Grid* pGrid, int typ)
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
void Snake::Load(ifstream& InFile, Grid* pGrid, int typ)
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
		InFile >> start;
		InFile>>end;
		CellPosition startpos(start);
		CellPosition endpos(end);
		Snake* pSnake = new Snake(startpos, endpos);
		pGrid->AddObjectToCell(pSnake);

	}
}
