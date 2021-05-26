#include "card10.h"
#include<fstream>
card10::card10(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 10;// set the inherited cardNumber data member with the card number (10 here)
	taken =5;
	mor=5;
	offer=false;
	made = 0;
}

card10::~card10(void)
{
}

void card10::ReadCardParameters(Grid * pGrid)
{
	do{
	     pGrid->PrintErrorMessage("Luxor City selected: Enter its Price in POSITIVE integer,click ");
	     price= pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(price<0);

	do{
		 pGrid->PrintErrorMessage("Enter the POSITIVE fees of Luxor City ,click ");
	     fees= pGrid->GetInput()->GetInteger(pGrid->GetOutput());
	}while(fees<0);
}
void card10::reset()
{
	taken =5;
	mor=5;
	offer=false;
}
int card10::getmor()
{
return mor;
}
void card10::setmor(int x)
{
	mor=x;
}
int card10::getfee()
{
	return fees;
}
int card10::getprice()
{
	return price;
}
void card10::settaken(int x)
{
	taken=x;
}
int  card10::gettaken()
{
	return taken;
}
void card10::setprice(int x)
{
	price=x;
}
void card10::setfees(int x)
{
	fees=x;
}
void card10::setoffer(bool x)
{
	offer=x;
}
bool card10::getoffer()
{
	return offer;
}
void card10::Apply(Grid* pGrid, Player* pPlayer)
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
		pGrid->PrintErrorMessage("Monopoly Card Luxor reached! Do you want to buy it?? click then enter y/n");
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
void card10:: setmade(bool m)
{
	if(m==0 || m==1 )
	{
		made=m;
	}
	else
	{
		return;
	}
}
bool card10::getmade()
{
	return made;
}
void card10::Save(ofstream& OutFile,Grid*pGrid, int typ)
{
	Card::Save(OutFile,pGrid, typ);
	
	Card* pCard = pGrid->CheckCardNumber(cardNumber);
	
	if ((pCard->GetCardNumber() >= 7 && pCard->GetCardNumber() <= 11))
	{
		if(getmade()==0)
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
void card10::Load(ifstream& InFile, Grid* pGrid, int typ)
{
	if (pGrid->getcity(10) == NULL)
	{
		InFile >> price >> fees;
		setprice(price);
		setfees(fees);

	}

	else
	{
		setprice(pGrid->getcity(10)->getprice());
		setfees(pGrid->getcity(10)->getfee());

	}
}




