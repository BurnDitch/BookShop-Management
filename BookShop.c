#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

//a structure has been defined which is used to maintain the details of any book
typedef struct
{
	char book_name[30];   
	char author[30];
	int b_id;
	int a_id;
	int copy;
	float price;
}book; //the structure is of type book
book records; //a variable records of type book is globally declared

void administrator(book records);  //function prototype
void user (book records);  //function prototype

//starting of the main program
void main()
{
		int i;    //variable declaration
		char str[10];  //variable declaration
		while(1)
		{
			     system("cls"); 

			     COORD c;
			     c.X = 30;
			     c.Y = 10;
			     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);                 
				 // gotoxy(30,10);
				 printf("PRESS 1 IF YOU ARE USER");

				 COORD d;
			     d.X = 30;
			     d.Y = 12;
			     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),d);
				 // gotoxy(30,12);
				 printf("PRESS 2 TO IF YOU ARE AN ADMINISTRATOR");

				 COORD e;
			     e.X = 30;
			     e.Y = 14;
			     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),e);
				 // gotoxy(30,14);
				 printf("PRESS 0 TO EXIT");

				 COORD f;
			     f.X = 30;
			     f.Y = 16;
			     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),f);
				 printf("ENTER YOUR CHOICE :");
				 fflush(stdin); //clearing the input buffer
				 scanf("%d",&i);  //taking input for required choice


				 switch (i)   //starting of switch case
				 {
						case 1:
							user(records);  //calling the user function to perform required tasks by the user
							break;

                        case 2:
							printf("ENTER THE PASSWORD(IN CAPITAL LETTER) :");
							scanf("%s",str);  //taking the password as input


							if(strcmp(str,"BOOKSHOP")==0)   //matching the password given as input with the stored password
							administrator(records); //calling administrator function to perform required tasks by him
							else
							printf("INVALID USER");
							getch();
							break;

					    case 0:
							exit(0); //termination of program

				  }//end of switch case

		  }//end of while
		// getch();

} //end of main function




