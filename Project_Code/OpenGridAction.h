#pragma once


#include"Grid.h"
#include "Action.h"

class OpenGridAction : public Action
{
	string Filename;
public:

	OpenGridAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads OpenGridAction action parameters (Filename)

	virtual void Execute(); // Loads the grid



	virtual ~OpenGridAction(); // Virtual Destructor

};



