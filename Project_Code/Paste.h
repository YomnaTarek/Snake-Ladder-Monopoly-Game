#pragma once

#include "Action.h"

class Paste : public Action
{
	//Add the add action parameters as private data members

   // [Action Parameters]:

	CellPosition CardOrCoinDestCell;// Destination cell of the card or coinset

public:

	Paste(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads PasteCardOrCoinsAction action parameters (Destination cell)

	virtual void Execute(); //Pastes all the card's or coinset's data to destination cell from clipboard


	virtual ~Paste(); // Virtual Destructor




};