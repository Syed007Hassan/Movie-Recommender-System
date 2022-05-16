#include<iostream>
#include<stdlib.h>
#include<string>
#include <fstream>
#include<stack>
#include<queue>
#include<conio.h>
#include<windows.h>
using namespace std;

class Node{
	
	public:
		string userid;
		string name;
		string id;
		string rating;
		string genre;
		string year;
		string dur;
		string imdb;
		string d_name;
		string description;
		int height;
		Node *left;
		Node *right;
	
	
	Node(string a,string b,string c,string d,string e, string f, string g, string h, string i, string j){
		userid = a;
		name = b;
		id = c;
		rating =d;
		genre= e;
		year=f;
		dur=g;
		imdb=h;
		d_name=i;
		description=j;
		left = right = 0;
		
	}
	
};

class Movies{
	
	Node *root;
	
	public:
		
		Movies(){
			root = 0;
		}
   
   //Inserting in AVL like BST
   
   //Returns the height of the tree
		int heightFinder(Node *n){
			if(n == 0)
			return 0;
	
			return n->height;
		}
  
  //Returns max of two heights given 
		int max(int a, int b){    
			return (a > b)? a : b;
		}

   //Checks whether left-sub tree is heavier or right one 
		int checkBalance(Node *r){
			if(r == 0){
				return 0;
			}
			else{
				return ( heightFinder(r->left) - heightFinder(r->right) );
			}
		}
   
   //Insertion starts from here
    	void insert(string a,string b,string c,string d,string e, string f, string g, string h, string i, string j) {
    		//	cout << "d";
        	root = insert(a,b,c,d,e,f,g,h,i,j, root);
    	}

		Node *insert(string a,string b,string c,string d,string e,string f, string g, string h, string i, string j, Node *r){
   	
			if( r == 0){
				r = new Node(a,b,c,d,e,f,g,h,i,j);
				r->height = 1;
			}
			else if(c < r->id){
				r->left = insert(a,b,c,d,e,f,g,h,i,j,r->left);
			}
			else if(c > r->id){
				r->right = insert(a,b,c,d,e,f,g,h,i,j,r->right);
			}
			else{
				return r;  
			}
    
			r->height = 1 + max(heightFinder(r->left),heightFinder(r->right));   //updating height of ancestor
	
			int balancing_Factor = checkBalance(r);  //checking balancing factor
    
    		// Right rotation to be performed as nodes alligned to the left
    		if (balancing_Factor > 1 && c < r->left->id){
				return RightRotation(r);
			}
		
     		// Left rotation to be performed as nodes alligned to the right
    		if (balancing_Factor < -1 && c > r->right->id){
        		return LeftRotation(r);
			}
 
    		// LR ROTATION
    		if (balancing_Factor > 1 && c > r->left->id){
				r->left = LeftRotation(r->left);
        		return RightRotation(r);
			}
 
    		//  RL ROTATION
    		if (balancing_Factor < -1 && c < r->right->id){
	    		r->right = RightRotation(r->right);
        		return LeftRotation(r);	
			}

    		return r;
		}
   
		Node *RightRotation(Node *y){
			Node *x = y->left;      
			Node *z = x->right;        
	                        
			x->right = y;
			y->left = z; 
	
    		y->height = max(heightFinder(y->left) , heightFinder(y->right)) + 1;
    		x->height = max(heightFinder(x->left) , heightFinder(x->right)) + 1;

    		return x;
		}
 

		Node *LeftRotation(Node *x){
			Node *y = x->right; 
			Node *z = y->left;  
 	                
			y->left = x;
			x->right = z;
	
    		x->height = max(heightFinder(x->left) , heightFinder(x->right)) + 1;
    		y->height = max(heightFinder(y->left) , heightFinder(y->right)) + 1;

    		return y;
		} 

    	//Returns the min left node
    	Node *min(Node *r){
			if(r == 0){
				return 0;
			}
			else if(r->left == 0){
				return r;
			}
			else{
				return min(r->left);
			}	
		}

		//Deletion like BST then update height for balancing the tree
    	void deleteByMovieID(string val){
			root = removebyID(val,root);
			
		}
   		
