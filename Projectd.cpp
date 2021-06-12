#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<conio.h>

/*BUS TRANSPORTATION PORTAL as group project for Programming Fundamentals
by k181198, Mubeen;k181113, Saad ur Rehman;k181184, Anas Siddiqui;and k181294, Jaafar.*/

//All functions used in this project.
void create_acc();
void trans_state();
void userpass();
void user();
void buy_ticket();
void view_bought();
void refund();
void admin();
void edit_data();
void cancel_bookings();
void edit_routes();
void add_data(FILE *);
void delete_data(FILE *);
void edit_pricing(FILE *);

struct ticket{
	char bus[20];
	char name[20];
	char starting_point[20];
	char des[20];
	char category[10];
	int stopno;
	int cost;
}t;

struct login_details
{
	char username[20];
	char pass[20];
	char a_u;
}u,f,c,n;

struct stop{
	int sno;
	char bus[20];
	char city[10];
	int travelmin; 
};

struct time{
	char busn[20];
	int hour;
	int min;
};

main()//Redirects user to a choice to create an account, or just login with an existing one. Admins will be redirected to login
{
	system("cls");
	printf("\t\t\t\t\t\t*****************************\n\t\t\t\t\t\t    FAST TRANSPORT PORTAL\n\t\t\t\t\t\t*****************************\n\n\n");
	int choice,flag=1;
	puts("\t\t\t**************************************************************");
	printf("\t\t\tLogin as: \n\t\t\t1. Customer\n\t\t\t2. Administrator\n\t\t\t0. Exit\n ");
	puts("\t\t\t**************************************************************");
	puts("Choice:");
	scanf("%d",&choice);
	do{
		flag=1;
		switch (choice)
		{
			case 1:
				trans_state();
				flag=0;
				break;
			case 2:
				userpass();
				flag=0;
				break;
			case 0:
				exit(0);
				break;
			default:
				printf("Invalid Choice");
				printf("\nEnter correct choice: ");
				scanf("%d",&choice);
				flag=0;
				break;
		}
	}while(flag==0);
}

void trans_state()
{
	system("cls");
	int choice,flag;
	printf("Choose your option: \n1. Login\n2. Create account\n0. Exit\n\nChoice: ");
	scanf("%d",&choice);
	do{
		flag=1;
		switch (choice)
		{
			case 1:
				userpass();
				break;
			case 2:
				create_acc();
				break;
			case 0:
				exit(0);
				break;
			default:
				printf("Invalid Choice");
				printf("\nEnter correct choice: ");
				scanf("%d",&choice);
				flag=0;
				break;
		}
	}while(flag==0);
}

void create_acc()//Creating a fresh user account
{
	system("cls");
	int flag,i=0;
	FILE *fp,*fs;
	fp=fopen("login_details.txt","a");
	fs=fopen("login_details.txt","r");
	if(fp==NULL)
	{
		printf("File can't be accessed");
		exit(0);	
	}
	printf("KEEP YOUR USERNAME AND PASSWORD SAFE\nYOU WILL NEED THESE TO LOGIN EVERYTIME\n\n");
	n.a_u='U';
	do{
		printf("Choose a username: ");
		scanf("%s",n.username);
		flag=1;
		while(fscanf(fs,"%s %s %c\n",c.username,c.pass,&c.a_u)!=EOF)
		{
			if(strcmp(c.username,n.username)==0)
			{
				flag=0;
				printf("\nUsername already exists.\n");
			}
		}
	}while(flag==0);
	printf("Enter password: ");
	while(1)
	{
		n.pass[i]=getch();
		if(n.pass[i]==13)
		{
			n.pass[i]='\0';
			break;
		}
		if(u.pass[i]=='\b')
		{
			printf("\b");
			i--;
			continue;
		}
		printf("*");
		i++;
	}
	fprintf(fp,"\n%s %s %c",n.username,n.pass,n.a_u);
	fclose(fp);
}

