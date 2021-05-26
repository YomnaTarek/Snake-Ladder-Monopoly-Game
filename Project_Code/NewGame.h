#pragma once

#include "Action.h"

class NewGame: public Action
{	
public:
	NewGame(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); 
	
	virtual void Execute(); 
	
	virtual ~NewGame(); // A Virtual Destructor
};

