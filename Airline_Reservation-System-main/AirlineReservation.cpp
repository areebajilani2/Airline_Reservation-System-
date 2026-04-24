#include<iostream>
#include<Windows.h>  //for changing console colors
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

//===================================================	 FUNCTIONS	  ===========================================================

/////////////////////////////////////////////////////	COLORS FUNCTION	  ///////////////////////////////////////////////////////
void white(){
		HANDLE w= GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(w,7);
}																		
void orange(){
		HANDLE o= GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(o,6);
}								
void red(){
		HANDLE r= GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(r,4);
}
void cyan(){
		HANDLE c= GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(c,3);
}
/////////////////////////////////////////////////////	CLASS COORDINATES FUNCTION	/////////////////////////////////////////////
void xy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//===================================================	 CLASSES	=============================================================

//	FORWARD DECLARATION
class Admin;

/////////////////////////////////////////////////////	CLASS AIRLINE	/////////////////////////////////////////////////////////
class Airline{
	public:
		string airline_name;
		//construcor		
		Airline(){
			airline_name="|  PAK AIRLINE  |";
		}
		// Account authentication
		int authentication(int i, string user, string pass){
			int confirmation=0;
			string st_user, st_pass;
			if(i==1){
				fstream file;
				file.open("proaccounts.txt", ios::in);
				while(file>>st_user>>st_pass){
					if(user == st_user){
						xy(4,4);
						red();
						cout<<'\a';
						cout<<"| o User-Name Already Taken....";
						Sleep(1);
						white();
						file.close();
						return confirmation = -1;
					}
				}
				file.close();
			}
			if(i==1){
				fstream file;
				file.open("proaccounts.txt", ios::app);
				file<<user<<" "<<pass<<endl;
				file.close();
			}
			else if(i==2){
				fstream file;
				file.open("proaccounts.txt", ios::in);
				while(file>>st_user>>st_pass){
					if(st_user==user && st_pass==pass){
						xy(8,12);
						orange();
						cout<<"| o LOGIN SUCCESSFUL....";
						Sleep(1);
						white();
						file.close();
						return confirmation = 1;
					}
				}		
				file.close();
				xy(8,12);
				red();
				cout<<'\a';
				cout<<"| o LOGIN FAILED (Wrong Password OR username)....";
				Sleep(2);
				white();
			}
			return confirmation;
		}
		
		// LOGO
		void air_detail(){
			cyan();
			xy(9,2);
			cout<<"=================";
			xy(9,3);
			cout<<"|  PAK AIRLINE  |";
			xy(9,4);
			cout<<"=================";
			white();
		}
		
		// MAIN START MENU
		void main_menu(){
			xy(8,7);
			cout<<"| 1) Admin.";
			xy(8,9);
			cout<<"| 2) Customer.";
			xy(8,11);
			cout<<"| 3) Exit.";			
		}
		
		// CUSTOMER MENU
		void menu(){
			xy(8,7);
			cout<<"| 1) Sign Up.";
			xy(8,9);
			cout<<"| 2) Login.";
			xy(8,11);
			cout<<"| 3) Return To Previous Menu.";
			xy(8,13);
			cout<<"| 4) Exit.";
		}
};

/////////////////////////////////////////////////////	CLASS NODE	 ////////////////////////////////////////////////////////////
class Node{
	public:
		Node *prev;
		Node *next;
		string Pnr,
			   Name,
			   Age,
			   Number,
			   Cnic,
			   Seat_no,
			   Departure,
			   Destination,
			   Price;
		
		Node(string pnr, string name, string age, string number,
			 string cnic, string seat_no, string departure,
			 string destination, string price){
			Pnr = pnr;
			Name = name;
			Age = age;
			Number = number;
			Cnic = cnic;
			Seat_no = seat_no;
			Departure = departure;
		   	Destination = destination;
			Price = price;	
			prev = NULL;
			next = NULL;
		}
};

/////////////////////////////////////////////////////	CLASS LINKEDLIST   //////////////////////////////////////////////////////
class LinkedList{
	private:
		Airline *A;
		Node *head = NULL;
		Node *tail = NULL;
	
	public:
		// INSERTION
		void insertAtStart(string pnr, string name, string age, string number, 
						   string cnic, string seat_no, string departure,
			 			   string destination, string price){
			 	
			Node *n_node = new Node(pnr, name, age, number, cnic, seat_no,
									departure, destination, price);
			if(tail == NULL){
				tail = n_node;
			}
			n_node->prev = head;
			if(head != NULL){
				head->next = n_node;
			}
			head = n_node;
		}		

		// DELETION
		void deleteByData(string d){
			A->air_detail();
		    if(head == NULL){
				cout<<"\no | No Tickets to Delete.";
				return;
		    }
		    Node *temp = tail;
		    while(temp != NULL){
		        if(d == temp->Pnr){
					cyan();
					cout<<"\n\n\t| o  PNR   : "<<temp->Pnr<<endl;
					cout<<"\t| o  Name  : "<<temp->Name<<endl;
					cout<<"\t| o  Age   : "<<temp->Age<<endl;
					cout<<"\t| o  Number : "<<temp->Number<<endl;
					cout<<"\t| o  CNIC   : "<<temp->Cnic<<endl;
					cout<<"\t| o  Seat No   : "<<temp->Seat_no<<endl;
					cout<<"\t| o  Departure   : "<<temp->Departure<<endl;
					cout<<"\t| o  Destination : "<<temp->Destination<<endl;
					cout<<"\t| o  Price  : "<<temp->Price<<endl;
					white();
					cout<<"\n\n\t    | o ";
					system("pause");
					system("cls");
					red();
		            cout<<" o | '"<<d<<"' Deleted Successfully..."<<endl;
		            white();
					if(temp == tail){
		                tail = temp->next;
		                if(tail != NULL) {
		                    tail->prev = NULL;
		                } else {
		                    // If the list is empty, clear the file
		                    fstream file;
		                    file.open("Tickets.txt", ios::out | ios::trunc);
		                    file.close();
		                }
		            }
		            else if(temp == head){
		                head = temp->prev;
		                head->next = NULL;
		            }
		            else{
		                temp->prev->next = temp->next;
		                temp->next->prev = temp->prev;
		            }
		            delete temp;
		            // Update the file
		            fstream file;
		            file.open("Tickets.txt", ios::out);
		            Node *temp2 = tail;
		            while(temp2 != NULL){
		                file<<"PNR "<<temp2->Pnr<<endl;
		                file<<"Name "<<temp2->Name<<endl;
		                file<<"Age "<<temp2->Age<<endl;
		                file<<"Number "<<temp2->Number<<endl;
		                file<<"CNIC "<<temp2->Cnic<<endl;
		                file<<"Seat-No "<<temp2->Seat_no<<endl;
		                file<<"Departure "<<temp2->Departure<<endl;
		                file<<"Destination "<<temp2->Destination<<endl;
		                file<<"Price "<<temp2->Price<<endl<<endl;
		                temp2 = temp2->next;
		            }
		            file.close();
		            return;
		        }
		        temp = temp->next;
		    }
		    cout<<" o | '"<<d<<"' Not Found..."<<endl;
		}
		// SEARCH
		void search(string d){
			Node *temp = tail;
			A->air_detail();
			xy(8,7);
		    if(head == NULL){
				cout<<"o | No Tickets to Search.";
				return;
		    }
			while(temp != NULL){
				if(d == temp->Pnr){
					cyan();
					cout<<"\n\n\t| o  PNR   : "<<temp->Pnr<<endl;
					cout<<"\t| o  Name  : "<<temp->Name<<endl;
					cout<<"\t| o  Age   : "<<temp->Age<<endl;
					cout<<"\t| o  Number : "<<temp->Number<<endl;
					cout<<"\t| o  CNIC   : "<<temp->Cnic<<endl;
					cout<<"\t| o  Seat No   : "<<temp->Seat_no<<endl;
					cout<<"\t| o  Departure   : "<<temp->Departure<<endl;
					cout<<"\t| o  Destination : "<<temp->Destination<<endl;
					cout<<"\t| o  Price  : "<<temp->Price<<endl;
					white();					
					return;
				}
				temp = temp->next;
			}
			cout<<" o | '"<<d<<"' Not Found..."<<endl;
		}
		