   		// This module deletes the movie w.r.t its ID.
		Node *removebyID(string val,Node *r){
			Node *temp;
			if(r == 0){
				return 0;
			}
			else if(val < r->id){
				r->left = removebyID(val,r->left);
			}
			else if(val > r->id){
				r->right = removebyID(val,r->right);
			}
			else if(r->left && r->right){
				temp = min(r->right);
				r->id = temp->id;
				r->right = removebyID(r->id, r->right);
			}
			else{
				cout<<"\n\n\t\t\t\t\tMovie has been deleted "<<endl;
				temp = r;
				r->height = 1 + max(heightFinder(r->left),heightFinder(r->right));
				if(r->right == 0){
					r = r->right;
				}
				else if(r->left == 0){
					r = r->left;
				}
		
				delete temp;
			}
	

    		int balancing_Factor = checkBalance(r);
			// Right rotation to be performed as nodes alligned to the left
    		if (balancing_Factor > 1 && checkBalance(r->left) >= 0){
        		return RightRotation(r);
			}
		
			// Left rotation to be performed as nodes alligned to the right
    		if (balancing_Factor < -1 && checkBalance(r->right) <= 0 ){
        		return LeftRotation(r);
			}
 
    		// LR ROTATION
    		if (balancing_Factor > 1 && checkBalance(r->left) < 0){
        		r->left = LeftRotation(r->left);
        		return RightRotation(r);
			}
 
    		//  RL ROTATION
    		if (balancing_Factor < -1 && checkBalance(r->right) > 0){
				r->right = RightRotation(r->right);
        		return LeftRotation(r);
			}

    		return r;
		}
		
		// This function checks whether the user is authorised by checking the password. It then deletes the movie.
		pass(string val) {
			int i=0;
    		char ch,st[21],ch1[21]={"janab"};
    		cout<<"\n\n\n\n\n\n\t\t\t\t Enter Password : ";
    		
    		while(1)
    		{
    			ch=getch();
    			if(ch==13)
    			{
        			st[i]='\0';
        			break;
    			}
    			else if(ch==8&&i>0)
    			{
        			i--;
        			cout<<"\b \b";
    			}
    			else
    			{
    				cout<<"*";
    				st[i]=ch;
    				i++;
    			}
    		}
    		ifstream inf("password.txt");
    		inf>>ch1;
    		inf.close();
    		for(i=0;st[i]==ch1[i]&&st[i]!='\0'&&ch1[i]!='\0';i++);
    		if(st[i]=='\0'&&ch1[i]=='\0')
    		{
        		system("cls");
        		deleteByMovieID(val);
    		}
    		else
    		{
        		cout<<"\n\n\t\tWrong Password.\n\n\t\ttry again.....\n";
        		getch();
        		system("cls");
        		pass(val);
    		}
    	}
    	
    	// This function checks whether the user is authorised by checking the password. It then deletes the movie.
    	passs() {
			int i=0;
    		char ch,st[21],ch1[21]={"janab"};
    		cout<<"\n\n\n\n\n\n\t\t\t\t Enter Password : ";
    		
    		while(1)
    		{
    			ch=getch();
    			if(ch==13)
    			{
        			st[i]='\0';
        			break;
    			}
    			else if(ch==8&&i>0)
    			{
        			i--;
        			cout<<"\b \b";
    			}
    			else
    			{
    				cout<<"*";
    				st[i]=ch;
    				i++;
    			}
    		}
    		ifstream inf("password.txt");
    		inf>>ch1;
    		inf.close();
    		for(i=0;st[i]==ch1[i]&&st[i]!='\0'&&ch1[i]!='\0';i++);
    		if(st[i]=='\0'&&ch1[i]=='\0')
    		{
        		system("cls");
        		string a,b,c,d,e,f,g,h,i,j;
        		cout << "\n\n\t\t\t\tEnter Details:\n";
        		cout<<"\t\t\t\tEnter the user id: ";
        		getline(cin,a);
        		cout<<"\n\t\t\t\tEnter the movie name: ";
        		getline(cin,b);
        		cout<<"\n\t\t\t\tEnter the unique movie id: ";
        		getline(cin,c);
        		cout<<"\n\t\t\t\tEnter the movie rating: ";
        		getline(cin,d);
        		cout<<"\n\t\t\t\tEnter the movie genre: ";
        		getline(cin,e);
        		cout<<"\n\t\t\t\tEnter the date of release (DD-MM-YY): ";
        		getline(cin,f);
        		cout<<"\n\t\t\t\tEnter the movie duration: ";
        		getline(cin,g);
        		cout<<"\n\t\t\t\tEnter the IMDB id: ";
        		getline(cin,h);
        		cout<<"\n\t\t\t\tEnter the d name: ";
        		getline(cin,i);
        		cout<<"\n\t\t\t\tEnter the description of movie: ";
        		getline(cin,j);
        		
        		
        		root = insert(a,b,c,d,e,f,g,h,i,j, root);
    		}
    		else
    		{
        		cout<<"\n\n\t\tWrong Password.\n\n\t\ttry again.....\n";
        		getch();
        		system("cls");
        		passs();
    		}
    	}
		
