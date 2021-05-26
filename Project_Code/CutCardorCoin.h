#pragma once

#include "Action.h"

class CutCardorCoin : public Action
{
	//Add the add action parameters as private data members

   // [Action Parameters]:

	CellPosition CardOrCoinCell;// source cell of the card or coinset

public:

	CutCardorCoin(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads CutCardOrCoinsAction action parameters (source cell)

	virtual void Execute(); // Copy all the card's or coinset's data to clipboard


	virtual ~CutCardorCoin(); // Virtual Destructor




};