		// TRAVERSAL
		void display(){
			Node *temp = tail;
			A->air_detail();
			xy(8,7);
		    if(head == NULL){
				cout<<"o | No Tickets to Display.";
				return;
		    }
			while(temp!=NULL){
				cyan();
				cout<<"\n\n\t| o  PNR   : "<<temp->Pnr<<endl;
				cout<<"\t| o  Name  : "<<temp->Name<<endl;
				cout<<"\t| o  Age   : "<<temp->Age<<endl;
				cout<<"\t| o  Number : "<<temp->Number<<endl;
				cout<<"\t| o  CNIC   : "<<temp->Cnic<<endl;
				cout<<"\t| o  Seat No   : "<<temp->Seat_no<<endl;
				cout<<"\t| o  Departure   : "<<temp->Departure<<endl;
				cout<<"\t| o  Destination : "<<temp->Destination<<endl;
				cout<<"\t| o  Price  : "<<temp->Price<<endl<<endl;
				temp = temp->next;
				cout<<endl<<endl;			
			}
			white();	
		}
};

/////////////////////////////////////////////////////	CLASS FLIGHT   //////////////////////////////////////////////////////////
class Flight{
	public :
		Airline *A;
	
		void flight_menu(){
			A->air_detail();
			xy(8,7);
			cout<<"|   o FLIGHT DETAILS";
			xy(8,9);
			cout<<"| 1) International FLights.";
			xy(8,11);
			cout<<"| 2) Domestic Flights.";
			xy(8,13);
			cout<<"| 3) Exit.";
		}
};

/////////////////////////////////////////////////////	CLASS TICKET  ///////////////////////////////////////////////////////////
class Ticket : public Flight {	
	private :
		Airline *A;
		int pnr;
		int confirmation=0;

	public :
		// TICKET DESTROYER
		~Ticket(){}
		
		// GENERATING PNR
		void generating_pnr(){
			A->air_detail();
			xy(8,7);
			orange();
			cout<<"|   o Generating PNR.";
			for(int i=0 ; i<3 ; i++){
				Sleep(1);
				cout<<".";		
			}
			xy(8,9);
			cout<<"| o Successfully Generated....";
			white();
			Sleep(2);
			system("cls");
			int no;
			string word;
			fstream file;
			file.open("pnr_generator.txt", ios::in);
			file>>word;
			file.close();
			no = stoi(word);
			pnr=rand() % (99999 - 9999 + 1) + no;
			no = no+123;
			word = to_string(no);
			file.open("pnr_generator.txt", ios::out);
			file<<word;
			file.close();
		}
		
		// GENERATING TICKET PROCESS
		int generating_ticket(){
			generating_pnr();
			A->air_detail();
			xy(8,7);
			cout<<"|   o Your Ticket PNR Is = "<<pnr;
			xy(8,9);
			cout<<"| 1) Proceed Further.";
			xy(8,11);
			cout<<"| 2) Cancel Process (Main-menu).";
			xy(8,13);
			cout<<"| 3) Exit.";
			
			return pnr;
		}

		// CHECK EXITING TICKET
		int check_existing_ticket(string pnr){
a:				
			fstream file;
			file.open("Tickets.txt", ios::in);
			string line, pnr1, pnr2;
			while(file>>pnr1){
				if(pnr==pnr1){
					xy(8,12);
					cout<<"| o PNR '"<<pnr<<"' FOUND....";
					Sleep(2);
					system("cls");
					A->air_detail();
					xy(9,7);
					orange();
					cout<<"PNR "<<pnr<<endl;
					int z=9;
					for(int i=0 ; i<8 ; i++){
						xy(9,z);
						file>>pnr1>>pnr2;
						cout<<pnr1<<"  :  "<<pnr2;
						z++;
						z++;
					}				
					cout<<endl<<endl;
					file.close();
					xy(8,26);
					string ch;
					cyan();
					cout<<"| o Do you Want to Cancel this Ticket? ( Y / N ) : ";
					white();
					cin>>ch;
					if(ch == "y" || ch =="Y"){
						fstream file1;
						fstream file2;
						file1.open("Tickets.txt", ios::in);
						file2.open("Temp.txt", ios::out);
						int tmp = 0;
						string word1, word2;
						while(file1>>word1>>word2){
							if(word1 == "PNR" && word2 == pnr ){
								tmp++;
							}
							if(tmp>0 && tmp<9){
								tmp++;
								if(tmp == 9){
									tmp = 0;
								}
							}
							else{
								file2<<word1<<" "<<word2<<endl;
							}
						}
						file1.close();
						file2.close();
						file1.open("Tickets.txt", ios::out | ios::trunc);
						file2.open("Temp.txt", ios::in);
						while(file2>>word1>>word2){
							if(word1 == "PNR"){
								file1<<endl;
							}
							file1<<word1<<" "<<word2<<endl;
						}	
						file1.close();
						file2.close();
						remove("Temp.txt");
						system("cls");
						red();
						cout<<'\a';
						xy(8,17);
						cout<<" | o TICKET CANCELLED....";
						white();
						xy(8,20);
						cout<<" | o ";
				    	system("pause");
				    	system("cls");
				    	return confirmation;					
					}
					else if(ch == "n" || ch =="N"){
						return confirmation;
					}
					else{
						system("cls");
						xy(4,4);
						red();
						cout<<'\a';
						cout<<"INVALID ENTRY.........";
				    	white();
				    	cout<<"\n\n\t | o ";
				    	system("pause");
				    	system("cls");
				    	goto a;
					}
				}			
			}
			system("cls");
			A->air_detail();
			red();
			xy(8,12);
			cout<<"| o PNR "<<pnr<<" NOT FOUND....";
			white();
			xy(8,15);
			string ch;			
			xy(8,19);
			cout<<"| o";
			system("pause");
			return confirmation;
		}
};

/////////////////////////////////////////////////////	CLASS PASSENGER	 ////////////////////////////////////////////////////////
class Passenger {
	private :
		Airline *A;
		Ticket *T;
		string f_name;
		string s_name;
		int age;
		long long phone;
		long long cnic;

	public :		
		// CANCEL TICKET
		~Passenger(){
			delete T;
			red();
			cout<<'\a';
			cout<<"\n\n\t | o TICKET CANCELLED....";
			white();
			system("pause");
		}
		
		// PASSENGER MENU
		void passenger_menu(){
			A->air_detail();
			xy(8,7);
			cout<<"| 1) Flight Details.";
			xy(8,9);
			cout<<"| 2) Check Existing Ticket.";
			xy(8,11);
			cout<<"| 3) Log-out.";
			xy(8,13);
			cout<<"| 4) Exit.";
		}
		
