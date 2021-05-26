#include "card7.h"
#include<fstream>
card7::card7(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber =7;// set the inherited cardNumber data member with the card number (7 here)
	taken =5;   
	mor=5;
	price=0;
	fees=0;
	offer=false;
	made = 0;
	
}

card7::~card7(void)
{
}

void card7::ReadCardParameters(Grid * pGrid)
{
	do{
	     pGrid->PrintErrorMessage("Cairo city selected: Enter its Price in POSITIVE integer,click ");
	     price= pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(price<0);

	do{
		 pGrid->PrintErrorMessage("Enter the POSITIVE fees of Cairo City ,click ");
	     fees= pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(fees<0);
}
void card7::reset()
{
	taken =5;
	mor=5;
	offer=false;
}
void card7::settaken(int x)
{
	taken=x;
}
int  card7::gettaken()
{
	return taken;
}
int card7::getfee()
{
	return fees;
}
int card7::getprice()
{
	return price;
}
int card7::getmor()
{
return mor;
}
void card7::setmor(int x)
{
	mor=x;
}
void card7::setprice(int x)
{
	price=x;
}
void card7::setfees(int x)
{
	fees=x;
}
void card7::setoffer(bool x)
{
	offer=x;
}
bool card7::getoffer()
{
	return offer;
}
void card7::Apply(Grid* pGrid, Player* pPlayer) // apply is pretty much the  same so comments are only written in card 7
{ 
	if(pGrid->isbenefit()!=NULL)                      // first condition to check is that if there is any benefit player, is benefit checks if there is any player that has his benefit switch on
     {
		 Player* benefit=pGrid->isbenefit();      //is benefit grid function returns the first player to have his benefit in a firt come first serve way;
		 if(benefit->getpnum()!=pPlayer->getpnum())   // a routine check that checks if the current player on the city is the one with the benefit switch on or not 
		 {
			 pPlayer->SetWallet(pPlayer->GetWallet()-fees);  // decremets the fees from the wallet of the current palyer
			pGrid->getplayer(benefit->getpnum())->SetWallet(pGrid->getplayer(benefit->getpnum())->GetWallet()+fees);  //incremets those fees in the wallet of the benefit player 
		 }
     }
  else  // now this are the possible 4 conditions 
   {
	   if(taken==5&& pPlayer->GetWallet()>=price)    //1. the city is not bought and the player on it have its price then ask him if he wants to buy it 
	{
		pGrid->PrintErrorMessage("Monopoly Card Cairo reached! Do you want to buy it?? click then enter y/n");
		string choice = pGrid->GetInput()->GetSrting(pGrid->GetOutput());
		if(choice=="y")
		{
	pPlayer->SetWallet(pPlayer->GetWallet()-price);
	pGrid->setmonopoly(this->GetCardNumber(),pPlayer->getpnum());   //setmonopoly is a grid function that loops over the all cells if there is a monooboli card makes its taken to be that player number
		}
		else
			return;
	}
	else if(taken!=5 && mor==5)  //case 2: the city is taken but not mortged to any body so money goes to taken if he is not the player on card 
	{
		if(pPlayer->getpnum()!=taken)
		{
			pPlayer->SetWallet(pPlayer->GetWallet()-fees);
			pGrid->getplayer(taken)->SetWallet(pGrid->getplayer(taken)->GetWallet()+fees);
		}
	}
	else if(taken!=5 && mor!=5&& mor!=taken)  //case 3: the city is taken and mortaged so money of fees go to mortaged player
	{
		if(pPlayer->getpnum()!=mor)
		{
			pPlayer->SetWallet(pPlayer->GetWallet()-fees);
			pGrid->getplayer(mor)->SetWallet(pGrid->getplayer(mor)->GetWallet()+fees);
		}
	}
	else if(taken!=5 && mor!=5&& mor==taken)  //case 4 happens due to the lose mortage card where the taken is the same as the mortgegd so treated like case 2 and set mortgage to its deafult value
	{
		mor=5;
		if(pPlayer->getpnum()!=taken)
		{
			pPlayer->SetWallet(pPlayer->GetWallet()-fees);
			pGrid->getplayer(taken)->SetWallet(pGrid->getplayer(taken)->GetWallet()+fees);
		}
	}
   }
     pGrid->UpdateInterface();
}


void card7::setmade(bool m)
{
	if (m == 0 || m == 1)
	{
		made = m;
	}
	else
	{
		return;
	}
}
bool card7::getmade()
{
	return made;
}

void card7::Save(ofstream& OutFile, Grid* pGrid, int typ)
{
	Card::Save(OutFile, pGrid, typ);

	Card* pCard = pGrid->CheckCardNumber(cardNumber);

	if ((pCard->GetCardNumber() >= 7 && pCard->GetCardNumber() <= 11))
	{
		if (getmade() == 0)
		{
			OutFile << getprice() << " " << getfee() << endl;
			pGrid->SetSave(GetCardNumber());
		}
		else
		{
			OutFile << endl;
			return;
		}
	}

}
void card7::Load(ifstream& InFile, Grid* pGrid, int typ)
{
	if (pGrid->getcity(7) == NULL)
	{
		InFile >> price >> fees;
		setprice(price);
		setfees(fees);

	}

	else
	{
		setprice(pGrid->getcity(7)->getprice());
		setfees(pGrid->getcity(7)->getfee());

	}
}


