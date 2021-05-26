#include "card9.h"
#include<fstream>
card9::card9(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 9;// set the inherited cardNumber data member with the card number (9 here)
	taken =5;
	mor=5;
	offer=false;
	made = 0;
}

card9::~card9(void)
{
}

void card9::ReadCardParameters(Grid * pGrid)
{
	do{
	     pGrid->PrintErrorMessage("Aswan City selected: Enter its Price in POSITIVE integer,click ");
	     price= pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(price<0);

	do{
		 pGrid->PrintErrorMessage("Enter the POSITIVE fees of Aswan City ,click ");
	     fees= pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(fees<0);
}
void card9::reset()
{
	taken =5;
	mor=5;
	offer=false;
}
int card9::getmor()
{
return mor;
}
void card9::setmor(int x)
{
	mor=x;
}
int card9::getfee()
{
	return fees;
}
int card9::getprice()
{
	return price;
}
void card9::settaken(int x)
{
	taken=x;
}
int  card9::gettaken()
{
	return taken;
}
void card9::setprice(int x)
{
	price=x;
}
void card9::setfees(int x)
{
	fees=x;
}
void card9::setoffer(bool x)
{
	offer=x;
}
bool card9::getoffer()
{
	return offer;
}
void card9::Apply(Grid* pGrid, Player* pPlayer)
{ if(pGrid->isbenefit()!=NULL)
     {
		 Player* benefit=pGrid->isbenefit();
		 if(benefit->getpnum()!=pPlayer->getpnum())
		 {
			 pPlayer->SetWallet(pPlayer->GetWallet()-fees);
			pGrid->getplayer(benefit->getpnum())->SetWallet(pGrid->getplayer(benefit->getpnum())->GetWallet()+fees);
		 }
     }
  else
   {
	   if(taken==5 && pPlayer->GetWallet()>=price)
	{
		pGrid->PrintErrorMessage("Monopoly Card Aswan reached! Do you want to buy it?? click then enter  y/n");
		string choice = pGrid->GetInput()->GetSrting(pGrid->GetOutput());
		if(choice=="y")
		{
	pPlayer->SetWallet(pPlayer->GetWallet()-price);
	pGrid->setmonopoly(this->GetCardNumber(),pPlayer->getpnum());
		}
		else
			return;
	}
	else if(taken!=5 && mor==5)
	{
		if(pPlayer->getpnum()!=taken)
		{
			pPlayer->SetWallet(pPlayer->GetWallet()-fees);
			pGrid->getplayer(taken)->SetWallet(pGrid->getplayer(taken)->GetWallet()+fees);
		}
	}
	else if(taken!=5 && mor!=5&& mor!=taken)
	{
		if(pPlayer->getpnum()!=mor)
		{
			pPlayer->SetWallet(pPlayer->GetWallet()-fees);
			pGrid->getplayer(mor)->SetWallet(pGrid->getplayer(mor)->GetWallet()+fees);
		}
	}
	else if(taken!=5 && mor!=5&& mor==taken)
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

void card9::setmade(bool m)
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
bool card9::getmade()
{
	return made;
}
void card9::Save(ofstream& OutFile, Grid* pGrid, int typ)
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
void card9::Load(ifstream& InFile, Grid* pGrid, int typ)
{
	if (pGrid->getcity(9) == NULL)
	{
		InFile >> price >> fees;
		setprice(price);
		setfees(fees);

	}

	else
	{
		setprice(pGrid->getcity(9)->getprice());
		setfees(pGrid->getcity(9)->getfee());

	}
}