		// INSERT PASSENGER INFORMATION
		void get_passenger_details(){
		s:
			A->air_detail();
			xy(8,7);
			cout<<"| o First Name : ";
			xy(40,7);
			cout<<" o Second Name : ";
			xy(8,9);
			cout<<"| o Enter Age : ";
			xy(8,11);
			cout<<"| o Enter Phone Number :";
			xy(8,13);
			cout<<"| o Enter CNIC : ";
			xy(26,7);
			cin>>f_name;
			xy(58,7);
			cin>>s_name;
			xy(25,9);
			cin>>age;
			while (cin.fail()){
		        cin.clear();
		        cin.ignore(256,'\n');
		        system("cls");
		        red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
		    	white();
		    	cout<<"\n\n\t | o ";
		    	system("pause");
		    	system("cls");
		   	    goto s;
		  	}
			xy(35,11);
			cin>>phone;
			while (cin.fail()){
		        cin.clear();
		        cin.ignore(256,'\n');
		        system("cls");
		        red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
		    	white();
		    	cout<<"\n\n\t | o ";
		    	system("pause");
		    	system("cls");
		   	    goto s;
		  	}
		  	if(phone>999999999 && phone<99999999999){}
			else{
				system("cls");
		        red();
				cout<<'\a';
				cout<<"INVALID PHONE NUMBER.........(11-DIGITS)";
		    	white();
		    	cout<<"\n\n\t | o ";
		    	system("pause");
		    	system("cls");
		   	    goto s;
			}
			xy(25,13);
			cin>>cnic; 
			while (cin.fail()){
		    	cin.clear();
		        cin.ignore(256,'\n');
		        system("cls");
		        red();
				cout<<'\a';
				cout<<"INVALID CNIC .........(FORMAT - 03XXXXXXXXX)";
		    	white();
		    	cout<<"\n\n\t | o ";
		    	system("pause");
		    	system("cls");
		   	    goto s;
		  	}
		 	if(cnic>999999999999 && cnic<9999999999999){}
			else{
				system("cls");
		        red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
		    	white();
		    	cout<<"\n\n\t | o ";
		    	system("pause");
		    	system("cls");
		   	    goto s;
			}
			string c_cnic;		 
		  	string s; 
		  	stringstream ss;  
		  	ss<<cnic;  
		 	ss>>s;  
		  	fstream file;
			file.open("Tickets.txt", ios::in);
			
			while(file>>c_cnic){				
				if(s==c_cnic){
					system("cls");
					red();
					cout<<"\n\n\t\t| o CNIC ALREADY REGISTERED...";
					white();
					cout<<"\n\n\t | o ";
					system("pause");
					system("cls");
					goto s;
				}
			}		
		}
		
		// SHOW PASSENGER INFORMATION
		void display_passenger_details(){
st:
			system("cls");
			A->air_detail();
			cyan();
			xy(8,7);
			cout<<"| o --> RE-CHECK DETAILS ENTERED.";
			white();
			xy(8,9);
			cout<<"| o Name : "<<f_name<<" "<<s_name;
			xy(8,11);
			cout<<"| o Age : "<<age;
			xy(8,13);
			cout<<"| o Phone Number : "<<phone;
			xy(8,15);
			cout<<"| o CNIC : "<<cnic;
			xy(8,17);
			white();
			cout<<"| 1)  Want to Correct Information.";
			xy(8,19);
			cout<<"| 2)  Proceed. ";
			string ch;
			xy(1,21);
			cyan();
			cout<<" => Enter Your Choice : ";
			white();
			cin>>ch;
			// WANT TO CHANGE INFORMATION ENTERED
			if(ch == "1"){
				system("cls");
				get_passenger_details();
				goto st;
			}
			// PROCEED
			else if(ch == "2"){
				return;
			}
			// INVALID
			else{
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");
				goto st;				
			}
		}		
		
		// STORING PASSENGER INFO IN FILE
		void save_passenger_details(){
			fstream file;	
			file.open("Tickets.txt",ios::app);
			file<<"Name "<<f_name<<"_"<<s_name<<endl;
			file<<"Age "<<age<<endl;
			file<<"Number "<<phone<<endl;
			file<<"CNIC "<<cnic<<endl;
			file.close();
		}
};

/////////////////////////////////////////////////////	CLASS ADMIN	  ///////////////////////////////////////////////////////////
class Admin{
	public:
		Airline *A;
		string country[4],
			   city[8], 
			   seats[8], 
			   date[8], 
			   price[8], 
			   word,
			   ch;
		string d_city[4],
			   d_seats[4],
			   d_date[4],
			   d_price[4],
			   d_time = "9:30:00_AM";
		
		int i=0, 
		    co=0, 
			ci=0, 
			se=0, 
			da=0, 
			pr=0, 
			z, 
			y;
	
		// READING FROM FILE 	
		Admin(){
			fstream file;
			// For International 
			file.open("Inter_Data.txt", ios::in);
			// READING AND STORING IN ARRAYS
			while(file>>word){
				//country
				if(i<4){
					country[co] = word;
					co++;
				}
				//cities
				else if(i<12){
					city[ci] = word;
					ci++;
				}
				//seats
				else if(i<20){
					seats[se] = word;
					se++;
				}
				//date
				else if(i<28){
					date[da] = word;
					da++;
				}
				// price
				else{
					price[pr] = word;
					pr++;
				}
				i++;
			}
			file.close();
			// For Domestic
			file.open("Dom_Data.txt", ios::in);
			// READING AND STORING IN ARRAYS
			i=0, ci=0, se=0, da=0, pr=0;
			while(file>>word){
				//cities
				if(i<4){
					d_city[ci] = word;
					ci++;
				}
				//seats
				else if(i<8){
					d_seats[se] = word;
					se++;
				}
				//date
				else if(i<12){
					d_date[da] = word;
					da++;
				}
				// price
				else{
					d_price[pr] = word;
					pr++;
				}
				i++;
			}
			file.close();			 
		}
		
		/* INSERTING DATA BACK TO FILE 
		   INCASE OF ANY CHANGES OCCURED */
		int Insertion_in_File(){
			fstream file;
			// For International
			file.open("Inter_Data.txt", ios::out);
			co=0, ci=0, se=0, da=0, pr=0;
			for(int i=0 ; i<36 ; i++){
				if(i<4){
					file<<country[co]<<" ";
					co++;
				}
				// cities
				else if(i<12){
					file<<city[ci]<<" ";
					ci++;
				}
				// seats
				else if(i<20){
					file<<seats[se]<<" ";
					se++;
				}
				// date
				else if(i<28){
					file<<date[da]<<" ";
					da++;
				}		
				// price
				else{			
					file<<price[pr]<<" ";
					pr++;
				}
				file<<endl;
			}
			file.close();
			// For Domestic
			file.open("Dom_Data.txt", ios::out);
			ci=0, se=0, da=0, pr=0;
			for(int i=0 ; i<16 ; i++){
				// cities
				if(i<4){
					file<<d_city[ci]<<" ";
					ci++;
				}
				// seats
				else if(i<8){
					file<<d_seats[se]<<" ";
					se++;
				}
				// date
				else if(i<12){
					file<<d_date[da]<<" ";
					da++;
				}		
				// price
				else{			
					file<<d_price[pr]<<" ";
					pr++;
				}
				file<<endl;
			}
			file.close();
			return 1;				
		}
		
		// ADMIN USER-PASS
		bool Admin_acc(){
			string user, pass, username, password;
			fstream file;
			file.open("adminaccount.txt", ios :: in);
			file>>user>>pass;
			file.close();
			system("cls");
			A->air_detail();
			string ch;
			xy(8,7);
			cyan();
			cout<<"| o ADMIN LOGIN. ";
			xy(8,9);
			cout<<"| o Enter User-Name : ";
			xy(8,11);
			cout<<"| o Enter Password  : ";
			xy(31,9);
			cin>>username;
			xy(31,11);
			cin>>password;
			if(username == user && password == pass){
				xy(8,12);
				orange();
				cout<<"| o LOGIN SUCCESSFUL....";
				Sleep(1);
				white();
				system("cls");	
				return true;			
			}			
			else{
				xy(8,12);
				red();
				cout<<'\a';
				cout<<"| o LOGIN FAILED (Wrong Password OR username)....";
				Sleep(2);
				white();
				return false;		
			}
		}
		
