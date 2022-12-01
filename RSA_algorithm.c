#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#define R 25
#define L 2
#define ITERATION 15

int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i;
 
char msg[100];

void ce();
 
long int cd(long int);
 
void encrypt();
 
void decrypt();

long long mulmod(long long a, long long b, long long mod)
{
    long long x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {    
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}



long long modulo(long long base, long long exponent, long long mod)
{
    long long x = 1;
    long long y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}
 


int Miller(long long p,int iteration)
{
 
    int i=0;
    long long s;
    if (p < 2)
    {
        return 0;
    }
    if (p != 2 && p % 2==0)
    {
        return 0;
    }
     s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    srand(time(0));
    for (i = 0; i < iteration; i++)
    {   
        long long a = rand() % (p - 1) + 1, temp = s;
        long long mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return 0;
        }
    }
    return 1;
}

void changestr(char str[], int n)
{
    str[n] = '|';
}

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds)
		;
}

void loader()
{
    int i, j, n = 0;
    char str[] = "                                                 ";
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\t\t\t\t\t\t\t>--RSA PORTAL--<\n");
    printf("\n\t\t\t\t\t\t\t\t-----LOADING-----\n");
    printf("\n");
    for(i = 0 ; i < 50 ; i++)
    {
        printf("\r\t\t\t\t\t\t[%-50s]", str);
        changestr(str, n);
        n++;
        delay(100);
    }
    printf("\n\n\t\t\t\t\t\t\t press Enter to start the RSA PORTAL");
    getchar();
    return;
}

void main() {
    loader();
    system("clear");
     

   srand(time(0));
   bool mycontinue = true;
   while(mycontinue){
       p=(rand() % (R - L + 1)) + L;
       q=(rand() % (R - L + 1)) + L;
       if(Miller(p,ITERATION) && Miller(q,ITERATION) && p!=q)
            mycontinue=false;
   }

 
	system("clear");
	printf("\nENTER MESSAGE\n");
 
	fflush(stdin);
 
	scanf("%s",msg);
 
	for (i=0;msg[i]!='\0';i++)
 
	m[i]=msg[i];
 
	n=p*q;
 
	t=(p-1)*(q-1);
 
	ce();

 
	encrypt();
 
	decrypt();
 
	getch();
 
}

 
void ce() {
 
	int k;
 
	k=0;
 
	for (i=2;i<t;i++) {
 
		if(t%i==0)
 
		    continue;
 
		flag=Miller(i,ITERATION);
 
		if(flag==1&&i!=p&&i!=q) {
 
			e[k]=i;
 
			flag=cd(e[k]);
 
			if(flag>0) {
 
				d[k]=flag;
 
				k++;
 
			}
 
			if(k==99)
 
			        break;
 
		}
 
	}
 
}
 
long int cd(long int x) {
 
	long int k=1;
 
	while(1) {
 
		k=k+t;
 
		if(k%x==0)
 
		    return(k/x);
 
	}
 
}
 
void encrypt() {
 
	long int pt,ct,key=e[0],k,len;
 
	i=0;
 
	len=strlen(msg);
 
	while(i!=len) {
 
		pt=m[i];
 
		pt=pt-96;
 
		k=1;
 
		for (j=0;j<key;j++) {
 
			k=k*pt;
 
			k=k%n;
 
		}
 
		temp[i]=k;
 
		ct=k+96;
 
		en[i]=ct;
 
		i++;
 
	}
 
	en[i]=-1;
 
	printf("\nTHE ENCRYPTED MESSAGE IS\n");
 
	for (i=0;en[i]!=-1;i++)
 
	printf("%c",en[i]);
 
}
 
void decrypt() {
 
	long int pt,ct,key=d[0],k;
 
	i=0;
 
	while(en[i]!=-1) {
 
		ct=temp[i];
 
		k=1;
 
		for (j=0;j<key;j++) {
 
			k=k*ct;
 
			k=k%n;
 
		}
 
		pt=k+96;
 
		m[i]=pt;
 
		i++;
 
	}
 
	m[i]=-1;
 
	printf("\nTHE DECRYPTED MESSAGE IS\n");
 
	for (i=0;m[i]!=-1;i++)
 
	printf("%c",m[i]);
 
}


