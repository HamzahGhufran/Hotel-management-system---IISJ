
// Program to manage a hotel 



//header files used 

#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<iomanip.h>
#include<stdio.h>
#include<dos.h>
#include<process.h>
#include<conio.h>



class hotel
{
    int room_no;
    char name[30];
    char address[50];
    char phone[10];
	int nod;
    
    public:
    void main_menu();    //to dispay the main menu
    void add();        //to book a room
    void display();    //to display the customer record
    void rooms();    //to display alloted rooms
    void edit();    //to edit the customer record
    int check(int);    //to check room status
    void modify(int);    //to modify the record
    void delete_rec(int);//to delete the record
	void tariffcalc();  //TO CALCULATE TARIFF
	void exiting() ;            //to exit from the program
};



 

                      //program definitions




void hotel::main_menu()
{
    int choice;
    
    
    while(choice!=6)
	{
        
        cout<<"\n\t\t\t\t*************";
        cout<<"\n\t\t\t\t* MAIN MENU *";
        cout<<"\n\t\t\t\t*************";
        cout<<"\n\n\n\t\t\t1.Book A Room";
        cout<<"\n\t\t\t2.Customer Record";
        cout<<"\n\t\t\t3.Rooms Allotted";
        cout<<"\n\t\t\t4.Edit Record";
		cout<<"\n\t\t\t5.Exit";
        cout<<"\n\n\t\t\tEnter Your Choice: ";
        cin>>choice;

		system("cls");

        
        switch(choice)
        {
            case 1: add();
                    break;
            case 2: display();
                    break;
            case 3: rooms();
                    break;
            case 4: edit();
                    break;
            case 5: exiting();
				    break;
            default:
                    {
                        cout<<"\n\n\t\t\tWrong choice!!!";
                        cout<<"\n\t\t\tPress any key to continue!!";
						
                    }
        }
    }
}



 
void hotel::add()
{
    
    int r,flag;
    ofstream fout("Record.dat",ios::app);
    
    cout<<"\n Enter Customer Details";
    cout<<"\n **********************";
    cout<<"\n\n Room no: ";
    cin>>r;
    flag = check(r);
    
    if(flag == 1)
	{cout<<"\n Sorry..!!!Room is already booked";}
    
	else
    {
        room_no=r;
        cout<<" Name: ";
        cin>>name;
        cout<<"\n Address: "; 
        cin>>address;
        cout<<" \nPhone No: ";
        cin>>phone;
        fout.write((char*)this,sizeof(hotel));
        cout<<"\n Room is booked!!!";
    }
   
    fout.close();
	tariffcalc();
}





 
void hotel::display()
{
    
    ifstream fin("Record.dat",ios::in);
    int r,flag=0;
    cout<<"\n Enter room no: ";
    cin>>r;
    
    while(!fin.eof())
    {
        fin.read((char*)this , sizeof(hotel));
        if(room_no==r)
        {
            cout<<"\n Cusromer Details";
            cout<<"\n ****************";
            cout<<"\n\n Room no: "<<room_no;
            cout<<"\n Name: "<<name;
            cout<<"\n Address: "<<address;
            cout<<"\n Phone no: "<<phone;
            flag=1;
            break;
        }
    }
    
    if(flag==0)
        cout<<"\n Sorry Room no. not found or vacant!!";
       
    fin.close();
}





 
void hotel::rooms()
{
    ifstream fin("Record.dat",ios::in);
    cout<<"\n\t\t\tList Of Rooms Allotted";
    cout<<"\n\t\t\t*********************";
    cout<<"\n\n Room No.\t\tName\t\tAddress\t\tPhone No.\n";
    
    while(!fin.eof())
    {
        fin.read((char*)this,sizeof(hotel));
        cout<<"\n\n "<<room_no<<"\t\t"<<name;
        cout<<"\t\t"<<address<<"\t\t"<<phone;
    }
    
    cout<<"\n\n\n\t\t\tPress any key to continue!!";
    
    fin.close();
}
 
void hotel::edit()
{
    int choice,r;
    
    cout<<"\n EDIT MENU";
    cout<<"\n *********";
    cout<<"\n\n 1.Modify Customer Record";
    cout<<"\n 2.Delete Customer Record";
    
    cout<<"\n Enter your choice: ";
    cin>>choice;
    
    cout<<"\n Enter room no: ";
    cin>>r;
    
    switch(choice)
    {
        case 1: modify(r);
                break;
        case 2: delete_rec(r);
                break;
        default: cout<<"\n Wrong Choice!!";
    }
    
}
 



int hotel::check(int r)
{
    int flag=0;
    ifstream fin("Record.dat",ios::in);
    while(!fin.eof())
    {
        fin.read((char*)this,sizeof(hotel));
        if(room_no==r)
        {
            flag=1;
                break;
        }
    }
    
    fin.close();
    return(flag);
}
 





