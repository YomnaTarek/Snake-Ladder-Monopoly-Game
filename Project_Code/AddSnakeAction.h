#pragma once

#include "Action.h"

class AddSnakeAction : public Action
{
	// [Action Parameters]
	CellPosition from;          // 1- the card number
	CellPosition to; // 2- cell position of the card

	// Note: These parameters should be read in ReadActionParameters()
	
public:
	AddSnakeAction(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads AddSnakeAction action parameters (startPos, endPos)
	
	virtual void Execute(); // Creates a new snake Object 
	                        // then Sets this snake object to the GameObject Pointer of its Cell
	
	virtual ~AddSnakeAction(); // A Virtual Destructor
};

