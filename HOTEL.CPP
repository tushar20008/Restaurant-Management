/*
CBSE PROJECT
EXECUTED BY :TUSHAR ANAND AND VATSAL AGGARWAL
*/

# include <iostream.h>
# include <fstream.h>
# include <stdio.h>
# include <conio.h>
# include <iomanip.h>
# include <ctype.h>
# include <string.h>

class Hotel
{
 int Qty,Fno;
 char FoodItem [20];
 float Price;
 public:
 int getno(){ return Fno ;}
 void Input()
 {
	cout<<"Enter Food Code : ";
	cin>>Fno;
	cout<<endl;
	cout<<"Enter Food Item : ";
	gets(FoodItem);
	cout<<endl;
	cout<<"Enter the Price : ";
	cin>>Price;
	cout<<endl;
	cout<<"Enter Quantity : ";
	cin>>Qty;
	cout<<endl;
 }
 void InputPrice()
 {
	cin>>Price;
	cout<<endl;
 }
 void InputQty()
 {
	cin>>Qty;
	cout<<endl;
 }
 void InputName()
 {
	gets(FoodItem);
	cout<<endl;
 }
 void Output()
 {
	 cout<<setw(10)<<Fno<<setw(20)<<FoodItem<<setw(10)<<Price;
	 cout<<endl;
 }
 void Output2()
 {
	 cout<<setw(10)<<FoodItem<<"\t"<<setw(5)<<Qty<<"\t"<<setw(5)<<Price;
	 cout<<endl;
 }
 void Insert();
 void Delete();
 void EditPrice();
 void EditQty();
 void EditName();
 void ShowMenu();
 void TakeOrder();
 void Billing();
 void CopyFile(char[],char[]);
 void Sort();
 void Sales();
};

void main()
{
 clrscr();
 int choice1=0,choice2;
 Hotel H;
 do
 {
	cout<<"WELCOME !!!"<<endl<<endl;
	cout<<"1.Insert New Item"<<endl;
	cout<<"2.Edit "<<endl;
	cout<<"3.Take Order"<<endl;
	cout<<"4.Total Sales"<<endl;
	cout<<"5.Quit"<<endl;
	cin>>choice1;
	switch(choice1)
	{
	 case 1:H.Insert();
		break;
	 case 2:do
		{
		 cout<<"What would you like to change??"<<endl<<endl;
		 cout<<"1.Delete a pre-existing food item"<<endl;
		 cout<<"2.Make change in the Price of a food item"<<endl;
		 cout<<"3.Make change in the Quantity of a food item"<<endl;
		 cout<<"4.Make change in the name of food item"<<endl;
		 cout<<"5.Return Back"<<endl;
		 cin>>choice2;
		 if (choice2 == 1)
		 H.Delete();
		 else if (choice2 == 2)
		 H.EditPrice();
		 else if (choice2 == 3)
		 H.EditQty();
		 else if (choice2 == 4)
		 H.EditName();
		}while(choice2 !=5);
		 break;
	 case 3:H.ShowMenu();
		break;
	 case 4:H.Sales();
		break;
	 case 5:cout<<"Thanks for coming. Do visit us Again!!"<<endl;
		break;
	}
 }while(choice1!=5);
 getch();
}

void Hotel :: Insert()
{
 fstream fil;
 fil.open("Hotel.dat",ios::app|ios::binary);
 Hotel H;
 cout<<"Enter the data of new food item"<<endl;
 H.Input();
 fil.write((char*)&H,sizeof(H));
 cout<<"Changes have been Saved"<<endl;
 H.Sort();
}