void userpass()//Allows admins or user to login and redirects them to their user interferences
{
	system("cls");
	int choice,flag,i=0;
	FILE *fp;
	fp=fopen("login_details.txt","r");
	if(fp==NULL)
	{
		printf("File can't be accessed");
		exit(0);
	}
	printf("FIELDS ARE CASE SENSITIVE\n\n");
	printf("Enter username: ");
	scanf("%s",u.username);
	fflush(stdin);
	printf("Enter password: ");
	while(1)
	{
		u.pass[i]=getch();
		if(u.pass[i]==13)
		{
			u.pass[i]='\0';
			break;
		}
		if(u.pass[i]=='\b')
		{
			printf("\b");
			i--;
			continue;
		}
		printf("*");
		i++;
	}
	fflush(stdin);
	static int count=0;
	while(fscanf(fp,"%s %s %c\n",f.username,f.pass,&f.a_u)!=EOF)
	{
		if(strcmp(u.username,f.username)==0&&strcmp(u.pass,f.pass)==0&&'A'==f.a_u)
		{
			printf("\nLOGIN AS ADMIN SUCCESSFULL.....");
			puts("\npress any key to continue...");
			getch();
			admin();
			break;
		}
		else if(strcmp(u.username,f.username)==0&&strcmp(u.pass,f.pass)==0&&'U'==f.a_u)
		{
			printf("\nLOGIN AS USER SUCCESSFULL...");
			puts("\npress any key to continue...");
			getch();
			user();
			break;
		}
		else if(feof(fp))
		{
			count++;
			if (count==3)//If end user doesnt try incorrect credintials too many times
			{
				printf("You have entered incorrect credentials too many times. Please try later");
				exit(0);
			}
			printf("Incorrect Username/Password\n1. Try again\n2. Create new user account\n0. Exit\nEnter choice: ");
			scanf("%d",&choice);//Choice to create new account in case user enters wrong password
			switch (choice)
			{
				case 1:
					userpass();
					break;
				case 2:
					create_acc();
					break;
				case 0:
					exit(0);
					break;
				default:
					printf("Invalid Choice");
					printf("\nEnter correct choice: ");
					scanf("%d",&choice);
					flag=0;
					break;
			}
		}
	}
	fclose(fp);
}

void user()//User interference
{
	system("cls");
	printf("WELCOME User %s\n\n",u.username);
	int choice,flag;
	void (*p[3])();
	p[0]=buy_ticket;
	p[1]=view_bought;
	p[2]=refund;
	printf("Choose action to perform:\n1. Buy tickets\n2. View bought tickets\n3. Refund tickets\n0. Log out\nChoice: ");
	scanf("%d",&choice);
	choice--;
	do{
		flag=1;
		switch (choice)
		{
			case 0:
			case 1:
			case 2:
				(*p[choice])();
				break;
			case -1:
				main();
				break;
			default:
				printf("Invalid Choice");
				printf("\nEnter correct choice: ");
				scanf("%d",&choice);
				choice--;
				flag=0;
				break;
		}
	}while(flag==0);
}