		//Search in BST 
   		
   		// search by the ID of the movie
		void searchById(string val){
			Node *temp = find(val,root);
   	 		
			if(temp==NULL) {
				cout<<"\t\t\t\t\tMovie is not there! "<<endl;
				getchar();
				system ("CLS");
				return;
			}
			if(temp->id == val){
				
				cout <<"\n\n\t\t\t\t\tMovie Details: \n\n";
				cout<<"\t\t\t\t\tID: "<<temp->id<<endl;
				cout<<"\t\t\t\t\tMOVIE NAME: "<<temp->name<<endl;
				cout<<"\t\t\t\t\tMOVIE RATING: "<<temp->rating<<endl;
				cout<<"\t\t\t\t\tMOVIE GENRE: "<<temp->genre<<endl;
				cout<< "\t\t\t\t\tDate: " <<  temp->year<<endl;
				cout<< "\t\t\t\t\tDuration: " << temp->dur <<endl;
				cout<< "\t\t\t\t\tIMDB: " << temp->imdb<<endl;
				cout<<"\t\t\t\t\tDirector Name:"<<temp->d_name<<endl;
				cout<<"\n\t\t\t\t\t\t:Overview:\n\n"<<temp->description<<endl<<endl;
			    getchar();
				system ("CLS");
			}
			else{
				cout<<"\t\t\t\t\tMovie is not there! "<<endl;
				getchar();
				system ("CLS");
			}	
		}
   
   		// search by the name of the movie
		void searchByname(string val){		
   	 
			stack<Node*> Stack;
			Node *temp=root;
			
			while(temp!=NULL || Stack.empty()==false) {
				while(temp!=NULL) {
					Stack.push(temp);
					temp=temp->left;
				}
				
				temp=Stack.top();
				Stack.pop();
				
				if(temp->name == val) {
					break;
				}
				temp=temp->right;
			}
   	 		
   	 		if(temp==NULL) {
   	 			cout<<"\n\n\t\t\t\t\tMovie is not present!/ "<<endl;
				getchar();
				system ("CLS");
				return;
			}
			if(temp->name == val){
				
				cout <<"\n\n\t\t\t\t\tMovie Details: \n\n";
				cout<<"\t\t\t\t\tID: "<<temp->id<<endl;
				cout<<"\t\t\t\t\tMOVIE NAME: "<<temp->name<<endl;
				cout<<"\t\t\t\t\tMOVIE RATING: "<<temp->rating<<endl;
				cout<<"\t\t\t\t\tMOVIE GENRE: "<<temp->genre<<endl;
				cout<< "\t\t\t\t\tDate: " <<  temp->year<<endl;
				cout<< "\t\t\t\t\tDuration: " << temp->dur <<endl;
				cout<< "\t\t\t\t\tIMDB: " << temp->imdb<<endl;
				cout<<"\t\t\t\t\tDirector Name:"<<temp->d_name<<endl;
				cout<<"\n\t\t\t\t\t\t:Overview:\n\n"<<temp->description<<endl<<endl;
				
				getchar();
				system ("CLS");
			}
			else{
				cout<<"\n\n\t\t\t\t\tMovie is not present!/ "<<endl;
				getchar();
				system ("CLS");
			}	
		}
   		