		// INTERNATIONAL UPDATE FILE DATA
		int Update_Data(){
			system("cls");
			A->air_detail();
			xy(8,7);
			cout<<"| 1) Change Flights Destination.";
			xy(8,9);
			cout<<"| 2) Change Flights Date.";
			xy(8,11);
			cout<<"| 3) Change Flights Prices.";
			xy(8,13);
			cout<<"| 4) Return to Previous Menu.";
			xy(8,15);
			cout<<"| 5) Exit.";
			xy(1,17);
			cyan();
			cout<<"=> ENTER YOUR CHOICE : ";
			white();
			cin>>ch;
			
			////////  Change flight destination
cfde:
			if(ch == "1"){
				system("cls");
				z=7;
				for(int j=0 ; j<4 ; j++){
					xy(8,z);
					cout<<j+1<<") "<<country[j];
					z+=2;
				}
				xy(1,17);
				cyan();
				cout<<" => Choose which Flight's Destination you want to change : ";
				white();
				cin>>i;
				if(i>0 && i<5){
					xy(1,19);
					cyan();					
					cout<<" => Enter Country Name : ";
					white();
					cin>>country[i-1];
					xy(1,21);
					cyan();
					cout<<" => Enter 1st City Name of '"<<country[i-1]<<"' : ";
					white();
					cin>>city[(i*2)-2];
					xy(1,22);
					cyan();
					cout<<" => Enter 2nd City Name of '"<<country[i-1]<<"' : ";
					white();
					cin>>city[(i*2)-1];
				}
				else{
					system("cls");
					xy(4,4);
					red();
					cout<<'\a';
					cout<<"INVALID ENTRY.........";
					white();
					xy(4,6);
					system("pause");
					system("cls");	
					goto cfde;
				}
			}		
			////////  Change flight dates
			else if(ch == "2"){
cfda:
				system("cls");
				A->air_detail();
				cyan();
				xy(8,7);
				cout<<"Sr   Country / City";
				xy(7,8);
				cout<<"";
				white();
				z = 10;
				for(int j=0 ; j<4 ; j++){
					xy(8,z);
					cout<<(j*2)+1<<") "<<country[j]<<" / "<<city[j*2];
					z+=2;
					xy(8,z);
					cout<<(j*2)+2<<") "<<country[j]<<" / "<<city[(j*2)+1];
					z+=2;
				}
				cyan();
				cout<<"\n\n => Choose which Flight's Date you want to change : ";
				white();
				cin>>i;
				cyan();
				cout<<"\n => Assign New Date (M/D/Y) : ";
				white();
				// invalid
				if(i<1 || i>8){
					system("cls");
					xy(4,4);
					red();
					cout<<'\a';
					cout<<"INVALID ENTRY.........";
					white();
					xy(4,6);
					system("pause");
					system("cls");	
					goto cfda;					
				}
				else{
					cin>>date[i-1];
				}				
			}		
			////////  Change flight Prices
			else if(ch == "3"){
cfp:
				system("cls");
				A->air_detail();
				cyan();
				xy(8,7);
				cout<<"Sr   Country / City";
				xy(7,8);
				cout<<"";
				white();
				z = 10;				
				for(int j=0 ; j<4 ; j++){
					xy(8,z);
					cout<<(j*2)+1<<") "<<country[j]<<" / "<<city[j*2];
					z+=2;
					xy(8,z);
					cout<<(j*2)+2<<") "<<country[j]<<" / "<<city[(j*2)+1];
					z+=2;
				}
				cyan();
				cout<<"\n\n => Choose which Flight's Price you want to change : ";
				white();
				cin>>i;
				cyan();
				cout<<"\n => Assign New Price : ";
				white();
				// invalid
				if(i<1 || i>8){
					system("cls");
					xy(4,4);
					red();
					cout<<'\a';
					cout<<"INVALID ENTRY.........";
					white();
					xy(4,6);
					system("pause");
					system("cls");	
					goto cfp;					
				}
				else{
					cin>>price[i-1];
				}
			}				
			////////  Return to main menu			
			else if(ch == "4"){
				system("cls");
				return 1;
			}		
			////////  Exit
			else if(ch == "5"){
				Insertion_in_File();
				exit(0);
			}
			////////  Invalid
			else{
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");	
				return 1;
			}
			system("cls");
			return 1;			
		}
		
		// INTERNATIONAL OVER-WRITE FILE DATA
		void Overwrite_Enter_data(){
			////////  OVERWRITE OR ENTER DATA
				system("cls");
				A->air_detail();
				// inserting data in arrays
				fstream file;
				xy(8,7);
				cout<<"| o Enter Available Country Names : "<<endl;
				z=9;
				y=1;
				for(int i=0; i<4 ;i++){
					xy(y,z);
					cyan();
					cout<<i+1<<" => ";
					white();
					cin>>country[i];
					y+=20;
				}		
				system("cls");	
				A->air_detail();
				xy(8,7);
				cout<<"| o Enter Two Available cities For Each Country : \n";
				z=9;
				for(int i=0 ; i<4 ; i++){
					xy(8,z);
					z+=2;
					cout<<"| o For Country "<<country[i]<<"' :\n";
					xy(1,z);
					z+=2;
					cyan();
					cout<<" => ";
					white();
					cin>>city[(i*2)];
					cyan();
					xy(1,z);
					z+=2;
					cout<<" => ";
					white();
					cin>>city[(i*2)+1];
				}
				//  SEATS WILL BE FIXED TO 30
				for(int i=0 ; i<4 ; i++){
					d_seats[i] = "30";
				}				
				system("cls");	
				A->air_detail();
				xy(8,7);
				cout<<"| o Enter Dates For Each Flight :";
				z=9;
				for(int i=0 ; i<4 ; i++){
					xy(8,z);
					z+=2;
					cout<<"| o For Flight "<<country[i]<<"/"<<city[i*2]<<"\n";
					xy(1,z);
					z+=2;
					cyan();
					cout<<" => ";
					white();
					cin>>date[(i*2)];
					xy(8,z);
					z+=2;
					cout<<"| o For Flight "<<country[i]<<"/"<<city[(i*2)+1]<<"\n";
					xy(1,z);
					z+=2;
					cyan();
					cout<<" => ";
					white();
					cin>>date[(i*2)+1];
				}
				system("cls");	
				A->air_detail();
				xy(8,7);
				cout<<"| o Enter Prices For Each Flight :";
				z=9;
				for(int i=0 ; i<4 ; i++){
					xy(8,z);
					z+=2;
					cout<<"| o For Flight "<<country[i]<<"/"<<city[i*2]<<"\n";
					xy(1,z);
					z+=2;
					cyan();
					cout<<" => ";
					white();
					cin>>price[(i*2)];
					xy(8,z);
					z+=2;
					cout<<"| o For Flight "<<country[i]<<"/"<<city[(i*2)+1]<<"\n";
					xy(1,z);
					z+=2;
					cyan();
					cout<<" => ";
					white();
					cin>>price[(i*2)+1];
				}			
			system("cls");
		}		

