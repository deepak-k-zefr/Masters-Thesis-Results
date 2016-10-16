//Potts Model reorientaion for Grain Growth
#include<iostream>
#include<fstream>
#include<time.h>
#include<string.h>
#include<cstdlib>
#include<math.h>
using namespace std;

int main()
{
 srand(time(NULL));

int i;
// Coordinates of 100 seeds
   double x[100];
   double y[100];
   double z[100];

    for(i=0;i<100;i++)
    {
        x[i]=(double)(rand()%100);
        y[i]=(double)(rand()%100);
        z[i]=(double)(rand()%100);
        cout<<x[i]<<","<<y[i]<<","<<z[i]<<endl;
     
    }

int a,b,c,d,w,e,r,index1=0;
// initial assigning of all voxels as '0'

int N[100][100][100];
int A[100][100][100];
for(b=0; b<100;b++)
   for(c=0;c<100;c++)
    for(d=0;d<100;d++)
{
    N[b][c][d]=0;

}



double dist,small=1000;
//planting the seeds
for(a=0; a<100;a++)
   {
w=x[a];
e=y[a];
r=z[a];
N[w][e][r]=a;
}


//Finding shortest seed for each voxel
for(b=0; b<100;b++)
    {
   for(c=0;c<100;c++)
     {
      for(d=0;d<100;d++)
        {
    for(e=0;e<100;e++)
    {
     dist= sqrt(pow(b-x[e],2) + pow(c-y[e],2)+pow(d-z[e],2));

     if    (small>dist )
    {
        small=dist;
    index1=e;

    }
    N[b][c][d]=index1;
     
    }
    small=1000; 

}
}
}


// initial structure in a file according to format
ofstream file2;
file2.open("initial.doc");
for(b=0; b<100;b++)
{

   for(c=0;c<100;c++)
    {

    for(d=0;d<=100;d++)
{
A[b][c][d]=N[b][c][d];
  file2<<b<<" "<<c<<" "<<" "<<d<<" "<<N[b][c][d] <<"   "<<endl;

}

    }
    }
    
file2.close();

int h=0;
for(b=0; b<100;b++)
    {
   for(c=0;c<100;c++)
     {
      for(d=0;d<100;d++)
        {

 if (((N[b][c][d]!=N[b+1][c][d]) ||  (N[b][c][d]!=N[b][c+1][d]) || (N[b][c][d]!=N[b][c][d+1]) || (N[b][c][d]!=N[b-1][c][d]) ||  (N[b][c][d]!=N[b][c-1][d]) || (N[b][c][d]!=N[b][c][d-1]) ||(N[b][c][d]!=N[b+1][c+1][d] )|| (N[b][c][d]!=N[b-1][c-1][d] )||(N[b][c][d]!=N[b][c+1][d+1] )||(N[b][c][d]!=N[b][c-1][d-1] )||(N[b][c][d]!=N[b+1][c][d+1] )|| (N[b][c][d]!=N[b-1][c][d-1] )|| (N[b][c][d]!=N[b+1][c-1][d] ) ||(N[b][c][d]!=N[b-1][c+1][d] )|| (N[b][c][d]!=N[b][c+1][d-1] )||(N[b][c][d]!=N[b][c-1][d+1] )||(N[b][c][d]!=N[b+1][c][d-1] )
|| (N[b][c][d]!=N[b-1][c][d+1] )) && ((b!=100) && (c!=100) && (d!=100) && (b!=0) && (c!=0) && (d!=0)))
{
 
N[b][c][d]=0;
h++;
   }

}}
   }
cout<<"h(Grain boundary points) is before orientation:"<<h<<endl;


//Potts Model reorientaion
int index[100]; 
int count=0,change=0,nochange=0;
double e_n,e_temp,temp=0;
ofstream file1;
file1.open("final.doc");

int allcount=0;
while(count!=100000)
{


b=(rand()%100); 
c=(rand()%100);
d=(rand()%100);

allcount++;
if (((N[b][c][d]!=N[b+1][c][d]) ||  (N[b][c][d]!=N[b][c+1][d]) || (N[b][c][d]!=N[b][c][d+1]) || (N[b][c][d]!=N[b-1][c][d]) ||  (N[b][c][d]!=N[b][c-1][d]) || (N[b][c][d]!=N[b][c][d-1]) ||(N[b][c][d]!=N[b+1][c+1][d] )|| (N[b][c][d]!=N[b-1][c-1][d] )||(N[b][c][d]!=N[b][c+1][d+1] )||(N[b][c][d]!=N[b][c-1][d-1] )||(N[b][c][d]!=N[b+1][c][d+1] )|| (N[b][c][d]!=N[b-1][c][d-1] )|| (N[b][c][d]!=N[b+1][c-1][d] ) ||(N[b][c][d]!=N[b-1][c+1][d] )|| (N[b][c][d]!=N[b][c+1][d-1] )||(N[b][c][d]!=N[b][c-1][d+1] )||(N[b][c][d]!=N[b+1][c][d-1] )
|| (N[b][c][d]!=N[b-1][c][d+1] )) && ((b!=100) && (c!=100) && (d!=100) && (b!=0) && (c!=0) && (d!=0)))
{


i=0;
memset(index, 0, sizeof(index));
temp=N[b][c][d];
 count++;
e_n=0;
if (N[b][c][d]!=N[b+1][c][d] )
      {
index[i]=N[b+1][c][d];
i++;
e_n=e_n+1;
}
if (N[b][c][d]!=N[b][c+1][d] )
      {
index[i]=N[b][c+1][d];
i++;
e_n=e_n+1;
}
if (N[b][c][d]!=N[b][c][d+1] )
      {
index[i]=N[b][c][d+1];
i++;
e_n=e_n+1;
}
if (N[b][c][d]!=N[b-1][c][d] )
      {
index[i]=N[b-1][c][d];
i++;
e_n=e_n+1;
}
if (N[b][c][d]!=N[b][c-1][d] )
      {
index[i]=N[b][c-1][d];
i++;
e_n=e_n+1;
}
if (N[b][c][d]!=N[b][c][d-1] )
      {
index[i]=N[b][c][d-1];
i++;
e_n=e_n+1;
}

if (N[b][c][d]!=N[b+1][c+1][d] )
      {
index[i]=N[b+1][c+1][d];
i++;
e_n=e_n+1;
}

if (N[b][c][d]!=N[b-1][c-1][d] )
      {
index[i]=N[b-1][c-1][d];
i++;
e_n=e_n+1;
}

if (N[b][c][d]!=N[b][c+1][d+1] )
      {
index[i]=N[b][c+1][d+1];
i++;
e_n=e_n+1;
}

if (N[b][c][d]!=N[b][c-1][d-1] )
      {
index[i]=N[b][c-1][d-1];
i++;
e_n=e_n+1;
}

if (N[b][c][d]!=N[b+1][c][d+1] )
      {
index[i]=N[b+1][c][d+1];
i++;
e_n=e_n+1;
}

if (N[b][c][d]!=N[b-1][c][d-1] )
      {
index[i]=N[b-1][c][d-1];
i++;
e_n=e_n+1;
}

if (N[b][c][d]!=N[b+1][c-1][d] )
      {
index[i]=N[b+1][c-1][d];
i++;
e_n=e_n+1;
}

if (N[b][c][d]!=N[b-1][c+1][d] )
      {
index[i]=N[b-1][c+1][d];
i++;
e_n=e_n+1;
}


if (N[b][c][d]!=N[b][c+1][d-1] )
      {
index[i]=N[b][c+1][d-1];
i++;
e_n=e_n+1;
}

if (N[b][c][d]!=N[b][c-1][d+1] )
      {
index[i]=N[b][c-1][d+1];
i++;
e_n=e_n+1;
}

if (N[b][c][d]!=N[b+1][c][d-1] )
      {
index[i]=N[b+1][c][d-1];
i++;
e_n=e_n+1;
}
if (N[b][c][d]!=N[b-1][c][d+1] )
      {
index[i]=N[b-1][c][d+1];
i++;
e_n=e_n+1;
}


index1=rand()%(i+1);
N[b][c][d]=index[index1];

e_temp=0;

if (N[b][c][d]!=N[b+1][c][d] )
{	e_temp=e_temp+1;
}
if (N[b][c][d]!=N[b][c+1][d] )
{	e_temp=e_temp+1;
}
if (N[b][c][d]!=N[b][c][d+1] )
{	e_temp=e_temp+1;
}
if (N[b][c][d]!=N[b-1][c][d] )
{	e_temp=e_temp+1;
}
if (N[b][c][d]!=N[b][c-1][d] )
{	e_temp=e_temp+1;
}
if (N[b][c][d]!=N[b][c][d-1] )
{	e_temp=e_temp+1;
}
if (N[b][c][d]!=N[b+1][c+1][d] )
 {	e_temp=e_temp+1;
}    

if (N[b][c][d]!=N[b-1][c-1][d] )
{	e_temp=e_temp+1;
}      
if (N[b][c][d]!=N[b][c+1][d+1] )
{	e_temp=e_temp+1;
}      
if (N[b][c][d]!=N[b][c-1][d-1] )
{	e_temp=e_temp+1;
}     
if (N[b][c][d]!=N[b+1][c][d+1] )
{	e_temp=e_temp+1;
}     
if (N[b][c][d]!=N[b-1][c][d-1] )
{	e_temp=e_temp+1;
}    
if (N[b][c][d]!=N[b+1][c-1][d] )
{	e_temp=e_temp+1;
}    
if (N[b][c][d]!=N[b-1][c+1][d] )
{	e_temp=e_temp+1;
}    
if (N[b][c][d]!=N[b][c+1][d-1] )
{	e_temp=e_temp+1;
}      
if (N[b][c][d]!=N[b][c-1][d+1] )
{	e_temp=e_temp+1;
}      
if (N[b][c][d]!=N[b+1][c][d-1] )
{	e_temp=e_temp+1;
}     
if (N[b][c][d]!=N[b-1][c][d+1] )
{	e_temp=e_temp+1;
}     


double r1=((double)rand() / (double)(RAND_MAX)) ;

double p=exp(2*(e_n-e_temp));


if (e_n<=e_temp && p<r1)
{
 nochange++;
//cout<<"No reorientaion because of increase in energy:"<<endl;
//cout<<"e_n and e-temp is    "<<e_n<<"    "<<e_temp<<"   probabilty and random number  "<<p<<"    "<<r1<<endl;
N[b][c][d]=temp;
}
else
{
change++;
}
/*
cout<<"reorientaion takes place because of decrease in energy:"<<endl;
cout<<"e_n and e-temp is   "<<e_n<<"  "<<e_temp<<"probabilty and random number  "<<p<<"     "<<r1<<endl;
}*/
}
}


int h=0;
int gbx[1000000],gby[1000000],gbz[1000000],vacancy[100];
for(b=0; b<100;b++)
    {
   for(c=0;c<100;c++)
     {
      for(d=0;d<100;d++)
        {

 if (((N[b][c][d]!=N[b+1][c][d]) ||  (N[b][c][d]!=N[b][c+1][d]) || (N[b][c][d]!=N[b][c][d+1]) || (N[b][c][d]!=N[b-1][c][d]) ||  (N[b][c][d]!=N[b][c-1][d]) || (N[b][c][d]!=N[b][c][d-1]))
      && (N[b+1][c][d]!=0) && (N[b][c+1][d]!=0) && (N[b][c][d+1]!=0) && (N[b-1][c][d]!=0) &&  (N[b][c-1][d]!=0)  && (N[b][c][d-1]!=0) &&   (c!=100) && (d!=100) && (b!=0) && (c!=0) && (d!=0))
{
 
//N[b][c][d]=0;
gbx[h]=b;
gby[h]=c;
gbz[h]=d;
h++;
   }
else
{
//N[b][c][d]=1;
}

}}
   }

int v;
//Picking 100 vacancies
 for(i=0;i<100;i++)
    {
        vacancy[i]=(int)(rand()%h);
         v=vacancy[i];
          b=gbx[v],c=gby[v],d=gbz[v];   
        N[b][c][d]=-1;    
}


cout<<"Number of grains with 0 index after orientation :"<<h<<endl;


cout<<" Number of reorientations :"<<change<<endl;
cout<<" Number of failed attempts :"<<nochange<<endl;
cout<<" Probabilty of Success   :"<<double((double)change/(double)(nochange+change))<<endl;

ofstream file3;
file3.open("voxels1.xls");

for(b=0; b<100;b++)
   for(c=0;c<100;c++)
    for(d=0;d<100;d++)
{
  file1<<b<<" "<<c<<" "<<" "<<d<<" "<<N[b][c][d] <<"   "<<endl;
  }

//int d1=0,c1=0;
int temp1;
int old [100];
int new1[100];
memset(old, 0, sizeof(old));
memset(new1, 0, sizeof(new1));
for(b=0; b<100;b++)
   for(c=0;c<100;c++)
    for(d=0;d<100;d++)
{
  /*if(A[b][c][d]!=N[b][c][d])
{c1++;}
 else
{ d1++;}
*/
temp1=N[b][c][d];
new1[temp1]++;
temp1=A[b][c][d];
old[temp1]++;

}


file3<<"     OLD Values  "<<"      NEW values"<<endl;
for (b=0;b<100;b++)
{

file3<<"for"<<b<<"=  "<<old[b]<<"       "<<new1[b]<<endl;

}

//cout<<"Similar values:   "<<d1<<endl;
//cout<<"Disimilar values:   "<<c1<<endl;
cout<<" Total attempts: "<<allcount<<endl;
/*int foo= sizeof(N)/sizeof(int);
cout<<"Size of N"<<foo<<endl;
foo= sizeof(A)/sizeof(int);
cout<<"Size of N"<<foo<<endl;
file3.close(); 
file1.close();
*/

}



