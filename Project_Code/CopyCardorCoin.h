#pragma once
#include "Action.h"

class CopyCardorCoin : public Action
{
	//Add the add action parameters as private data members

   // [Action Parameters]:

	CellPosition CardOrCoinCell;// source cell of the card or coinset

public:

	CopyCardorCoin(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads CopyCardOrCoinsAction action parameters (source cell)

	virtual void Execute(); // Copy all the card's or coinset's data to clipboard
							

	virtual ~CopyCardorCoin(); // Virtual Destructor




};