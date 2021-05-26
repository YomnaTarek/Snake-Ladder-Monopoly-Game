#pragma once

#include "Action.h"

class Offer : public Action
{
	int cardNumber;            // 1- the card he want to offer
	// Note: These parameters should be read in ReadActionParameters()
	
public:
	Offer(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads Offer mortgage action parameters (cardNumber)
	
	virtual void Execute(); 
	
	virtual ~Offer(); // A Virtual Destructor
};