void Hotel :: Delete()
{
 fstream fil1,fil2;
 fil1.open("Hotel.dat",ios::in|ios::binary);
 fil2.open("Temp.dat",ios::out|ios::binary);
 int Fno;
 cout<<"Enter the code of food item to be deleted : ";
 cin>>Fno;
 int Delete=0;
 Hotel H;
 while(fil1.read((char*)&H,sizeof(H)))
 {
	if(!(H.Fno==Fno))
	fil2.write((char*)&H,sizeof(H));
	else
	Delete++;
 }
 fil1.close();
 fil2.close();
 if (Delete)
 {
	CopyFile("Temp.dat","Hotel.dat");
	cout<<"Changes have been made"<<endl;
 }
 else
 cout<<"Invalid Entry. Please try again."<<endl;
 H.Sort();
}

void Hotel :: EditPrice()
{
 fstream fil;
 fil.open("Hotel.dat",ios::in|ios::out|ios::binary);
 Hotel H;
 int found=0;
 int Fno;
 cout<<"Enter the code of food item in which you want to make changes : "<<endl;
 cin>>Fno;
 while(fil.read((char*)&H,sizeof(H)) && !found)
 {
	if(H.Fno==Fno)
	{
	 cout<<"Enter the new price : "<<endl;
	 H.InputPrice();
	 fil.seekg(fil.tellg()-sizeof(H));
	 fil.write((char*)&H,sizeof(H));
	 found++;
	}
 }
 if(found)
 cout<<"Your Changes have Been Saved"<<endl;
 else
 cout<<"Match not found. Please try again!!"<<endl;
 fil.close();
}

void Hotel :: EditQty()
{
 fstream fil;
 fil.open("Hotel.dat",ios::in|ios::out|ios::binary);
 Hotel H;
 int found=0;
 int Fno;
 cout<<"Enter the code of food item in which you want to make changes : "<<endl;
 cin>>Fno;
 while(fil.read((char*)&H,sizeof(H)) && !found)
 {
	if(H.Fno==Fno)
	{
	 cout<<"Enter the new Quantity :"<<endl;
	 H.InputQty();
	 fil.seekg(fil.tellg()-sizeof(H));
	 fil.write((char*)&H,sizeof(H));
	 found++;
	}
 }
 if(found)
 cout<<"Your Changes have Been Saved"<<endl;
 else
 cout<<"Match not found. Please try again!!"<<endl;
 fil.close();
}
void Hotel :: EditName()
{
 fstream fil;
 fil.open("Hotel.dat",ios::in|ios::out|ios::binary);
 Hotel H;
 int found=0;
 int Fno;
 cout<<"Enter the code of food item in which you want to make changes : "<<endl;
 cin>>Fno;
 while(fil.read((char*)&H,sizeof(H)) && !found)
 {
	if(H.Fno==Fno)
	{
	 cout<<"Enter the new name :"<<endl;
	 H.InputName();
	 fil.seekg(fil.tellg()-sizeof(H));
	 fil.write((char*)&H,sizeof(H));
	 found++;
	}
 }
 if(found)
 cout<<"Your Changes have Been Saved"<<endl;
 else
 cout<<"Match not found. Please try again!!"<<endl;
 fil.close();
}

void Hotel :: CopyFile(char C1[], char C2[])
{
 fstream fil1,fil2;
 fil1.open(C1,ios::in|ios::binary);
 fil2.open(C2,ios::out|ios::binary);
 Hotel H;
 while(fil1.read((char*)&H,sizeof(H)))
 fil2.write((char*)&H,sizeof(H));
 fil1.close();
 fil2.close();
}

void Hotel :: ShowMenu()
{
 fstream fil;
 Hotel H;
 H.Sort();
 cout<<setw(10)<<"F.Code."<<setw(20)<<"FoodItem"<<setw(10)<<"Price"<<endl;
 fil.open("Hotel.dat",ios::binary|ios::in);
 while(fil.read((char*)&H,sizeof(H)))
 {
	H.Output();
 }
 fil.close();
 H.TakeOrder();
}