void buy_ticket()//User buys their desireable ticket
{
	FILE *fp,*fs,*ft;
	char *p[]={"Karachi","Hyderabad","Sukkur","Lahore","Islamabad","Quetta","Rawalpindi","Faislabad","Multan","Sialkot","Peshawar","Nawabshah","Murree","Kashmir"};
	int st_point,d,flag,travel,var,n=0,choice,suggest,min=100;
	strcpy(t.name,u.username);
	printf("\n\n1.Karachi\t2.Hyderarbad\t3.Sukkar\n4.Lahore\t5.Islamabad\t6.Quetta\n7.Rawalpindi\t8.Faislabad\t9.multan\n10.sialkot\t11.Peshawar\t12.Nawabshah\n13.Murree\t14.Kashmir\n");
	do{
		flag=1;
		printf("choose starting point: ");
		scanf("%d",&st_point);
		strcpy(t.starting_point,p[st_point-1]);
		fflush(stdin);
		printf("choose Destination ");
		scanf("%d",&d);
		strcpy(t.des,p[d-1]);
		if (d==st_point)
		{
			printf("\nYou entered the same pickup and destination. Please input correct values\n");
			flag=0;
		}
	}while(flag=0);
	fflush(stdin);
	printf("\n\n1.Economy\t2.Business\nEnter class to travel in: ");
	scanf("%d",&var);
	if(var==1)
	{
		strcpy(t.category,"Economy");
	}
	else if(var==2)
	{
		strcpy(t.category,"Business");
	}
	fflush(stdin);
	fflush(stdin);
	fp=fopen("bookings.txt","a+");
	fs=fopen("routes.txt","r");
	ft=fopen("routes.txt","r");
	if(fp==NULL||fs==NULL)
	{
		printf("Can't open file");
		exit(0);
	}
	struct stop s,q;
	printf("\nSno.\t    Bus name        \tPickup\t \tDestination \tCategory     Stops \tCost");
	while(!feof(fs))
	{
		fscanf(fs,"%d %s %s %d\n",&s.sno,s.bus,s.city,&s.travelmin);
		while(!feof(ft))
		{
			fscanf(ft,"%d %s %s %d\n",&q.sno,q.bus,q.city,&q.travelmin);
			if((strcmp(s.city,t.starting_point)==0)&&(strcmp(q.city,t.des)==0)&&(strcmp(q.bus,s.bus)==0)&&(q.sno>s.sno))
			{
				strcpy(t.bus,q.bus);
				t.stopno=q.sno-s.sno-1;
				travel=q.travelmin-s.travelmin;
				if(strcmp(t.category,"Economy"))
				{
					t.cost=travel*7.5;
				}
				if(strcmp(t.category,"Business"))
				{
					t.cost=travel*7.5*1.75;
				}
				n++;
				if(t.stopno<min)//Calculating best choice for user, based on minimum number of stops.
				{
					min=t.stopno;
					suggest=n;
				}
				printf("\n%4d %15s     %15s %15s %15s   %4d    \t%4d\n",n,t.bus,t.starting_point,t.des,t.category,t.stopno,t.cost);
				break;
			}
		}
		rewind(ft);
	}
	printf("Enter sno. to book tickets(#%d is suggested)",suggest);
	scanf("%d",&choice);
	rewind(ft);
	rewind(fs);
	n=0;
	while(!feof(fs))
	{
		fscanf(fs,"%d %s %s %d\n",&s.sno,s.bus,s.city,&s.travelmin);
		while(!feof(ft))
		{
			fscanf(ft,"%d %s %s %d\n",&q.sno,q.bus,q.city,&q.travelmin);
			if((strcmp(s.city,t.starting_point)==0)&&(strcmp(q.city,t.des)==0)&&(strcmp(q.bus,s.bus)==0)&&(q.sno>s.sno))
			{
				strcpy(t.bus,q.bus);
				t.stopno=q.sno-s.sno-1;
				travel=q.travelmin-s.travelmin;
				//Calculating costs for the trip based on time taken between the trip and class.
				if(strcmp(t.category,"Economy"))
				{
					t.cost=travel*7.5;
				}
				if(strcmp(t.category,"Business"))
				{
					t.cost=travel*7.5*1.75;
				}
				n++;
				if(choice==n)
				{
					fprintf(fp,"%s %s %s %s %s %d %d\n",t.name,t.bus,t.starting_point,t.des,t.category,t.stopno,t.cost);
					printf("\nTICKET SUCCESSFULLY BOOKED\nRs. %d have been deducted from your account",t.cost);
				}
				break;
			}
		}
		rewind(ft);
	}
	fclose(fp);	
	fclose(fs);
	fclose(ft);
	puts("\nPress any key to continue...");
	getch();
	user();
}

void view_bought()//Users can view all tickets they booked previously.
{
	FILE *fp;
	fp=fopen("bookings.txt","r");
	if(fp==NULL)
	{
		printf("file not found \n");
	}
	printf("\tBus name\tPickup\t\tDestination\tCategory\tStops\n");
	do
	{
		if(strcmp(t.name,u.username)==0)
		{
			printf("%15s %15s %15s %15s \t%3d\n",t.bus,t.starting_point,t.des,t.category,t.stopno);
		}
	}while((fscanf(fp,"%s %s %s %s %s %d %d\n",t.name,t.bus,t.starting_point,t.des,t.category,&t.stopno,&t.cost)!=EOF));
	fclose(fp);
	puts("\nPress any key to continue...");
	getch();
	user();
}