   		//This functon is linked to search by ID. It finds the perticular Node which has the desired movie details w.r.t its ID.
		Node *find(string val, Node *r){
			if(r == 0){
				return 0;
			}
			else if(val < r->id){
				return find(val,r->left);
			}
			else if(val > r->id){
				return find(val,r->right);
			}
			return r;	  
		}
   
   		//This function is linked with top Ratings. It displays the movies which have 5 star rating in InOrder treversal.
		void ratingInorder(Node *r){
			if(r == 0){
				return;
			}
	
			if(r->rating == "5"){
    	
				cout<<"\n\n\t\t\t\t\tID: "<<r->id<<endl;
				cout<<"\t\t\t\t\tMOVIE NAME: "<<r->name<<endl;
				cout<<"\t\t\t\t\tMOVIE RATING: "<<r->rating<<endl;
				cout<<"\t\t\t\t\tMOVIE GENRE: "<<r->genre<<endl;
				cout<< "\t\t\t\t\tDate: " <<  r->year<<endl;
				cout<< "\t\t\t\t\tDuration: " << r->dur <<endl;
				cout<< "\t\t\t\t\tIMDB: " << r->imdb<<endl;
				cout<<"\t\t\t\t\tDirector Name: "<<r->d_name<<endl;
				cout<<"\n\t\t\t\t\t\t:Overview:\n\n"<<r->description<<endl<<endl;
			}   
			ratingInorder(r->left);
			ratingInorder(r->right);   
		} 
  		
  		//This function displays all the movies which have a 5 star rating
    	void displayTopRatings(){
			cout<<"\n\n\t\t\t\t\tTop rated Movies:  "<<endl;
			ratingInorder(root);
			getchar();
			cout<<endl<<endl;
		}
   
   		//This function displays all the movies w.r.t the rating which the user provided in InOrder treversal.
    	void preferedInorder(string a,Node *r){
			if(r == 0){
				return;
			}
	
			if(r->rating == a){
				cout<<"\n\n\t\t\t\t\tID: "<<r->id<<endl;
				cout<<"\t\t\t\t\tMOVIE NAME: "<<r->name<<endl;
				cout<<"\t\t\t\t\tMOVIE RATING: "<<r->rating<<endl;
				cout<<"\t\t\t\t\tMOVIE GENRE: "<<r->genre<<endl;
				cout<< "\t\t\t\t\tDate: " <<  r->year<<endl;
				cout<< "\t\t\t\t\tDuration: " << r->dur <<endl;
				cout<< "\t\t\t\t\tIMDB: " << r->imdb<<endl;
				cout<<"\t\t\t\t\tDirector Name: "<<r->d_name<<endl;
				cout<<"\n\t\t\t\t\t\t:Overview:\n\n"<<r->description<<endl<<endl;
			}   
			preferedInorder(a,r->left);
			preferedInorder(a,r->right);   
		} 
  		
  		//This function displays all the movies w.r.t the rating which the user provided.
    	void displayUserPreferedRatings(string a){
    		cout<<"\n\n\t\t\t\t\tUser preferred rating movies: "<<endl;
			preferedInorder(a,root);
			getchar();
			system ("CLS");
			cout<<endl<<endl;
		}
   		
   		// search by the Genre of the movie
		void searchByGenre(string val){
			ByGenre(val,root);
			getchar();
			system ("CLS");
			cout<<endl<<endl;
		}
   		
