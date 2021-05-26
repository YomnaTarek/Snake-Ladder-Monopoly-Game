#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.

enum ActionType // The actions supported (add more as needed)
{
	//  [1] Actions of Design Mode

	ADD_LADDER,		// Add Ladder Action
	ADD_SNAKE,		// Add Snake Action	
	ADD_CARD,		// Add Card Action	
	ADD_COINSET,//3
	COPY,//4
	CUT,//5
	PASTE,//6
    DELETES, //7
	SAVEGRID,//8
	OPENGRID, //9
	EXIT,			// Exit Application
	TO_PLAY_MODE,	// Go to Play Mode

	///TODO: Add more action types of Design Mode

	//  [2] Actions of Play Mode

	ROLL_DICE,	// Roll Dice ActionITM_DICE_VALUE,
	Dice_value,
	OMOR,   //offer mortgage
	AMOR,     //Accept mortgage
	RMOR,      //return motgage
	SELL,
	NEWGAME,
	TO_DESIGN_MODE,	// Go to Design Mode
	EXITT,
	///TODO: Add more action types of Play Mode

	//  [3] Others

	EMPTY,				// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,			// Inside Grid Area
	STATUS 				// Inside StatusBar Area
};

#endif