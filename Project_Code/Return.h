#pragma once

#include "Action.h"

class Return : public Action
{
	
	int cardNumber; // card to return its mortgage

	
public:
	Return(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads Return mortgage action parameters (cardNumber)
	
	virtual void Execute(); 
	
	virtual ~Return(); // A Virtual Destructor
};