void refund()//Users can get a partial refund of their ticket
{
	FILE *fp,*fs;
	int n=0,sn,days,ref;
	fp=fopen("bookings.txt","r");
	fs=fopen("temp.txt","w");
	if(fp==NULL)
	{
		printf("File can't be opened\n");
		exit(0);
	}
	printf("Sno. \tBus name\tPickup\t\tDestination\tCategory\tStops\n");
	do
	{
		if(strcmp(t.name,u.username)==0)
		{
			n++;
			printf("%3d %15s %15s %15s %15s \t%3d\n",n,t.bus,t.starting_point,t.des,t.category,t.stopno);
		}
	}while((fscanf(fp,"%s %s %s %s %s %d %d\n",t.name,t.bus,t.starting_point,t.des,t.category,&t.stopno,&t.cost)!=EOF));
	printf("\nEnter s no of booking you want a refund for: ");
	scanf("%d",&sn);
	printf("Before how many days from now did you buy this ticket: ");
	scanf("%d",&days);
	rewind(fp);
	n=0;
	do
	{
		if(strcmp(t.name,u.username)==0)
		{
			n++;
			if(n!=sn)
			{
				fprintf(fs,"%s %s %s %s %s %d %d\n",t.name,t.bus,t.starting_point,t.des,t.category,t.stopno,t.cost);
			}
			else if(n==sn)
			{
				//Refund calculation based on number of days user came after buying a ticket.
				if (days<=2)
				{
					ref=t.cost*75/100;
					printf("\nRs. %d are refunded to your account");
				}
				else if (days<=4)
				{
					ref=t.cost*50/100;
					printf("\nRs. %d are refunded to your account");
				}
				else
				{
					ref=0;
					printf("You are not eligible for a refund");
				}
			}
		}
	}while((fscanf(fp,"%s %s %s %s %s %d %d\n",t.name,t.bus,t.starting_point,t.des,t.category,&t.stopno,&t.cost)!=EOF));
	fclose(fp);
	fclose(fs);
	//changes in file made.
	remove("bookings.txt");
	rename("temp.txt","bookings.txt");
	puts("\nPress any key to continue...");
	getch();
	user();
}

void admin()//Admin interference and options
{
	system("cls");
	printf("WELCOME Admin %s\n\n",u.username);
	int flag,choice=0;
	void (*p[3])();
	p[0]=edit_data;
	p[1]=cancel_bookings;
	printf("Choose action to perform:\n1. Edit data\n2. Cancel bookings\n0. Log out\nChoice: ");
	scanf("%d",&choice);
	choice--;
	do{
		flag=1;
		switch (choice)
		{
			case 0:
			case 1:
				(*p[choice])();
				break;
			case -1:
				main();
				break;
			default:
				printf("Invalid Choice");
				printf("\nEnter correct choice: ");
				scanf("%d",&choice);
				choice--;
				flag=0;
				break;
		}
	}while(flag==0);
}

void edit_data()//Can add or delete bus routes here
{
	system("cls");
	int choice,flag;
	FILE *fp;
	fp=fopen("routes.txt","r+");
	if (fp==NULL)
	{
		printf("Cannot open file");
		exit(0);
	}
	printf("Choose an option:\n1. Add a bus service and define its routes\n2. Delete a bus service and all its data.\n0. Go back\nChoose an option: ");
	
	scanf("%d",&choice);
	do{
		flag=1;
		switch(choice)
		{
			case 1:
				add_data(fp);
				break;
			case 2:
				delete_data(fp);
				break;
			case 0:
				admin();
				break;
			default:
				printf("Invalid Choice");
				printf("\nEnter correct choice: ");
				scanf("%d",&choice);
				flag=0;
				break;
		}
	}while(flag==0);
}