void hotel::modify(int r)
{
    long pos,flag=0;
    fstream file("Record.dat",ios::in|ios::out|ios::binary);
    
    while(!file.eof())
    {
        pos=file.tellg();
        file.read((char*)this,sizeof(hotel));
        if(room_no==r)
        {
            cout<<"\n Enter New Details";
            cout<<"\n *****************";
            cout<<"\n Name: ";
            gets(name);
            cout<<" Address: ";
            gets(address);
            cout<<" Phone no: ";
            gets(phone);
            
            file.seekg(pos);
            file.write((char*)this,sizeof(hotel));
            cout<<"\n Record is modified!!";
            flag=1;
            break;
        }
    }
    
    if(flag==0)
        cout<<"\n Sorry Room no. not found or vacant!!";
        
    file.close();
}






 
void hotel::delete_rec(int r)
{
    int flag=0;
    char ch;
    ifstream fin("Record.dat",ios::in);
    ofstream fout("temp.dat",ios::out);
    
    while(!fin.eof())
    {
        fin.read((char*)this,sizeof(hotel));
        if(room_no==r)
        {
            cout<<"\n Name: "<<name;
            cout<<"\n Address: "<<address;
            cout<<"\n Pone No: "<<phone;
            cout<<"\n\n Do you want to delete this record(y/n): ";
            cin>>ch;
            
            if(ch=='n' || ch == 'N')
            fout.write((char*)this,sizeof(hotel));
            
            flag=1;
        }
        else
            fout.write((char*)this,sizeof(hotel));
    }
    
    fin.close();
    fout.close();
    
    if(flag==0)
        cout<<"\n Sorry room no. not found or vacant!!";
    else
    {
        remove("Record.dat");
        rename("temp.dat","Record.dat");
    }
}




void hotel::exiting()
{
	system("cls") ;

	char ch ;
	cout<<"\n\n\t\t********************************************************************************* \n";
	cout<<"\t\t *  __________  _       _  ____________  __       __    __      __   _________  * \n";
	cout<<"\t\t * |_________| | |     | | | |______| | |  ##    | |   | |    #  #  |  _______| * \n";
	cout<<"\t\t *     | |     | |     | | | |      | | | | ##   | |   | |  #  #    | |         * \n";
	cout<<"\t\t *     | |     | |_____| | | |      | | | |  ##  | |   | |#  #      | |_______  * \n";
	cout<<"\t\t *     | |     | |_____| | | |______| | | |   ## | |   | |  <       |________ | * \n";
	cout<<"\t\t *     | |     | |     | | | |______| | | |    ##  |   | |#  #              | | * \n";
	cout<<"\t\t *     | |     | |     | | | |      | | | |      | |   | |  #  #     _______| | * \n";
	cout<<"\t\t *     |_|     |_|     |_| |_|      |_| |_|      |_|   |_|    # _#  |_________| * \n";
	cout<<"\t\t ******************************************************************************** \n";
	cout<<"\n\n\t\t ******************************************************************************** \n";
	cout<<"\t\t ** S.NO  **            MADE BY:                **   CLASS   **   ROLL NO.   **** \n";
	cout<<"\t\t ******************************************************************************** \n";
	cout<<"\t\t **  1.   ** MOHAMMAD HAMZAH GHUFRAN            **   XII-B-5 **      20      **** \n";
	cout<<"\t\t **  2.   ** MOHAMMAD AADIL KHAN                **   XII-B-5 **      21      **** \n";
	cout<<"\t\t **  3.   ** SYED MONIS IQBAL                   **   XII-B-5 **              **** \n";
	cout<<"\t\t **  4.   ** ABDUL HADI ABDUL WAHED             **   XII-B-5 **      13      **** \n";
	cout<<"\t\t ******************************************************************************** \n\n";
	cout<<"\n Press any alphabet to continue_ ";
	cin>>ch ;
	exit(0) ;
}

void hotel::tariffcalc()
{
	int nod , servdays ;
	double tariff ;
	cout<<"\n\n\n Enter no of days to stay:";
	cin>>nod;
	cout<<"\n Enter no of days hotel services will be required ";
	cin>>servdays ;

	tariff = 83*nod + 72.5*servdays ;

	cout<<"\n\n\n The total due amount is: Rs."<<tariff<<endl<<endl;
}



 
void main()
{
    hotel h;
    
     cout<<"\n\n\n";
    cout<<"\t\t\t\t\t"<<"****************************** \n";
	cout<<"\t\t\t\t\t"<<"*  HOTEL MANAGEMENT PROJECT  *"<<endl;
    cout<<"\t\t\t\t\t"<<"****************************** \n\n\n\n";

	cout<<"\t\t\t\t\t\t\t\t\t\t\t ***************************\n";
	cout<<"\t\t\t\t\t\t\t\t\t\t\t BY: MOHAMMAD HAMZAH GHUFRAN"<<endl;
	cout<<"\t\t\t\t\t\t\t\t\t\t\t     MOHAMMAD AADIL KHAN"<<endl;
	cout<<"\t\t\t\t\t\t\t\t\t\t\t     SYED MONIS IQBAL"<<endl;
	cout<<"\t\t\t\t\t\t\t\t\t\t\t     ABDUL HADI"<<endl;
	cout<<"\t\t\t\t\t\t\t\t\t\t\t CLASS: XII-B-5"<<endl;
	cout<<"\t\t\t\t\t\t\t\t\t\t\t *************************** \n\n\n";




    h.main_menu();
}