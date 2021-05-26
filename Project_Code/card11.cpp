#include "card11.h"
#include<fstream>
card11::card11(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 11;// set the inherited cardNumber data member with the card number (11 here)
	taken =5;
	mor=5;
	offer=false;
	made = 0;
}

card11::~card11(void)
{
}

void card11::ReadCardParameters(Grid * pGrid)
{
	do{
	     pGrid->PrintErrorMessage("Hurghada City selected: Enter its Price in POSITIVE integer,click ");
	     price= pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(price<0);

	do{
		 pGrid->PrintErrorMessage("Enter the POSITIVE fees of Hurghada City ,click ");
	     fees= pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(fees<0);
}
void card11::reset()
{
	taken =5;
	mor=5;
	offer=false;
}
int card11::getmor()
{
return mor;
}
void card11::setmor(int x)
{
	mor=x;
}
int card11::getfee()
{
	return fees;
}
int card11::getprice()
{
	return price;
}
void card11::settaken(int x)
{
	taken=x;
}
int  card11::gettaken()
{
	return taken;
}
void card11::setprice(int x)
{
	price=x;
}
void card11::setfees(int x)
{
	fees=x;
}
void card11::setoffer(bool x)
{
	offer=x;
}
bool card11::getoffer()
{
	return offer;
}
void card11::Apply(Grid* pGrid, Player* pPlayer)
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
	pGrid->GetOutput()->PrintMessage("Monopoly Card Hurghada City reached! Do you want to buy it?? click then y/n");
		string choice = pGrid->GetInput()->GetSrting(pGrid->GetOutput());
		if(choice=="y")
		{
	pPlayer->SetWallet(pPlayer->GetWallet()-price);
	pGrid->setmonopoly(this->GetCardNumber(),pPlayer->getpnum());
		}
		else
			return ;
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
	 pGrid->GetOutput()->ClearStatusBar();
}

void card11::setmade(bool m)
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
bool card11::getmade()
{
	return made;
}
void card11::Save(ofstream& OutFile, Grid* pGrid, int typ)
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
void card11::Load(ifstream& InFile, Grid* pGrid, int typ)
{
	if (pGrid->getcity(11) == NULL)
	{
		InFile >> price >> fees;
		setprice(price);
		setfees(fees);

	}

	else
	{
		setprice(pGrid->getcity(11)->getprice());
		setfees(pGrid->getcity(11)->getfee());

	}
}