		// INTERNATIONAL READING EXISTING DATA 
		int Existing_Data(){
				system("cls");
				A->air_detail();
				cyan();
				xy(8,7);
				cout<<"  o Country/city";
				xy(33,7);
				cout<<" o Date";
				xy(48,7);
				cout<<"o Available Seats";
				xy(70,7);
				cout<<"o Price";
				xy(6,8);
				cout<<"";
				cout<<"_";
				white();
				z=10;
				for(int i=0 ; i<4 ; i++){
					xy(8,z);
					cout<<"| o "<<country[i]<<"/"<<city[i*2];
					xy(34,z);
					cout<<date[i*2];
					xy(55,z);
					cout<<seats[i*2];
					xy(70,z);
					cout<<price[i*2];
					z+=2;
					xy(8,z);
					cout<<"| o "<<country[i]<<"/"<<city[(i*2)+1];
					xy(34,z);
					cout<<date[(i*2)+1];
					xy(55,z);
					cout<<seats[(i*2)+1];
					xy(70,z);
					cout<<price[(i*2)+1];
					z+=2;
				}
				xy(6,z-1);
				cyan();
				cout<<"";
				cout<<"_";
				white();
			xy(8,27);
			cout<<"\t| o ";
			system("pause");
			system("cls");	
			return 1;			
		}
					
		// INTERNATIONALMENU OF ADMIN
		int admin_menu(){
adminmenu:
			system("cls");
			A->air_detail();
			string ch;
			xy(8,7);
			cout<<"| 1) Update Data.";
			xy(8,9);
			cout<<"| 2) Over-write/Enter Data.";
			xy(8,11);
			cout<<"| 3) View Existing Data.";
			xy(8,13);
			cout<<"| 4) Return to Previous Menu.";
			xy(8,15);
			cout<<"| 6) Exit.";
			xy(1,17);	
			cyan();
			cout<<"=> ENTER YOUR CHOICE : ";
			white();
			cin>>ch;
			if(ch == "1"){
				Update_Data();
				goto adminmenu;
			}
			else if(ch == "2"){
				Overwrite_Enter_data();
				goto adminmenu;
			}
			else if(ch == "3"){
				Existing_Data();	
				goto adminmenu;
			}
			else if(ch == "4"){
				system("cls");
				return 1;
			}
			else if(ch == "5"){
				Insertion_in_File();
				exit(0);
			}
			else{
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");
				goto adminmenu;
			}	
		}
							
		// DOMESTIC UPDATE FILE DATA
		int D_Update_Data(){
			system("cls");
			A->air_detail();
			xy(8,7);
			cout<<"| 1) Change Flights Destination.";
			xy(8,9);
			cout<<"| 2) Change Flights Date.";
			xy(8,11);
			cout<<"| 3) Change Flights Prices.";
			xy(8,13);
			cout<<"| 4) Return to Previous Menu.";
			xy(8,15);
			cout<<"| 5) Exit.";
			xy(1,17);
			cyan();
			cout<<"=> ENTER YOUR CHOICE : ";
			white();
			cin>>ch;
			
			////////  Change flight destination
cfde:
			if(ch == "1"){
				system("cls");
				A->air_detail();
				z=7;
				for(int j=0 ; j<4 ; j++){
					xy(8,z);
					cout<<j+1<<") "<<d_city[j];
					z+=2;
				}
				xy(1,17);
				cyan();
				cout<<" => Choose which Flight's Destination you want to change : ";
				white();
				cin>>i;
				if(i>0 && i<5){
					xy(1,19);
					cyan();					
					cout<<" => Enter Country Name : ";
					white();
					cin>>d_city[i-1];
				}
				else{
					system("cls");
					xy(4,4);
					red();
					cout<<'\a';
					cout<<"INVALID ENTRY.........";
					white();
					xy(4,6);
					system("pause");
					system("cls");	
					goto cfde;
				}
			}		
			////////  Change flight dates
			else if(ch == "2"){
cfda:
				system("cls");
				A->air_detail();
				cyan();
				xy(8,7);
				cout<<"Sr   City";
				xy(7,8);
				cout<<"";
				white();
				z = 10;
				for(int j=0 ; j<4 ; j++){
					xy(8,z);
					cout<<(j*2)+1<<")  "<<d_city[j];
					z+=2;
				}
				cyan();
				cout<<"\n\n => Choose which Flight's Date you want to change : ";
				white();
				cin>>i;
				cyan();
				cout<<"\n => Assign New Date (M/D/Y) : ";
				white();
				// Invalid
				if(i<1 || i>8){
					system("cls");
					xy(4,4);
					red();
					cout<<'\a';
					cout<<"INVALID ENTRY.........";
					white();
					xy(4,6);
					system("pause");
					system("cls");	
					goto cfda;					
				}
				else{
					cin>>d_date[i-1];
				}				
			}		
			////////  Change flight Prices
			else if(ch == "3"){
cfp:
				system("cls");
				A->air_detail();
				cyan();
				xy(8,7);
				cout<<"o Sr   o City";
				xy(7,8);
				cout<<"";
				white();
				z = 10;				
				for(int j=0 ; j<4 ; j++){
					xy(8,z);
					cout<<(j*2)+1<<")   "<<city[j*2];
					z+=2;
				}
				cyan();
				cout<<"\n\n => Choose which Flight's Price you want to change : ";
				white();
				cin>>i;
				cyan();
				cout<<"\n => Assign New Price : ";
				white();
				// invalid
				if(i<1 || i>8){
					system("cls");
					xy(4,4);
					red();
					cout<<'\a';
					cout<<"INVALID ENTRY.........";
					white();
					xy(4,6);
					system("pause");
					system("cls");	
					goto cfp;					
				}
				else{
					cin>>d_price[i-1];
				}
			}				
			////////  Return to main menu			
			else if(ch == "4"){
				system("cls");
				return 1;
			}		
			////////  Exit
			else if(ch == "5"){
				Insertion_in_File();
				exit(0);
			}
			////////  Exit
			else{
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");	
				return 1;
			}
			system("cls");
			return 1;			
		}
		
		// DOMESTIC OVER-WRITE FILE DATA
		void D_Overwrite_Enter_data(){
			////////  OVERWRITE OR ENTER DATA
				system("cls");
				A->air_detail();
				// inserting data in arrays
				fstream file;
				xy(8,7);
				cout<<"| o Enter Available 'Pakistan' City Names : "<<endl;
				z=9;
				y=1;
				for(int i=0; i<4 ;i++){
					xy(y,z);
					cyan();
					cout<<i+1<<" => ";
					white();
					cin>>d_city[i];
					y+=20;
				}		
				//  SEATS WILL BE FIXED TO 30
				for(int i=0 ; i<4 ; i++){
					d_seats[i] = "30";
				}
				system("cls");	
				A->air_detail();
				xy(8,7);
				cout<<"| o Enter Dates For Each Flight :";
				z=9;
				for(int i=0 ; i<4 ; i++){
					xy(8,z);
					z+=2;
					cout<<"| o For Flight "<<d_city[i];
					xy(1,z);
					z+=2;
					cyan();
					cout<<" => ";
					white();
					cin>>d_date[i];
				}
				system("cls");	
				A->air_detail();
				xy(8,7);
				cout<<"| o Enter Prices For Each Flight :";
				z=9;
				for(int i=0 ; i<4 ; i++){
					xy(8,z);
					z+=2;
					cout<<"| o For Flight "<<d_city[i];
					xy(1,z);
					z+=2;
					cyan();
					cout<<" => ";
					white();
					cin>>d_price[i];
				}			
			system("cls");
		}		
	
