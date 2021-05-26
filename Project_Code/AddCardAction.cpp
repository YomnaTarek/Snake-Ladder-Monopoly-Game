#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include "DecWalletCard_1.h"
#include"Nextcard.h"
#include"card3.h"
#include"card4.h"
#include"card5.h"
#include"card6.h"
#include"card7.h"
#include"card8.h"
#include"card9.h"
#include"card10.h"
#include"card11.h"
#include"card12.h"
#include"card13.h"
#include"card14.h"
#include"card15.h"

AddCardAction::AddCardAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() 
{	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	int x=0;int y=0;
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Output* pout=pManager->GetGrid()->GetOutput();
	Input* pin=pManager->GetGrid()->GetInput();
	do{
	     pout->PrintMessage("Enter the card number 1-15,click ");
	     pin->GetPointClicked(x,y);
	     cardNumber=pin->GetInteger(pout);
	}while(cardNumber<1||cardNumber>15);

	do{
	     pout->PrintMessage("Double click on the empty valid cell to put the card on");
	     pin->GetPointClicked(x,y);
	     cardPosition = pin->GetCellClicked();
	}while(cardPosition.IsValidCell()==false);
	// 2- Read the "cardNumber" parameter and set its data member
	
	// 3- Read the "cardPosition" parameter (its cell position) and set its data member

	// 4- Make the needed validations on the read parameters
	pout->ClearStatusBar();
	// 5- Clear status bar
}

void AddCardAction::Execute() 
{

	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card * pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	    case 1:
		pCard = new DecWalletCard_1(cardPosition);
		break;
		case 2:
		pCard = new Nextcard(cardPosition);
		break;
		case 3:
		pCard = new card3(cardPosition);
		break;
		case 4:
		pCard = new card4(cardPosition);
		break;
		case 5:
		pCard = new card5(cardPosition);
		break;
		case 6:
		pCard = new card6(cardPosition);
		break;
		case 7:
		pCard = new card7(cardPosition);
		break;
		case 8:
		pCard = new card8(cardPosition);
		break;
		case 9:
		pCard = new card9(cardPosition);
		break;
		case 10:
		pCard = new card10(cardPosition);
		break;
		case 11:
		pCard = new card11(cardPosition);
		break;
		case 12:
		pCard = new card12(cardPosition);
		break;
		case 13:
		pCard = new card13(cardPosition);
		break;
		case 14:
		pCard = new card14(cardPosition);
		break;
		case 15:
		pCard = new card15(cardPosition);
	    break;
	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// A- We get a pointer to the Grid from the ApplicationManager
		Grid* pgrid=pManager->GetGrid();
		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
		if(cardNumber!=4 && cardNumber!=12)
		{
			if(cardNumber>=7 && cardNumber<=11)
			{
				if(pgrid->check(cardNumber)!=NULL)
				{
					Card* temp=pgrid->check(cardNumber);
					pCard->setprice(temp->getprice());
					pCard->setfees(temp->getfee());
				}
				else
					pCard->ReadCardParameters(pgrid);
			}
			else
				pCard->ReadCardParameters(pgrid);
		}

		if(pgrid->AddObjectToCell(pCard)==false)
			pgrid->PrintErrorMessage("INVALID position,click to continue....");
		// C- Add the card object to the GameObject of its Cell:

		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		
	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}