   		// search by the Genre of the movie and displays in InOrder Treversal.
		void ByGenre(string a,Node *r){
			if(r == 0){
				return;
			}
	
			if(r->genre == a){
    			cout<<"\n\n\t\t\t\t\tID: "<<r->id<<endl;
				cout<<"\t\t\t\t\tMOVIE NAME: "<<r->name<<endl;
				cout<<"\t\t\t\t\tMOVIE RATING: "<<r->rating<<endl;
				cout<<"\t\t\t\t\tMOVIE GENRE: "<<r->genre<<endl;
				cout<< "\t\t\t\t\tDate: " <<  r->year<<endl;
				cout<< "\t\t\t\t\tDuration: " << r->dur <<endl;
				cout<< "\t\t\t\t\tIMDB: " << r->imdb<<endl;
				cout<<"\t\t\t\t\tDirector Name: "<<r->d_name<<endl;
				cout<<"\n\t\t\t\t\t\t:Overview:\n\n"<<r->description<<endl<<endl;
			}   
			ByGenre(a,r->left);
			ByGenre(a,r->right);   
		} 
   
   		// search by the Date of release of the movie
		void searchbyDate(string d) {
			cout << "\n\n\t\t\t\t\tMovies released on date " << d << " are: \n\n";
			inorderByDate(d,root);
			getchar();
			system ("CLS");
			cout << endl<< endl;  
		}
   
   		//This function displays all the movies w.r.t the date of release which the user provided.
		void inorderByDate(string a,Node *r){
			if(r == 0){
				return;
			}
	
			if(r->year == a){
    			cout<<"\n\n\t\t\t\t\tID: "<<r->id<<endl;
				cout<<"\t\t\t\t\tMOVIE NAME: "<<r->name<<endl;
				cout<<"\t\t\t\t\tMOVIE RATING: "<<r->rating<<endl;
				cout<<"\t\t\t\t\tMOVIE GENRE: "<<r->genre<<endl;
				cout<< "\t\t\t\t\tDate: " <<  r->year<<endl;
				cout<< "\t\t\t\t\tDuration: " << r->dur <<endl;
				cout<< "\t\t\t\t\tIMDB: " << r->imdb<<endl;
				cout<<"\t\t\t\t\tDirector Name: "<<r->d_name<<endl;
				cout<<"\n\t\t\t\t\t\t:Overview:\n\n"<<r->description<<endl<<endl;
			}   
			inorderByDate(a,r->left);
			inorderByDate(a,r->right);   
		} 
   
   		// search by the IMBD ID of release of the movie
		void searchByImdbId(string val){
			
			stack<Node*> Stack;
			Node *temp=root;
			
			while(temp!=NULL || Stack.empty()==false) {
				while(temp!=NULL) {
					Stack.push(temp);
					temp=temp->left;
				}
				
				temp=Stack.top();
				Stack.pop();
				
				if(temp->imdb==val) {
					break;
				}
				temp=temp->right;
			}
			
			if(temp==NULL) {
				cout << "\n\n\t\t\t\t\tImdb Donot Exist!\n";
				getchar();
			    system ("CLS");
				return;
			}
			if(temp->imdb == val){
				
				cout <<"\n\n\t\t\t\t\tMovie Details: \n\n";
				cout<<"\t\t\t\t\tID: "<<temp->id<<endl;
				cout<<"\t\t\t\t\tMOVIE NAME: "<<temp->name<<endl;
				cout<<"\t\t\t\t\tMOVIE RATING: "<<temp->rating<<endl;
				cout<<"\t\t\t\t\tMOVIE GENRE: "<<temp->genre<<endl;
				cout<< "\t\t\t\t\tDate: " <<  temp->year<<endl;
				cout<< "\t\t\t\t\tDuration: " << temp->dur <<endl;
				cout<< "\t\t\t\t\tIMDB: " << temp->imdb<<endl;
				cout<<"\t\t\t\t\tDirector Name:"<<temp->d_name<<endl;
				cout<<"\n\t\t\t\t\t\t:Overview:\n\n"<<temp->description<<endl<<endl;
				
				getchar();
				system ("CLS");
			}
			else{
				cout<<"\n\n\t\t\t\t\tNode is not there "<<endl;
				
				getchar();
				system ("CLS");
			}	
		}
  

