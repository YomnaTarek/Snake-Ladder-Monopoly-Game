#pragma once

#include "Action.h"

class DiceValue : public Action
{

	// No parameters for this action

public:
	DiceValue(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~DiceValue();
};