void Hotel :: TakeOrder()
{
 fstream fil,fil2;
 Hotel H;
 int Qty=0,Fno;
 char Reply2;
 fil2.open("Temp2.dat",ios::binary|ios::out);
 cout<<endl<<"What would you like to Order ??"<<endl;
 do
 {
	cout<<"Enter the code of FoodItem : "<<endl;
	cin>>Fno;
	cout<<"Quantity : " <<endl;
	cin>>Qty;
	fil.open("Hotel.dat",ios::binary|ios::in|ios::out);
	while(fil.read((char*)&H,sizeof(H)))
	{
	 if(H.Fno==Fno)
	 {
		if((H.Qty-Qty)>=0)
		{
		 H.Qty=H.Qty-Qty;
		 fil.seekg(fil.tellg()-sizeof(H));
		 fil.write((char*)&H,sizeof(H));
		 H.Qty=Qty;
		 fil2.write((char*)&H,sizeof(H));
		 fil.close();
		}
		else
		{
		 cout<<"Sorry but we dont have that much "<<FoodItem <<endl;
		 cout<<"We only have " <<H.Qty<<endl;
		 fil.close();
		}
	 }
	}
	cout<<"Would you like to have anything Else (Y/N) ??"<<endl;
	cin>>Reply2;
 }while( Reply2 == 'Y' || Reply2 == 'y');
 cout<<"That was an excellent choice !"<<endl;
 cout<<"I repeat your Order"<<endl;
 cout<<setw(10)<<"FoodItem"<<"\t"<<setw(5)<<"Qty"<<"\t"<<setw(5)<<"Price"<<endl;
 fil2.close();
 H.Billing();
}

void Hotel :: Billing()
{
 fstream fil,fil2;
 Hotel H;
 int Bill=0;
 fil.open("Temp2.dat",ios::in|ios::binary);
 fil2.open("Sales.dat",ios::app|ios::binary);
 while(fil.read((char*)&H,sizeof(H)))
 {
	Bill=Bill+((H.Price)*(H.Qty));
	H.Output2();
	fil2.write((char*)&H,sizeof(H));
 }
 cout<<endl;
 cout<<"Your Total Bill including all Taxes is :- "<<Bill<<endl;
 cout<<"Thanks For Coming "<<endl;
 fil.close();
 fil2.close();
}
void Hotel :: Sales()
{
 Hotel H;
 fstream fil;
 fil.open("Sales.dat",ios::in|ios::binary);
 int Sales=0;
 while(fil.read((char*)&H,sizeof(H)))
 {
  Sales=Sales+((H.Price)*(H.Qty));
 }
 cout<<"Total Sales is "<<Sales<<endl;
 fil.close();
}

void Hotel :: Sort()
{
 fstream fil;
 Hotel H1,H2;
 fil.open("Hotel.dat",ios::in|ios::out|ios::binary);
 int N;
 fil.seekg(0,ios::end);
 N=fil.tellg()/sizeof(H1);
 for (int i=0; i<N-1; i++)
 {
  for (int j=0; j<N-1-i; j++)
  {
   fil.seekg(j*sizeof(H1));
   fil.read((char*)&H1, sizeof(H1));
   fil.read((char*)&H2, sizeof(H1));
   if(H1.getno()>=H2.getno())
   {
    fil.seekp(j*sizeof(H1));
    fil.write((char*)&H2, sizeof(H1));
    fil.write((char*)&H1, sizeof(H1));
   }
  }
 }
 fil.close();
}

