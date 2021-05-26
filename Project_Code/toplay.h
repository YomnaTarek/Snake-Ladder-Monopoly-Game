#pragma once

#include "Action.h"

class toplay : public Action
{
	
public:
	toplay(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); 

	virtual ~toplay(); // A Virtual Destructor
};

