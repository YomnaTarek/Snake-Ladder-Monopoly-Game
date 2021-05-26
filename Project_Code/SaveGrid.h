#pragma once

#include"Grid.h"
#include "Action.h"

class SaveGrid : public Action
{
	string Filename;
public:

	SaveGrid(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads SaveGridAction action parameters (Filename)

	virtual void Execute(); // Saves the grid



	virtual ~SaveGrid(); // Virtual Destructor

};