/*
OUTPUT :-

WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
1
Enter the data of new food item
Enter Food Code : 2

Enter Food Item : Pizza

Enter the Price : 100

Enter Quantity : 10

Changes have been Saved

WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
1
Enter the data of new food item
Enter Food Code : 2

Enter Food Item : Burger

Enter the Price : 50

Enter Quantity : 10

Changes have been Saved

WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
3
  F.Code.         FoodItem    Price
	1            Pizza      100
	2           Burger       50

What would you like to Order ??
Enter the code of FoodItem :
1
Quantity :
1
Would you like to have anything Else (Y/N) ??
Y
Enter the code of FoodItem :
2
Quantity :
2
That was an excellent choice !
I repeat your Order
  FoodItem        Qty   Price
     Pizza          1     100
     Burger         2      50

Your Total Bill including all Taxes is :- 200
Thanks For Coming

WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
4
Total Sales is 200

WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
2
What would you like to change?
1.Delete a pre-existing food item
2.Make change in the Price of a food item
3.Make change in the Quantity of a food item
4.Make change in the name of food item
5.Return Back
1
Enter the code of food item to be deleted : 2
Changes have been made
What would you like to change??

1.Delete a pre-existing food item
2.Make change in the Price of a food item
3.Make change in the Quantity of a food item
4.Make change in the name of food item
5.Return Back
5
WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
3
  F.Code.         FoodItem    Price
	1            Pizza      100

What would you like to Order ??
Enter the code of FoodItem :
1
Quantity :
2
Would you like to have anything Else (Y/N) ??
N
That was an excellent choice !
I repeat your Order
  FoodItem        Qty   Price
     Pizza          2     100

Your Total Bill including all Taxes is :- 200
Thanks For Coming

WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
4
Total Sales is 400
WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
2
Enter the code of food item in which you want to make changes :
1
Enter the new price :
150

Your Changes have Been Saved
What would you like to change??

1.Delete a pre-existing food item
2.Make change in the Price of a food item
3.Make change in the Quantity of a food item
4.Make change in the name of food item
5.Return Back
5
WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
3
  F.Code.         FoodItem    Price
	1            Pizza      150

What would you like to Order ??
Enter the code of FoodItem :
1
Quantity :
2
Would you like to have anything Else (Y/N) ??
N
That was an excellent choice !
I repeat your Order
  FoodItem        Qty   Price
     Pizza          2     150

Your Total Bill including all Taxes is :- 300
Thanks For Coming
WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
4
Total Sales is 700
WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
2
What would you like to change??

1.Delete a pre-existing food item
2.Make change in the Price of a food item
3.Make change in the Quantity of a food item
4.Make change in the name of food item
5.Return Back
3
Enter the code of food item in which you want to make changes :
1
Enter the new Quantity :
20

Your Changes have Been Saved
What would you like to change??

1.Delete a pre-existing food item
2.Make change in the Price of a food item
3.Make change in the Quantity of a food item
4.Make change in the name of food item
5.Return Back
5
WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
3
  F.Code.         FoodItem    Price
	1            Pizza      150

What would you like to Order ??
Enter the code of FoodItem :
1
Quantity :
21
Sorry but we dont have that much Pizza
We only have 20
Would you like to have anything Else (Y/N) ??
Y
Enter the code of FoodItem :
1
Quantity :
2
Would you like to have anything Else (Y/N) ??
N
I repeat your Order
  FoodItem        Qty   Price
     Pizza          2     150

Your Total Bill including all Taxes is :- 300
Thanks For Coming
WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
4
Total Sales is 1000
WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
2
What would you like to change ??
4
Enter the code of food item in which you want to make changes :
1
Enter the new name :
V.Pizza

Your Changes have Been Saved
What would you like to change??

1.Delete a pre-existing food item
2.Make change in the Price of a food item
3.Make change in the Quantity of a food item
4.Make change in the name of food item
5.Return Back
5
WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
3
3
  F.Code.         FoodItem    Price
	1          V.Pizza      150

What would you like to Order ??
Enter the code of FoodItem :
1
Quantity :
4
Would you like to have anything Else (Y/N) ??
I repeat your Order
  FoodItem        Qty   Price
   V.Pizza          4     150

Your Total Bill including all Taxes is :- 600
Thanks For Coming
WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
4
Total Sales is 1600
WELCOME !!!

1.Insert New Item
2.Edit
3.Take Order
4.Total Sales
5.Quit
5
Thanks for coming. Do visit us Again!!

*/