		void inorder(Node *r){
			if(r == 0){
				return;
			}
	   
			inorder(r->left);
		
    		cout<<"\n\n\t\t\t\t\tID: "<<r->id<<endl;
			cout<<"\t\t\t\t\tMOVIE NAME: "<<r->name<<endl;
			cout<<"\t\t\t\t\tMOVIE RATING: "<<r->rating<<endl;
			cout<<"\t\t\t\t\tMOVIE GENRE: "<<r->genre<<endl;
			cout<< "\t\t\t\t\tDate: " <<  r->year<<endl;
			cout<< "\t\t\t\t\tDuration: " << r->dur <<endl;
			cout<< "\t\t\t\t\tIMDB: " << r->imdb<<endl;
			cout<<"\t\t\t\t\tDirector Name: "<<r->d_name<<endl;
			cout<<"\n\t\t\t\t\t\t:Overview:\n\n"<<r->description<<endl<<endl;
			
			inorder(r->right);   
		} 
  
  		//This function displays all the movies that are present in the BST.
    	void display(){
    		cout<<"\n\t\t\tDisplay All Data: "<<endl;
			inorder(root);
			getchar();
			cout<<endl<<endl;
		}
		
		// search by the Genre of the movie w.r.t to its top rating
		void seachGenreTopRated(string val) {
			genreRatingInorder(val,root);
			getchar();
		}
		
		// display the Genre of the movie w.r.t to its top rating.
		void genreRatingInorder(string val,Node *r){
			if(r == 0){
				return;
			}
			
			genreRatingInorder(val,r->left);
			
			if(r->genre==val) {
				if(r->rating == "5"){
					
    				cout<<"\n\n\t\t\t\t\tID: "<<r->id<<endl;
					cout<<"\t\t\t\t\tMOVIE NAME: "<<r->name<<endl;
					cout<<"\t\t\t\t\tMOVIE RATING: "<<r->rating<<endl;
					cout<<"\t\t\t\t\tMOVIE GENRE: "<<r->genre<<endl;
					cout<< "\t\t\t\t\tDate: " <<  r->year<<endl;
					cout<< "\t\t\t\t\tDuration: " << r->dur <<endl;
					cout<< "\t\t\t\t\tIMDB: " << r->imdb<<endl;
					cout<<"\t\t\t\t\tDirector Name: "<<r->d_name<<endl;
					cout<<"\n\t\t\t\t\t\t:Overview:\n\n"<<r->description<<endl<<endl;
				}
			}  
			 
			genreRatingInorder(val,r->right);  
		} 
  
      
};

void text_animation(string a){ // For the animation at the starting of application

	int i;
	long double j;
	
	for(i=0;a[i]!='\0';i++){

		for(j=0;j<10000000;j++);
			cout<<a[i];
	}
}

