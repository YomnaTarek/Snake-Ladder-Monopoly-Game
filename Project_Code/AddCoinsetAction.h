#pragma once

#include "Action.h"

class AddCoinsetAction : public Action
{
	// [Action Parameters]
	CellPosition pos;          // 1- coin position
	int wallet; //2- wallet value

	// Note: These parameters should be read in ReadActionParameters()
	
public:
	AddCoinsetAction(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads AddCoinsetAction action parameters 
	
	virtual void Execute(); 
	
	virtual ~AddCoinsetAction(); // A Virtual Destructor
};