		// DOMESTIC READING EXISTING DATA 
		int D_Existing_Data(){
				system("cls");
				A->air_detail();
				cyan();
				xy(8,7);
				cout<<"    o City";
				xy(28,7);
				cout<<" o Date";
				xy(42,7);
				cout<<"o Available Seats";
				xy(64,7);
				cout<<"o Price";
				xy(6,8);
				cout<<"";
				cout<<"";
				white();
				z=10;
				for(int i=0 ; i<4 ; i++){
					xy(8,z);
					cout<<"| o "<<d_city[i];
					xy(28,z);
					cout<<d_date[i];
					xy(50,z);
					cout<<d_seats[i];
					xy(65,z);
					cout<<d_price[i];
					z+=2;
				}
				xy(6,z-1);
				cyan();
				cout<<"";
				cout<<"";
				white();
			xy(8,19);
			cout<<"\t| o ";
			system("pause");
			system("cls");	
			return 1;			
		}
			
		// DOMESTIC MENU OF ADMIN
		int D_admin_menu(){
adminmenu:
			system("cls");
			A->air_detail();
			string ch;
			xy(8,7);
			cout<<"| 1) Update Data.";
			xy(8,9);
			cout<<"| 2) Over-write/Enter Data.";
			xy(8,11);
			cout<<"| 3) View Existing Data.";
			xy(8,13);
			cout<<"| 4) Return to Previous Menu.";
			xy(8,15);
			cout<<"| 5) Exit.";
			xy(1,17);	
			cyan();
			cout<<"=> ENTER YOUR CHOICE : ";
			white();
			cin>>ch;
			if(ch == "1"){
				D_Update_Data();
				goto adminmenu;
			}
			else if(ch == "2"){
				D_Overwrite_Enter_data();
				goto adminmenu;
			}
			else if(ch == "3"){
				D_Existing_Data();	
				goto adminmenu;
			}
			else if(ch == "4"){
				system("cls");
				return 1;
			}
			else if(ch == "5"){
				Insertion_in_File();
				exit(0);
			}
			else{
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");
				goto adminmenu;
			}	
		}
			
		// VIEW TICKETS BY LINK LIST
		void View_Tickets(){
			LinkedList l;
			string word,
				   data,
				   ch, 
				   Pnr,
				   Name,
				   Age,
				   Number,
				   Cnic,
		     	   Seat_No,
				   Departure,
		     	   Destination,
			       Price;
			       
			fstream file;
			file.open("Tickets.txt", ios::in);
			while(file>>word>>Pnr>>word>>Name>>word>>Age>>word>>Number>>word>>Cnic>>
				  word>>Seat_No>>word>>Departure>>word>>Destination>>word>>Price){
				l.insertAtStart(Pnr, Name, Age, Number, Cnic, Seat_No, Departure,
								Destination, Price);
			}
			file.close();
list:	
			system("cls");
			A->air_detail();
			xy(8,7);
			cout<<"| 1) Display Tickets.";
			xy(8,9);
			cout<<"| 2) Search Ticket.";
			xy(8,11);
			cout<<"| 3) Delete Ticket.";
			xy(8,13);
			cout<<"| 4) Return To Previous Menu.";
			xy(8,15);
			cout<<"| 5) Exit.";	
			xy(1,17);
			cyan();
			cout<<" => Enter Your Choice : ";
			white();
			cin>>ch;	
			// Add
			if(ch == "1"){	
				A->air_detail();
				system("cls");
				l.display();
				cout<<"\n\n\t\t o | ";
				system("pause");
				system("cls");	
				goto list;	
			}
					
			// Delete
			else if(ch == "2"){
				cout<<"\n => Enter PNR to Search : ";
				cin>>data;
				system("cls");	
				l.search(data);
				cout<<"\n\n\t\to | ";
				system("pause");
				system("cls");	
				goto list;	
			}	
			// Search
			else if(ch == "3"){	
				cout<<"\n => Enter PNR to Delete : ";
				cin>>data;
				system("cls");	
				l.deleteByData(data);
				cout<<"\n\n\t\to | ";
				system("pause");
				system("cls");	
				goto list;	
			}
			// Display
			else if(ch == "4"){
				admin_mainmenu();
			}
			// Exit
			else if(ch == "5"){
				exit(0);
			}		
			// Invalid
			else{
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';			
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");	
				goto list;		
			}			
		}

		// MAIN-MENU OF ADMIN
		int admin_mainmenu(){
adminmainmenu:
			system("cls");
			A->air_detail();
			string ch;
			xy(8,7);
			cout<<"| 1) International Flights Data.";
			xy(8,9);
			cout<<"| 2) Domestic Flights Data.";
			xy(8,11);
			cout<<"| 3) View All Tickets.";
			xy(8,13);
			cout<<"| 4) Log-out.";
			xy(8,15);
			cout<<"| 5) Exit.";
			xy(8,17);	
			cyan();
			cout<<"=> ENTER YOUR CHOICE : ";
			white();
			cin>>ch;
			
			if(ch == "1"){
				admin_menu();
				goto adminmainmenu;
			}	
			else if(ch == "2"){
				D_admin_menu();
				goto adminmainmenu;
			}
			else if(ch == "3"){
				View_Tickets();
				return 1;				
			}	
			else if(ch == "4"){
				Insertion_in_File();
				return 1;				
			}	
			else if(ch == "5"){
				Insertion_in_File();
				exit(0);
			}
			else{
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");
				goto adminmainmenu;				
			}
			return 1;
		}
};

/////////////////////////////////////////////////////	CLASS INTERNATIONALFLIGHT  //////////////////////////////////////////////
class InternationalFlight{
	private :
		Airline *A;
	public :
		void flight_menu(Admin &obj){
			A->air_detail();
			xy(8,7);
			cout << "|  o AVAILABLE COUNTRY" ;
			xy(8,9);
			cout<<"| 1) "<<obj.country[0];
			xy(8,11);
			cout<<"| 2) "<<obj.country[1];
			xy(8,13);
			cout<<"| 3) "<<obj.country[2];
			xy(8,15);
			cout<<"| 4) "<<obj.country[3];
		}
};

/////////////////////////////////////////////////////	CLASS DOMESITCFLIGHT  ///////////////////////////////////////////////////
class DomesticFlight {
	private :
		Airline *A;
	public :
		void flight_menu(Admin &obj){
			A->air_detail();
			xy(8,7);
			cout<<"| o   AVAILABLE CITY ";
			xy(8,9);
			cout<<"| o "<<obj.d_city[0];
			xy(8,11);
			cout<<"| o "<<obj.d_city[1];
			xy(8,13);
			cout<<"| o "<<obj.d_city[2];
			xy(8,15);
			cout<<"| o "<<obj.d_city[3];
			xy(8,17);
			cout<<"| 1) Proceed.";
			xy(8,19);
			cout<<"| 2) Return to Previous Menu.";
			xy(8,21);
			cout<<"| 3) Exit.";
		}
};