void add_data(FILE *fp)//Adding bus routes.
{
	fseek(fp,0,SEEK_END);
	struct time t;
	int stops,travelt,currentt;
	puts("Enter bus name to add: ");
	fflush(stdin);
	gets(t.busn);
	printf("Enter number of total stops(0 if direct route): ");
	scanf("%d",&stops);
	stops+=2;
	printf("\n\n1.Karachi\t2.Hyderarbad\t3.Sukkar\n4.Lahore\t5.Islamabad\t6.Quetta\n7.Rawalpindi\t8.Faislabad\t9.Multan\n10.Sialkot\t11.Peshawar\t12.Nawabshah\n13.Murree\t14.Kashmir\nBE CAREFUL WHEN WRITING CITIES, FIELDS ARE CASE SENSITIVE\nDATA MAY NOT SAVE PROPERLY WHEN TYPED INCORRECTLY");
	struct stop s[stops];
	for (int i=0;i<stops;i++)
	{
		s[i].sno=i+1;
		strcpy(s[i].bus,t.busn);
		if(i==0)
		{
			puts("\nEnter starting point: ");
			fflush(stdin);
			gets(s[i].city);
			s[i].travelmin=0;
			travelt=0;
			fprintf(fp,"%d %s %s %d\n",s[i].sno,s[i].bus,s[i].city,s[i].travelmin);
		}
		if((i!=0)&&(i!=stops-1))
		{
			puts("Enter next stop: ");
			fflush(stdin);
			gets(s[i].city);
			printf("Enter travel time (in mins) to this destination: ");
			scanf("%d",&currentt);
			travelt+=currentt;
			s[i].travelmin=travelt;
			fprintf(fp,"%d %s %s %d\n",s[i].sno,s[i].bus,s[i].city,s[i].travelmin);
		}
		if(i==stops-1)
		{
			puts("Enter destination: ");
			fflush(stdin);
			gets(s[i].city);
			printf("Enter travel time (in mins) to this destination: ");
			scanf("%d",&currentt);
			travelt+=currentt;
			s[i].travelmin=travelt;
			fprintf(fp,"%d %s %s %d\n",s[i].sno,s[i].bus,s[i].city,s[i].travelmin);
		}
	}
	for (int i=stops-1;i>=0;i--)
	{
		
		if(i==stops-1)
		{
			fprintf(fp,"%d %s %s %d\n",s[stops-i-1].sno,s[i].bus,s[i].city,s[stops-i-1].travelmin);
		}
		if((i!=0)&&(i!=stops-1))
		{
			fprintf(fp,"%d %s %s %d\n",s[stops-i-1].sno,s[i].bus,s[i].city,s[stops-i-1].travelmin);
		}
		if(i==0)
		{
			fprintf(fp,"%d %s %s %d\n",s[stops-i-1].sno,s[i].bus,s[i].city,s[stops-i-1].travelmin);
		}
	}
	fclose(fp);
	printf("\nPress any key to continue");
	getc(fp);
	admin();
}

void delete_data(FILE *fp)//Deleting all content related to bus entered
{
	struct stop d;
    FILE *ft;
    char dbus[20],confirm;
    ft = fopen("temp.txt","w");

    printf("\nEnter bus name to delete its record: ");
    fflush(stdin);
	scanf("%s",dbus);
    rewind(fp);
    while (!feof(fp)){
        fscanf(fp,"%d %s %s %d", &d.sno,d.bus, d.city, &d.travelmin);

        if(strcmp(d.bus,dbus)!=0){
            fprintf(ft,"%d %s %s %d\n", d.sno,d.bus, d.city, d.travelmin);
        }
    }
	printf("Are you sure, you want to delete all of the data related to this bus(Y/N)?:  ");
	fflush(stdin);
	scanf("%c",&confirm);//Asking if admin is sure and have'nt changed his/her mind
	fclose(fp);
	fclose(ft);
    if(confirm=='Y')
    {
    	remove("routes.txt");
    	rename("temp.txt","routes.txt");
    	printf("\nAll data related to bus deleted");
	}
    else if(confirm=='N')
    {
		remove("temp.txt");
		printf("\nThe routes are not deleted");
	}
	printf("\nPress any key to continue");
	getc(fp);
	admin();
}

void cancel_bookings()//Can cancel any user's booking in case of any emergency or otherwise.
{
	FILE *fp,*fs;
	fp=fopen("bookings.txt","r");
	fs=fopen("temp.txt","w");
	if (fp==NULL||fs==NULL)
	{
		printf("File cannot be opened");
		exit(0);
	}
	int c,no,nol=1,sno=0;
	printf("S.no\t\tCustomer\tPickup    \tDestination    \tCategory\n");
	while (!feof(fp))
	{
		sno++;
		fscanf(fp,"%s %s %s %s %s %d %d\n",t.name,t.bus,t.starting_point,t.des,t.category,&t.stopno,&t.cost);
		printf("%4d  %15s  %15s  %15s  %15s\n",sno,t.name,t.starting_point,t.des,t.category);
	}
	printf("Enter s.no of booking you want to cancel ");
	scanf("%d",&no);
	rewind(fp);
	fflush(stdin);
	while(!feof(fp))
	{
		c=fgetc(fp);
		if(c=='\n')
		{
			nol++;
		}
		if (nol!=no)
		{
			fputc(c,fs);
		}
	}
	fclose(fp);
	fclose(fs);
	//Changes to file made.
	remove("bookings.txt");
	rename("temp.txt","bookings.txt");
	printf("\nBOOKING SUCCESsFULLY CANCELLED\nPress any key to continue");
	getch();
	admin();
}