int main(){
	
	system("Color 80");
		cout <<"\n\n\n\n\n";
			cout <<"\t\t\t\t______________________________________________________\n\n\n";
			text_animation("\t\t\t\t\t\t~~ MOVIE RECOMMENDER ~~\n\n" );
    		cout <<"\t\t\t\t______________________________________________________";
    		text_animation("\n\t\t\t\t\t\tPrepared By:\n\t\t\t\t\t\tEl Programmers\n\n");
   			cout <<"\t\t\t\t______________________________________________________\n";
   			cout << "\n\t\t\t\t\t";
			system("pause");
			system ("CLS");
	Movies data;
	int c=0, opt=0;
	
	ifstream ip("Dataset1.csv");
	ifstream ic("Dataset2.csv");
	ifstream iz("Dataset3.csv");
	
	if(!ip.is_open() || !ic.is_open() || !iz.is_open()) {
		cout << "\n\n\t\t\terror file open!" << endl;
	}

	string id, userid, name, rating, genres, date, dur, imdb, d_name, overview, rate;
	
	//Reading data from the CSV file and inserting in AVL BST.
	while(ip.good() || ic.good() || iz.good()) {
		c++;
		getline(ip,id,',');
		getline(ip,userid,',');
		getline(ip,name,',');
		getline(ip,rating,',');
		getline(ip,genres,'\n');
		getline(ic,date,',');
		getline(ic,dur,',');
		getline(ic,imdb,',');
		getline(ic,d_name,',');
		getline(ic,rate,'\n');
		getline(iz,overview,'\n');
		
		data.insert(userid,name,id,rate, genres, date, dur, imdb, d_name, overview);
		
		if(c==500000) {
			break;
	     }
	}	
	//cout << c;
	ip.close();
	ic.close();
	iz.close();
	
	while(1) {
		
		
   			
		cout << endl << "\t\t\t\t\t\t~~MENU~~" << endl << endl;
	
		cout << "\t\t\t\t\t1. Search by Movie ID.\n" << endl;
		cout << "\t\t\t\t\t2. Search by Movie Name.\n" << endl;
		cout << "\t\t\t\t\t3. Search by Movie Release Date.\n" << endl;
		cout << "\t\t\t\t\t4. Search by Movie Imbd ID.\n" << endl;
		cout << "\t\t\t\t\t5. Search by Movie Genre.\n" << endl;
		cout << "\t\t\t\t\t6. Search Top Rated Movies.\n" << endl;
		cout << "\t\t\t\t\t7. Search by your Prefered Rating.\n" << endl;
		cout << "\t\t\t\t\t8. Search each Genre for Top Rated Movies.\n" << endl;
		cout << "\t\t\t\t\t9. Display all Movies.\n" << endl;
		cout << "\t\t\t\t\t10.Add each Movie by ID.\n" << endl;
		cout << "\t\t\t\t\t11.Delete each Movie by ID.\n" << endl;
		cout << "\t\t\t\t\t12.Close Application.\n" << endl;
		
		cout << "\t\t\t\t\tEnter any option number: ";
		cin >> opt;
		cout << "\n\t\t\t\t\t";

		system ("CLS");
		
		switch(opt) {
			case 1:
				cout << "\n\n\n\n\t\t\t\t\tEnter the Movie ID: ";
				getchar();
				getline(cin,id);
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				data.searchById(id);
				break;
				
			case 2:
				cout << "\n\n\n\n\t\t\t\t\tEnter the Movie Name: ";
				getchar();
				getline(cin,name);
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				data.searchByname(name);
				break;
				
			case 3:
				cout << "\n\n\n\n\t\t\t\t\tEnter the Movie Release Date (DD-MM-YY): ";
				getchar();
				getline(cin,date);
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				data.searchbyDate(date);
				break;	
				
			case 4:
				cout << "\n\n\n\n\t\t\t\t\tEnter the Movie IMDB Id: ";
				getchar();
				getline(cin,imdb);
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				data.searchByImdbId(imdb);
				break;		
			
			case 5:
				cout << "\n\n\n\n\t\t\t\t\tEnter the Movie Genre: ";
				getchar();
				getline(cin,genres);
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				data.searchByGenre(genres);
				break;
						
			case 6:
				data.displayTopRatings();
				getchar();
			    cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				break;
			
			case 7:
				cout << "\n\n\n\n\t\t\t\t\tEnter your Prefered Rating in Number(1-5): ";
				getchar();
				getline(cin,rating);
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				data.displayUserPreferedRatings(rating);
				break;
				
			case 8:
				cout << "\n\n\n\n\t\t\t\t\tEnter the Movie Genre: ";
				getchar();
				getline(cin,genres);
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				data.seachGenreTopRated(genres);
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				break;
				
			case 9:
				cout << "\n\n\n\n\t\t\t\t\tList of all Movies: " << endl;
				data.display();
				getchar();
			    cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				break;
			
			
			case 10:
				cout << "\n\n\n\n\t\t\t\t\tEnter the data for movie addition: ";
				getchar();
				system ("CLS");
				data.passs();
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				break;	
				
					
			case 11:
				cout << "\n\n\n\n\t\t\t\t\tEnter the ID for deletion: ";
				getchar();
				getline(cin,id);
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				data.pass(id);
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
				break;	
					
				
			case 12:
				cout << "\n\n\n\n\t\t\t\t\tClosing Application...";
				cout <<"\n\n\n\n\t\t\t\t\tThank You.";
				exit(0);
				break;		
			
			default:
				cout << "\n\n\n\n\t\t\t\t\tEnter valid Option!."<<endl;
				getchar();
				getchar();
				cout << "\n\t\t\t\t\t";
				system("pause");
				system ("CLS");
			    						
		}
	}
    
	return 0;
}