//===================================================	MAIN FUNCTION	 ========================================================
int main(){
	
	// VARIABLES
	int num, 
		country, 
		ticket, 
		pnr, 
		seat_no,
		confirmation = 0;
	string choice,
		   subchoice,
		   username, 
		   pass, 
		   confirm_pass, 
		   save, 
		   existing;
	
	// CLASSE OBJECTS	
	Airline air;
	Passenger *pas = new Passenger(); 
	Ticket tic;
	Flight fli;
	Admin a;
	InternationalFlight inter;
	DomesticFlight dom;
mmenu:
	system("cls");
	air.air_detail();
	air.main_menu();
	xy(1,13);	
	cyan();
	cout<<"=> ENTER YOUR CHOICE : ";
	white();
	cin>>choice;
// MAIN IF 1
	if(choice == "1"){
		if(!a.Admin_acc()){
			goto mmenu;
		}
		a.admin_mainmenu();
		goto mmenu;
	}	
// MAIN ELSE IF 2
	else if(choice == "2"){		
start:
		system("cls");
		air.air_detail();
		air.menu();
		xy(1,15);	
		cyan();
		cout<<"=> ENTER YOUR CHOICE : ";
		white();
		cin>>choice;
		system("cls");
		// SIGN UP
		if(choice=="1"){
signup:
			air.air_detail();
			cyan();
			xy(8,7);
			cout<<"| o Create New Username : ";
			xy(8,9);
			cout<<"| o Create New Password : ";
			xy(8,11);
			cout<<"| o Confirm Password : ";
			white();
			xy(35,7);
			cin>>username;
			xy(35,9);
			cin>>pass;
			xy(32,11);
			cin>>confirm_pass;
			system("cls");
			// PASSWORD RE-TYPE CONFIRMATION
			if(pass!=confirm_pass){
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"| o PASSWORD DOESNOT MATCH.";
				white();
				xy(4,6);
				system("pause");
				system("cls");
				goto signup;
			}
			if(5 > username.length() || 5 > pass.length()){
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"| o USERNAME & PASSWORD SHOULD CONSIST ATLEAST 5 CHARACTERS.";
				white();
				xy(4,6);
				system("pause");
				system("cls");
				goto signup;				
			}
			confirmation = air.authentication(1, username, pass);
			if(confirmation == -1){
				system("cls");
				goto signup;
			}
		}
		// LOGIN 
		else if(choice=="2"){ 
			air.air_detail();
			xy(8,7);
			cyan();
			cout<<"| o Enter Username : ";
			xy(8,9);
			cout<<"| o Enter Password : ";
			white();
			xy(29,7);
			cin>>username;
			xy(29,9);
			cin>>pass;
			confirmation = air.authentication(2, username, pass);
			system("cls");
			// PASSWORD CONFIRMATION			
			if(confirmation!=1){
				goto start;
			}
		}
		// RETURN TO MAIN-MENU
		else if(choice=="3"){
			goto mmenu;
		}
		// EXIT
		else if(choice=="4"){
			exit(0);
		}
		// INVALID
		else{
			system("cls");
			xy(4,4);
			red();
			cout<<'\a';
			cout<<"INVALID ENTRY.........";
			white();
			xy(4,6);
			system("pause");
			system("cls");
			goto start;
		}
		
		//LOGGED IN PASSENGER MENU
mainmenu:
		system("cls");
		pas->passenger_menu();
		xy(1,15);
		cyan();
		cout<<"=> ENTER YOUR CHOICE : ";
		white();
		cin>>choice;
		system("cls");
		// FLIGHT DETAILS
		if(choice=="1"){
			pas->get_passenger_details();
			xy(4,15);
			cout<<"| o ";
			system("pause");
			system("cls");	
			xy(4,17);
			pas->display_passenger_details();
			xy(4,18);
			system("cls");
		}
		// CHECK EXISTING TICKETS
		else if(choice=="2"){	
			air.air_detail();
			xy(8,7);
			cout<<"| o SEARCH EXISTING TICKET : ";
			xy(8,9);
			cyan();
			cout<<"| o Enter Your Ticket PNR : ";
			white();
			cin>>existing;
			tic.check_existing_ticket(existing);
		    goto mainmenu;
		}
		// LOG-OUT
		else if(choice=="3"){
			goto start;
		}
		// EXIT
		else if(choice=="4"){
			exit(0);
		} 
		// INVALID
		else{
			system("cls");
			xy(4,4);
			red();
			cout<<'\a';
			cout<<"INVALID ENTRY.........";
			white();
			xy(4,6);
			system("pause");
			system("cls");
			goto mainmenu;
		}
		// GENERATING PNR
gen_pnr:
		pnr=tic.generating_ticket();
		xy(1,15);
		cyan();
		cout<<"=> ENTER YOUR CHOICE : ";
		white();
		cin>>choice;
		system("cls");		
		// PROCEED TICKET FURTHER 
		if(choice=="1"){
domestic_inter:
			fli.flight_menu();
			xy(1,15);
			cyan();
			cout<<"=> ENTER YOUR CHOICE : "; 
			white();
			cin>>choice;
			system("cls");
		}		
		// CANCEL TICKET PROCESS
		else if(choice=="2"){
			delete pas;
			goto mainmenu;
		}		
		// EXIT
		else if(choice=="3"){
			exit(0);
		}
		// INVALID
		else{
			system("cls");
			xy(4,4);
			red();
			cout<<'\a';
			cout<<"INVALID ENTRY.........";
			white();
			xy(4,6);
			system("pause");
			system("cls");
			goto gen_pnr;
		}																						
flightmenu:	
		// INTERNATIONAL FLIGHTS
		if(choice=="1"){
			inter.flight_menu(a);
			xy(8,19);
			cyan();
			cout<<"=> ENTER YOUR CHOICE : ";
			white();
			cin>>country;			
			// INTEGER VALUE & AND FUNCTION TO HANDLE STRING
			while (cin.fail()){
		        cin.clear();
		        cin.ignore(256,'\n');
		        system("cls");
		        red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
		    	white();
		    	cout<<"\n\n\t | o ";
		    	system("pause");
		    	system("cls");
		   	    goto flightmenu;
		  	}
			country--;
			system("cls");
			// COUNTRY INVALID
			if(country<0 || country>3){
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");
				goto flightmenu;
			}
			// DISPLAYING INTERNATIONAL FLIGHTS
DIF:
			num=1;
			air.air_detail();
			xy(5,7);
			cyan();
			cout<<"";
			xy(7,8);
			cout<<"o Sr-No";
			xy(20,8);
			cout<<"o Destination";
			xy(45,8);
			cout<<"o Date  ";
			xy(58,8);
			cout<<"o Available Seats";
			xy(80,8);
			cout<<"o Price";
			xy(5,9);
			cout<<"";
			// 1ST FLIGHT DETAILS
			xy(10,11);
			white();
			cout<<num<<")";
			xy(19,11);
			cout<<a.country[country]<<" / "<<a.city[country*2];
			xy(45,11);
			cout<<a.date[country*2];
			xy(65,11);
			cout<<a.seats[country*2];	
			xy(80,11);
			cout<<a.price[country*2];
			// 2ND FLIGHT DETAILS
			xy(10,13);
			cout<<num+1<<")";
			xy(19,13);
			cout<<a.country[country]<<" / "<<a.city[(country*2)+1];
			xy(45,13);
			cout<<a.date[(country*2)+1];
			xy(65,13);
			cout<<a.seats[(country*2)+1];	
			xy(80,13);
			cout<<a.price[(country*2)+1];
			xy(8,16);
			cyan();
			cout<<" => ENTER & BOOK YOUR TICKET : ";
			white();
			cin>>ticket;
			// INTEGER VALUE & AND FUNCTION TO HANDLE STRING
			while (cin.fail()){
		        cin.clear();
		        cin.ignore(256,'\n');
		        system("cls");
		        red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
		    	white();
		    	cout<<"\n\n\t | o ";
		    	system("pause");
		    	system("cls");
		   	    goto DIF;
		  	}			
			// INVALID TICKET OPTION
			if(ticket<1 || ticket>2){
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");
				goto flightmenu;
			}
		}
		// DOMESTIC FLIGHTS MENU
		else if(choice=="2"){ 
				dom.flight_menu(a);
				xy(8,21);
				cyan();
				cout<<"=> ENTER YOUR CHOICE : ";
				white();
				cin>>subchoice;
				country--;
				system("cls");	
			// DISPLAYING FLIGHTS
			if(subchoice=="1"){
DDF:			
				system("cls");
				num=1;
				air.air_detail();
				xy(5,7);
				cyan();
				cout<<"";
				xy(7,8);
				cout<<"o Sr No";
				xy(16,8);
				cout<<"o Destination";
				xy(33,8);
				cout<<"o Date";
				xy(60,8);
				cout<<"o Available Seats";
				xy(80,8);
				cout<<"o Price";
				xy(6,9);
				cout<<"";
				white();
				int z = 11;
				// DISPLAYING FOUR DOMESTIC FLIGHTS
				for(int i=0 ; i<4 ; i++){
					xy(11,z);
					cout<<num<<")";
					xy(16,z);
					cout<<a.d_city[i];
					xy(30,z);
					cout<<a.d_date[i];
					xy(58,z);
					cout<<a.d_seats[i];
					xy(77,z);
					cout<<a.d_price[i];
					z+=2;
				}
				xy(1,z);
				cyan();
				cout<<" => ENTER & BOOK YOUR TICKET : ";
				white();
				cin>>ticket;
				// INTEGER VALUE & AND FUNCTION TO HANDLE STRING
				while (cin.fail()){
			        cin.clear();
			        cin.ignore(256,'\n');
			        system("cls");
			        red();
					cout<<'\a';
					cout<<"INVALID ENTRY.........";
			    	white();
			    	cout<<"\n\n\t | o ";
			    	system("pause");
			    	system("cls");
			   	    goto DDF;
			  	}
				// INVALID TICKET OPTION
				if(ticket<1 || ticket>4){
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");
				goto flightmenu;
				}	
			}
			// INVALID OPTION
			else{
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");	
				goto flightmenu;
			}
		}
		// EXIT
		else if(choice=="3"){
			exit(0);
		}
		// INVALID
		else{
			system("cls");
			xy(4,4);
			red();
			cout<<'\a';
			cout<<"INVALID ENTRY.........";
			white();
			xy(4,6);
			system("pause");
			system("cls");
			goto domestic_inter;
		}		
		// NO SEATS AVAILABLE
		if(false){
seatsissue:
			system("cls");
			air.air_detail();
			xy(8,7);
			cyan();
			cout<<"| o --> All Seats Reserved.";
			white();
			xy(8,9);
			cout<<"| 1) Check Other Flights.";
			xy(8,11);
			cout<<"| 2) Return to Main Menu.";
			xy(8,13);
			cout<<"| 3) Exit.";			
			xy(1,15);
			cyan();
			cout<<" => Enter Your Choice : ";
			white();
			cin>>choice;
			if(choice == "1"){
				goto domestic_inter;		
			}	
			else if(choice == "2"){
				goto mainmenu;
			}
			else if(choice == "3"){
				exit(0);
			}
			else{
				system("cls");
				xy(4,4);
				red();
				cout<<'\a';
				cout<<"INVALID ENTRY.........";
				white();
				xy(4,6);
				system("pause");
				system("cls");
				goto seatsissue;				
			}		
		}
		//	INTERNATIONAL TICKET 					
		if(ticket==1 && subchoice!="1" && subchoice!="2"){
			int temp = stoi(a.seats[country*2]);
			// NOT ENOUGH SEATS
			if(temp < 1){
				goto seatsissue;								
			}
			a.seats[(country*2)] = to_string(temp - 1);
			system("pause");
			system("cls");
			seat_no = 31 - temp;
			// SAVING TICKET IN FILE
			fstream file;
			file.open("Tickets.txt",ios::app);
			file<<endl<<endl<<"PNR "<<pnr<<endl;
			file.close();
			pas->save_passenger_details();
			file.open("Tickets.txt",ios::app);
			file<<"Seat-No "<<seat_no<<endl;
			file<<"Departure "<<a.d_time<<endl;
			file<<"Destination "<<a.country[country*2];
			file<<"/"<<a.city[country*2]<<endl;
			file<<"Price "<<a.price[country*2];
		    file.close();  	
		}
		else if(ticket==2 && subchoice!="1" && subchoice!="2"){
			int temp = stoi(a.seats[(country*2)+1]);
			// NOT ENOUGH SEATS
			if(temp < 1){
				goto seatsissue;								
			}
			a.seats[(country*2)+1] = to_string(temp - 1);
			system("cls");
			cout<<"SUCESSFULLY SOTRED IN FILE";
			system("pause");
			system("cls");
			seat_no = 31 - temp;
			// SAVING TICKET IN FILE
			fstream file;
			file.open("Tickets.txt",ios::app);
			file<<endl<<endl<<"PNR "<<pnr<<endl;
			file.close();
			pas->save_passenger_details();
			file.open("Tickets.txt",ios::app);
			file<<"Seat-No "<<seat_no<<endl;
			file<<"Departure "<<Admin().d_time<<endl;
			file<<"Destination "<<a.country[(country*2)+1];
			file<<"/"<<a.city[(country*2)+1]<<endl;
			file<<"Price  "<<a.price[country*2];
		    file.close();
		}
	
		//	DOMESTIC TICKET SAVING IN FILE					
		else if(subchoice=="1"){
			int temp = stoi(a.d_seats[ticket-1]);
			// NOT ENOUGH SEATS
			if(temp < 1){
				goto seatsissue;								
			}
			a.d_seats[ticket-1] = to_string(temp - 1);
			seat_no = 31 - temp;
			// SAVING TICKET IN FILE
			fstream file;
			file.open("Tickets.txt",ios::app);
			file<<endl<<endl<<"PNR "<<pnr<<endl;
			file.close();
			pas->save_passenger_details();
			file.open("Tickets.txt",ios::app);
			file<<"Seat-No "<<seat_no<<endl;
			file<<"Departure  "<<a.d_time<<endl;
			file<<"Destination  Pakistan/"<<a.d_city[ticket-1]<<endl;
			file<<"Price  "<<a.d_price[ticket-1];
		    file.close();
		}
		// STORING IN FILE TO CHANGE AVAILABLE SEATS
		a.Insertion_in_File();
		
		system("cls");
		air.air_detail();
		xy(8,7);
		orange();
		cout<<"| o Generating Your Ticket.";
		for(int i=0 ; i<5 ; i++){
			Sleep(1);
			cout<<".";		
		}
		xy(8,9);
		cout<<"| o Successfully Generated....";
		white();
		xy(8,11);
		system("pause");	
end:
		system("cls");
		air.air_detail();
		xy(8,7);
		cout<<"| 1) Return To Main Menu.";
		xy(8,9);
		cout<<"| 2) Exit.";
		xy(8,12);
		cyan();
		cout<<"=> ENTER YOUR CHOICE : ";	
		white();
		cin>>choice;
		system("cls");
		// RETURN TO MAIN MENU (LAST)			
		if(choice=="1"){
			goto mainmenu;
		}	
		// EXIT (LAST)
		else if(choice=="2"){
				exit(0);
		}
		// INVALID (LAST)
		else{
			system("cls");
			xy(4,4);
			red();
			cout<<'\a';
			cout<<"INVALID ENTRY.........";
			white();
			xy(4,6);
			system("pause");
			system("cls");
			goto end;	
		}
	}
// MAIN ELSE IF 3
	else if(choice == "3"){
		exit(0);
	}
// MAIN ELSE 4
	else{
		system("cls");
		xy(4,4);
		red();
		cout<<'\a';
		cout<<"INVALID ENTRY.........";
		white();
		xy(4,6);
		system("pause");
		system("cls");
		goto mmenu;
	}
}