#pragma once

#include "Action.h"

class Delete : public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
	
	CellPosition GameObjCell;

	// Note: These parameters should be read in ReadActionParameters()

public:

	Delete(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads Delete action parameters (GameObjCell)

	virtual void Execute(); // Deletes the Game Object 
							


	virtual ~Delete(); // Virtual Destructor

};