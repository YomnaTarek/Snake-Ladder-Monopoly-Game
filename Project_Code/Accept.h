#pragma once

#include "Action.h"

class Accept : public Action
{
	int cardNumber;            // 1- the card he want to offer
	// Note: These parameters should be read in ReadActionParameters()
	
public:
	Accept(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads Accept mortgage action parameters (cardNumber)
	
	virtual void Execute();

	virtual ~Accept(); // A Virtual Destructor
};