void administrator(book records)
{
	FILE *p,*t,*q,*r;   //declaring file pointer......p is for books info....t is for demanded books....q is for transaction details....r is for temporary file for deleting record
	char an , b; //variable...an is for yes or no.
	int i,c,m,n=0;
	int a;        //for bookid modification
	static float sum;
	long int recsize;

	p=fopen("BOOK.C","rb+"); //opening a file in read mode...the file contains information about different books
	if (p==NULL)
	{
		p=fopen("BOOK.C","wb+"); //opening the file in write mode
			if(p==NULL)
			{
				puts("cannot open file");
				getch();
				exit(0);
			 }
	}

	t=fopen("DEMAND.C","rb+");//opening the file in read mode...the file contains information about the demanded books
	if(t==NULL)
	{
			t=fopen("DEMAND.C","wb+");  //opening
         	if(t==NULL)
			{
					puts("cannot open file");
					getch();
					exit(0);
			 }
	 }

	 q=fopen("BALANCE.C","rb+");  //opening a file for transaction//
	 if(q==NULL)
	 {
			q=fopen("BALANCE.C","wb+");  //the file is opened in writing mode
			if(q==NULL)
			{
					puts("CANNOT OPEN FILE");
					getch();
					exit(0);
			 }
	  }


	recsize=sizeof(records);

	while(1)
	{
			// clrscr();
		    system("cls");
			printf("PRESS 1 TO INSERT INTO ANY BOOK\n");
			printf("PRESS 2 TO LIST ALL BOOKS\n");
			printf("PRESS 3 TO INSERT INTO DEMAND LIST\n");
			printf("PRESS 4 TO LIST DEMAND BOOKS\n");
			printf("PRESS 5 TO MODIFY ANY RECORD\n");
			printf("PRESS 6 TO INSERT INTO TRANSACTION DETAILS\n");
			printf("PRESS 7 TO LIST TRANSACTION DETAILS\n");
			printf("PRESS 8 TO DELETE ANY RECORD\n");
			printf("PRESS 0 TO EXIT\n");


			printf("Enter your choice\n");
			fflush(stdin);
			scanf("%d",&i);//taking input to perform the specific operation

         switch(i)
			{
							case 1:
							fseek(p,0,SEEK_END); //keep the file pointer at the end of file
							an='y';
							while(an=='y')
							{
								printf(" ENTER BOOK NAME(IN CAPITAL LETTER):"); //taking input of the book nam,author name,
								scanf("%s",records.book_name);   //and other required informations about
								printf(" ENTER AUTHOR NAME(IN CAPITAL LETTER) :");   // any book
								scanf("%s",records.author);
								printf(" ENTER BOOK ID :");
								scanf("%d",&records.b_id);
								printf(" ENTER AUTHOR ID :");
								scanf("%d",&records.a_id);
								printf(" ENTER NUMBER OF COPIES :");
								scanf("%d",&records.copy);
								printf(" ENTER THE PRICE :");
								scanf("%f",&records.price);

								fwrite(&records,recsize,1,p);// writing the input data into the file in binary format

								printf(" ADD ANOTHER RECORD (y/n)");
								fflush(stdin);//clearing the input buffer
								an=getche();
						  }//end of while
						  break;


                     case 2:
						  rewind(p); //keeps the file pointer at the startinf of file

						  while(fread(&records,recsize,1,p)==1) //reads the data from the file
						  {
									printf(" BOOK NAME=%s",records.book_name);   //displaying the
									printf(" BOOK ID=%d",records.b_id);             //book details
									printf(" AUTHOR NAME=%s",records.author);
									printf(" AUTHOR ID=%d",records.a_id);
									printf(" NUMBER OF COPIES=%d",records.copy);
									printf(" PRICE=%f",records.price);
                           printf(" ");
						  }//end of while

						  getch();
						  break;


                     case 3:
						  fseek(t,0,SEEK_END); //keep the file pointer at the end of file

						  an='y';
						  while(an=='y')//to continue input taking
						  {
									printf(" ENTER BOOK NAME(IN CAPITAL LETTER) :");  //taking input of the required books that are not available
									scanf("%s",records.book_name);
									printf(" ENTER AUTHOR NAME(IN CAPITAL LETTER) :");
									scanf("%s",records.author);
									printf(" ENTER THE NUMBER OF COPIES :");
									scanf("%d",&records.copy);

									fwrite(&records,recsize,1,t); //writing the input data to the file in binary format

									printf(" ADD ANOTHER RECORD (y/n)");
									fflush(stdin); //clearing the input buffer
									an=getche();  //displays the character to be entered
							}//end of while
							break;


                     case 4:
							rewind(t); //keep the file pointer at the starting of file

							while(fread(&records,recsize,1,t)==1)//reads the data from the file
							{
									printf(" BOOKNAME=%s",records.book_name); //display the required books
									printf(" AUTHOR NAME=%s",records.author);
									printf(" NUMBER OF COPIES=%d",records.copy);
									printf(" ");
							}//end of while

							getch();
							break;

					case 5:
							an='Y';
							while(an=='Y')
							{

											printf(" ENTER THE BOOK ID TO MODIFY :");
											scanf("%d",&a);

											while(fread(&records,recsize,1,p)==1)
											{
														if(records.b_id==a)
														{

																	printf(" ENTER BOOK NAME :"); //taking input of the book nam,author name,
																	scanf("%s",records.book_name);   //and other required informations about
																	printf(" ENTER AUTHOR NAME :");   // any book
																	scanf("%s",records.author);
																	printf(" ENTER BOOK ID :");
																	scanf("%d",&records.b_id);
																	printf(" ENTER AUTHOR ID :");
																	scanf("%d",&records.a_id);
																	printf(" ENTER THE NUMBER OF COPIES :");
																	scanf("%d",&records.copy);
																	printf(" ENTER THE PRICE :");
																	scanf("%f",&records.price);

																	fseek(p,-recsize,SEEK_CUR);

																	fwrite(&records,recsize,1,p);//writing the modified record in the file
																	break;
														  }//end of if
												}//end of while

												printf(" MODIFY ANOTHER RECORD(Y/N) :");
												fflush(stdin);//clearing input buffer
												an=getche(); //the character will be displayed on screen
							 }//end of while

							 break;

					case 6:

							 an='Y';
							 while(an=='Y')
							 {
										fseek(q,0,SEEK_END);//placing the pointer at the end of file
										printf(" BOOK NAME( IN CAPITAL LETTER) :");//taking input
										scanf("%s",records.book_name);
										printf(" BOOK ID:");
										scanf("%d",&records.b_id);
										printf(" NO OF SOLD COPY :");
										scanf("%d",&records.copy);
										printf(" ENTER THE PRICE OF ONE COPY :");
										scanf("%f",&records.price);

										fwrite(&records,recsize,1,q);//writing the record in file

										printf(" ADD ANOTHER RECORD(Y/N)");
										fflush(stdin);//clearing the input buffer
										an=getche();
								}//end of while

								break;


					case 7:

								rewind(q);//the pointer is placed at the first position of file

								while(fread(&records,recsize,1,q)==1)//reading the data from file
								{
										printf("BOOKNAME=%s",records.book_name);//displaying the records
										printf("BOOK ID=%d",records.b_id);
										printf("PRICE OF ONE COPY=%f",records.price);
										printf("NO OF SOLD COPY=%d",records.copy);
								 }//end of while

								 getch();
								 break;


					case 8:

								 an='Y';
								 while(an=='Y')
								 {

										printf(" ENTER THE BOOK ID TO DELETE :");
										scanf("%d",&b);

										r=fopen("TEMP.C","wb");//a temporary file has benn opened
										rewind(p);

										while(fread(&records,recsize,1,p)==1)//readind the data
										{
												if(records.b_id!=b)
												{
														n++;
														fwrite(&records,recsize,1,r);//writing records in temporary file
												}//end of if
										}//end of while

										fclose(p);//file is colsed
										fclose(r);

										remove("BOOK.C");//original file is deleted
										rename("TEMP.C","BOOK.C");//temporary file is remaned
										p=fopen("BOOK.C","rb+");

										printf(" DELETE ANOTHER RECORD(Y/N)");
										fflush(stdin);
										an=getche();
									 }//end of while

									 getch();
									 break;



					case 0:

									 fclose(p);//closing the file BOOK.C
									 fclose(t);//closing the file DEMAND.C
									 fclose(q);//closing the file BALANCE.C
									 exit(0);

							  }//end of switch

					  }//end of while





void user(book records)
{
		FILE *p,*t;  //declaring file pointer
		char arr[30];
		int an; //variable declaration
		int i,e,cp,m,ch;
		int n=0;

		p=fopen("BOOK.C","rb+");//opening the file containing book details in read mode
		if(p==NULL)
		{
			p=fopen("BOOK.C","wb+");
			if(p==NULL)
			{
				puts("CANNOT OPEN FILE");
				getch();
				exit(0);
			}
		 }

		 t=fopen("DEMAND.C","rb+");//opening the file in read mode
		 if(t==NULL)
		 {
						t=fopen("DEMAND.C","wb+"); //opening the file in write mode
			if(t==NULL)
			{
				puts("CANNOT OPEN FILE");
				getch();
				exit(0);
			}
		 }

		  while(1)
		  {
						// clrscr();
		  	            system("cls");
						COORD c;
			            c.X = 30;
			            c.Y = 8;
			            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
						// gotoxy(30,8);
						printf("PRESS 1 TO SEARCH BY BOOK NAME ");
						COORD d;
			            d.X = 30;
			            d.Y = 10;
			            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),d);
						// gotoxy(30,10);
						printf("PRESS 2 TO SEARCH BY AUTHOR NAME ");
						COORD g;
			            g.X = 30;
			            g.Y = 12;
			            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),g);
						// gotoxy(30,12);
						printf("PRESS 0 TO EXIT");

						COORD f;
			            f.X = 30;
			            f.Y = 16;
			            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),f);
						// gotoxy(30,16);

						printf("ENTER YOUR CHOICE:");
						fflush(stdin);
						scanf("%d",&i);//taking input from user


						switch(i)
						{

									case 1:
									printf(" ENTER THE BOOK NAME(IN CAPITAL LETTER):");
									scanf("%s",arr);//taking the bok name from user


									rewind(p);

									while(fread(&records,sizeof(book),1,p)==1)//reading the data from file
									{
											if(strcmp(records.book_name,arr)==0)//comparing the data with input book name
											{
																printf(" BOOKNAME=%s",records.book_name);//displaying the required results
																printf(" AUTHOR=%s",records.author);
																printf(" BOOK ID=%d",records.b_id);
																printf(" PRICE=%f",records.price);
											}//end of if
									}//end of while


									printf(" DO YOU FIND REQUIRED BOOK(1 for yes/2 for no)");
									scanf("%d",&ch);//check for finding books

									if(ch==1)
									{
												printf(" ENTER THE BOOK ID :");
												scanf("%d",&e);

												printf(" ENTER THE NO. OF COPIES YOU WANT :");
												scanf("%d",&cp);//input for required copies

												rewind(p);//place the pointer at first position

												while(fread(&records,sizeof(book),1,p)==1)//reading the data from file
												{

														if(records.b_id==e)//comparing the book id with the input
														{

																	m=records.copy-cp;//calculating the remaining books after selling
																	if(m<0)//checking for availability of books
																	{
																			printf(" ALL THE COPIES ARE NOT AVAILABLE");
																			break;
																	}
																	printf(" COPIES ARE AVAILABLE");
														}
												} //end of while
									}//end of if

							if(ch==2)
							{

												printf(" DO YOU WANT TO GIVE ANY DEMAND?(1 FOR YES/2 FOR NO)");//for giving demand
												scanf("%d",&an);

												if(an==1)
												{


															fseek(t,0,SEEK_END);//placing the pointer at the end of file
															printf(" BOOK NAME (IN CAPITAL LETTER) :");
															scanf("%s",records.book_name);
															printf(" ENTER AUTHOR NAME (IN CAPITAL LETTER) :");
															scanf("%s",records.author);
															printf(" ENTER THE NO OF COPY :");
															scanf("%d",&records.copy);

															fwrite(&records,sizeof(book),1,t);//writing the record into file

                                             printf("YOUR DEMAND HAS BEEN PLACED SUCCESSFULLY");
												}//end of if


											if(an==2)
											{
															printf(" THANKS FOR YOUR CHOICE");
											}//end of if
							  }//end of if

						getch();
						break;


					case 2:
					printf(" ENTER THE AUTHOR NAME(IN CAPITAL LETTER):");
					scanf("%s",arr);//taking input the author name

					rewind(p);

					while(fread(&records,sizeof(book),1,p)==1)//reading the data from file
					{
								if(strcmp(records.author,arr)==0)//comparing the input with the data of file
								{
										printf(" BOOKNAME=%s",records.book_name);//displaying the required results
										printf("AUTHOR=%s",records.author);
										printf(" BOOK ID=%d",records.b_id);
										printf(" PRICE=%f",records.price);
								}//end of if
					}//end of else


					printf(" DO YOU FIND REQUIRED BOOK(1 for yes/2 for no)");
					scanf("%d",&ch);

					if(ch==1)
					{
								printf(" ENTER THE BOOK ID :");
								scanf("%d",&e);

								printf(" ENTER THE NO. OF COPIES YOU WANT :");
								scanf("%d",&cp);

								rewind(p);//place the pointer at the first position of file

								while(fread(&records,sizeof(book),1,p)==1)//reading the data from file
								{

											if(records.b_id==e)//comparing the book id with the input
											{

														m=records.copy-cp;//calculating the no of copies after selling
														if(m<0)//check for availability
														{
																	printf(" ALL THE COPIES ARE NOT AVAILABLE");
																	break;
														}//end of if
														printf(" COPIES ARE AVAILABLE");
											 }//end of if
								 }//end of while
					}//end of if

		if(ch==2)
		{

					printf(" DO YOU WANT TO GIVE ANY DEMAND?( 1 FOR YES / 2 FOR NO)");
					scanf("%d",&an);//for demand giving

					if(an==1)
					{


							fseek(t,0,SEEK_END); //placing the pointer at the end of file
							printf(" BOOK NAME (IN CAPITAL LETTER) :");//taking input
							scanf("%s",records.book_name);
							printf(" ENTER AUTHOR NAME (IN CAPITAL LETTER) :");
							scanf("%s",records.author);
							printf(" ENTER THE NO OF COPY :");
							scanf("%d",&records.copy);

							fwrite(&records,sizeof(book),1,t);//writing the data into file

                     printf("YOUR DEMAND HAS BEEN PLACED SUCCESSFULLY");
					}//end of if


					if(an==2)
					{
							printf(" THANKS FOR YOUR CHOICE");
					}//end of if
			}//end of if
					getch();
					break;



					case 0:

					fclose(p);//closing the file BOOK.C
					fclose(t);//closing the file DEMAND.C
					exit(0);
			}//end of switch
	  }//end of while

}//end of user function

