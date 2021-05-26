#pragma once

#include"Grid.h"
#include "Action.h"

class SwitchToDesignMode : public Action
{
	string choice;
public:

	SwitchToDesignMode(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads SwitchToDesignMode action parameters 

	virtual void Execute(); // switches to design mode
	

	virtual ~SwitchToDesignMode(); // Virtual Destructor

};

