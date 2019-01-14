
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
int size,score;
char a[100][100]={' '};
using namespace std;
struct node
{
	int x;
	int y;
	char ch;
	struct node *next;
};
struct food
{
	int x;
	int y;
};
struct poison
{
	int x;
	int y;
};
struct node *list(int length)
{
	struct node *start,*head,*ptr;
	ptr=new node();
	ptr->x=ptr->y=size/2;
	ptr->ch='S';
	ptr->next=NULL;
	start=head=ptr;
	length-=2;
	while(length--)
	{
		ptr=new node();
		ptr->x=head->x;
		ptr->y=head->y+1;
		ptr->ch='<';
		ptr->next=NULL;
		head->next=ptr;
		head=head->next;
	}
	ptr=new node();
	ptr->x=head->x;
	ptr->y=head->y+1;
	ptr->ch='E';
	head->next=ptr;
	ptr->next=NULL;
	return start;
}
void display(struct node *start,struct food *f,struct poison *p)
{
	system("CLS");
	int i,j;struct node *ptr;ptr=start;
	for(i=0;i<size;i++)
	{
		a[0][i]='*';
		a[i][0]='*';
		a[size-1][i]='*';
		a[i][size-1]='*';
	}
	a[f->x][f->y]='F';
	a[p->x][p->y]='P';
	cout<<"score = "<<score<<endl;
	while(ptr!=NULL)
	{
		a[ptr->x][ptr->y]=ptr->ch;
		if(ptr->x==start->x && ptr->y==start->y)
		a[ptr->x][ptr->y]=start->ch;
		ptr=ptr->next;	
	}
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			printf("%c ",a[i][j]);
		}
		cout<<endl;
	}
}
struct node *snakeload(char *loadata,int i)
{
	struct node *start,*ptr,*head;
	ptr=new node();
	while(loadata[i]!='-')
	{		
		ptr->x=ptr->x*10+((int)(loadata[i])-48);
		i=i+1;	
	}i=i+1;
	while(loadata[i]!='-')
	{	
		ptr->y=ptr->y*10+((int)(loadata[i])-48);
		i=i+1;	
	}i=i+1;
	ptr->ch='S';
	start=head=ptr;
	ptr->next=NULL;
	while(loadata[i]!='\0')
	{
		ptr=new node();
		while(loadata[i]!='-')
		{	
			ptr->x=ptr->x*10+((int)(loadata[i])-48);
			i=i+1;	
		}i=i+1;
		while(loadata[i]!='-')
		{	
			ptr->y=ptr->y*10+((int)(loadata[i])-48);
			i=i+1;
			if(loadata[i]=='\0')
			break;	
		}
		ptr->next=NULL;
		ptr->ch='<';
		head->next=ptr;
		head=head->next;
		if(loadata[i]!='\0')
		i=i+1;
		else
		break;		
	}
	ptr->ch='E';
	return start;
}
void change(struct node *start)
{
    struct node *ptr,*nptr;
    int e,b,c,d,i,j;
    for(i=0;i<size;i++)
    {
    	for(j=0;j<size;j++)
    	{
    		a[i][j]=' ';
		}
	}
    ptr=start;
    nptr=ptr->next;
    while(nptr!=NULL)
	{
		if(ptr==start)
		{
			e=nptr->x;
			b=nptr->y;
			nptr->x=ptr->x;
			nptr->y=ptr->y;
		}
		else
		{
			c=nptr->x;
			d=nptr->y;
			nptr->x=e;
			nptr->y=b;
			e=c;
			b=d;
		}
		ptr=ptr->next;
		nptr=ptr->next;
	}
}
void change1(struct node *start)
{
	int e,b,c,d,i,j;
	for(i=0;i<size;i++)
    {
    	for(j=0;j<size;j++)
    	{
    		a[i][j]=' ';
		}
	}
	struct node *ptr,*nptr,*ptr1;
	ptr=start;
	ptr1=new node();
    nptr=ptr->next;
    while(nptr!=NULL)
	{
		if(ptr==start)
		{
			e=nptr->x;
			b=nptr->y;
			nptr->x=ptr->x;
			nptr->y=ptr->y;
		}
		else
		{
			c=nptr->x;
			d=nptr->y;
			nptr->x=e;
			nptr->y=b;
			e=c;
			b=d;
		}
		ptr=ptr->next;
		nptr=ptr->next;
	}
	ptr->next=ptr1;
	ptr1->next=NULL;
	ptr1->ch='E';
	if(ptr!=start)
	ptr->ch='<';
	ptr1->x=c;
	ptr1->y=d;
}
void change2(struct node *start)
{
	int e,b,c,d,i,j;
	if(start->next==NULL)
	{
		cout<<"Game over score="<<score<<endl;
		exit(0);
	}
	if(start->next->ch=='E')
	{
		start->next=NULL;
	}
	for(i=0;i<size;i++)
    {
    	for(j=0;j<size;j++)
    	{
    		a[i][j]=' ';
		}
	}
	struct node *ptr,*nptr,*ptr1;
	ptr=start;
	ptr1=new node();
    nptr=ptr->next;
    if(start->next!=NULL)
    {
    while(nptr->next!=NULL)
	{
		if(ptr==start)
		{
			e=nptr->x;
			b=nptr->y;
			nptr->x=ptr->x;
			nptr->y=ptr->y;
		}
		else
		{
			c=nptr->x;
			d=nptr->y;
			nptr->x=e;
			nptr->y=b;
			e=c;
			b=d;
		}
		ptr=ptr->next;
		nptr=ptr->next;
	}
	ptr->ch='E';
	ptr->next=NULL;
	}
}
int movement(struct node *start,struct food *f,struct poison *p)
{
	struct node *ptr,*mark,*mark1;
	char ch;
	cin>>ch;
	if(ch=='w')
	{
		if(a[start->x-1][start->y]=='*')
		{
			change(start);
			start->x=size-2;
		}
		else
		{
			change(start);
			start->x=start->x-1;
		}
	}
	if(ch=='s')
	{
		if(a[start->x+1][start->y]=='*')
		{
			change(start);
			start->x=1;
		}
		else
		{
			change(start);
			start->x=start->x+1;
		}
	}
	if(ch=='a')
	{
		if(a[start->x][start->y-1]=='*')
		{
			change(start);
			start->y=size-2;
		}
		else
		{
			change(start);
			start->y=start->y-1;
		}
	}
	if(ch=='d')
	{
		if(a[start->x][start->y+1]=='*')
		{
			change(start);
			start->y=1;
		}
		else
		{
			change(start);
			start->y=start->y+1;
		}
	}
	if(ch=='q')
	{
		e:
		cout<<"Press s to save and quit or q to quit without save"<<endl;
		cin>>ch;
		if(ch=='s')
		{
		struct node* heads;heads=start;
		char data[100],i=-1,food1[100];
		ofstream outfile;
		outfile.open("snakesave.txt");
		itoa(score,data,10);
		outfile<<data<<"-";
		itoa(size,data,10);
		outfile<<data<<"-";
		itoa(f->x,data,10);
		outfile<<data<<"-";
		itoa(f->y,data,10);
		outfile<<data<<"-";
		itoa(p->x,data,10);
		outfile<<data<<"-";
		itoa(p->y,data,10);
		outfile<<data<<"-";
		while(heads->next!=NULL)
		{
			itoa(heads->x,data,10);
			outfile<<data<<"-";
			itoa(heads->y,data,10);
			outfile<<data<<"-";
			heads=heads->next;
		}
		itoa(heads->x,data,10);
		outfile<<data<<"-";
		itoa(heads->y,data,10);
		outfile<<data<<"\0";
		heads=heads->next;
		outfile.close();
		cout<<"Saved!"<<endl;
		exit(0);
		}
		else if(ch=='q')
		exit(0);
		else
		{
			cout<<"wrong input"<<endl;
			goto e;
		}
	}
	if(f->x==start->x && f->y==start->y)
	{
	change1(start);
	if(ch=='w')
	{
		start->x=start->x-1;
	}
	if(ch=='s')
	{
		start->x=start->x+1;
	}
	if(ch=='a')
	{
		start->y=start->y-1;
	}
	if(ch=='d')
	{
		start->y=start->y+1;
	}
	f->x=rand()%(size-4)+2;
	f->y=rand()%(size-4)+2;
	//mark1=start;
	score+=1;
	}
	else if(p->x==start->x && p->y==start->y)
	{
	change2(start);
	if(ch=='w')
	{
		if(a[start->x-1][start->y]=='*')
		{
			start->x=size-2;
		}
		else
		{
			start->x=start->x-1;
		}
	}
	if(ch=='s')
	{
		if(a[start->x+1][start->y]=='*')
		{
			start->x=1;
		}
		else
		{
			start->x=start->x+1;
		}
	}
	if(ch=='a')
	{
		if(a[start->x][start->y-1]=='*')
		{
			start->y=size-2;
		}
		else
		{
			start->y=start->y-1;
		}
	}
	if(ch=='d')
	{
		if(a[start->x][start->y+1]=='*')
		{
			start->y=1;
		}
		else
		{
			start->y=start->y+1;
		}
	}
	p->x=rand()%(size-4)+2;
	p->y=rand()%(size-4)+2;
	score-=1;
	}
	mark=start->next;
	display(start,f,p);
	while(mark!=NULL)
	{
		if(start->x==mark->x && start->y==mark->y)
		{
			cout<<"Game Over   Score = "<<score<<endl;
			return 0;
		}
		mark=mark->next;
	}
	movement(start,f,p);
}
int main()
{
	srand(time(NULL));
	char ch,loadata[500];
	int i,j,num;i=j=0;
	c:
	cout<<"Enter n for new and l for load"<<endl;
	cin>>ch;
	struct node *start;struct food *f;struct poison *p;
	f=new food();
	p=new poison();
	if(ch=='n')
	{
	int length;
	cout<<"Enter length greater than 1 and smaller than size-2 && sizeof array"<<endl;
	cin>>length>>size;
	while(length<2 && length>size-2)
	{
		cout<<"wrong input"<<endl;
		cin>>length>>size;
	}
	start=list(length);
	f->x=rand()%(size-4)+2;
	f->y=rand()%(size-4)+2;
	p->x=rand()%(size-4)+2;
	p->y=rand()%(size-4)+2;
	display(start,f,p);
	movement(start,f,p);
	}
	else if(ch=='l')
	{
		ifstream check("snakesave.txt");
		if(check)
		{
		ifstream infile;
		infile.open("snakesave.txt");
		infile>>loadata;
		while(loadata[i]!='-' || j==0)
		{
			if(loadata[0]=='-')
			i=i+1;
			score=score*10+((int)(loadata[i])-48);
			i=i+1;j=1;
		}i=i+1;
		if(loadata[0]=='-')
		score=score-(2*score);
		while(loadata[i]!='-')
		{
			
			size=size*10+((int)(loadata[i])-48);
			i=i+1;	
		}i=i+1;
		while(loadata[i]!='-')
		{
			f->x=f->x*10+((int)(loadata[i])-48);
			i=i+1;	
		}i=i+1;
		while(loadata[i]!='-')
		{
			f->y=f->y*10+((int)(loadata[i])-48);
			i=i+1;	
		}i=i+1;
		while(loadata[i]!='-')
		{
			p->x=p->x*10+((int)(loadata[i])-48);
			i=i+1;	
		}i=i+1;	
		while(loadata[i]!='-')
		{
			p->y=p->y*10+((int)(loadata[i])-48);
			i=i+1;	
		}i=i+1;	
		start=snakeload(loadata,i);
		display(start,f,p);
		movement(start,f,p);
		}
		else
		{
			cout<<"No Saved File Yet!"<<endl;
			goto c;
	    }
	}
	else
	{
		cout<<"wrong input"<<endl;
		goto c;
	}
	return 0;
}
