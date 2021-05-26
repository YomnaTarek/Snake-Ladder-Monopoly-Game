#pragma once

#include "Action.h"

class Sell: public Action
{
	
	int cardNumber; // card to return its mortgage

	
public:
	Sell(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads Sell city action parameters (cardNumber)
	
	virtual void Execute(); 
	
	virtual ~Sell(); // A Virtual Destructor
};

