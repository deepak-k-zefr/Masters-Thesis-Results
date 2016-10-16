//100 elliptical grains

//colors chosen
//20= Grain
//1=Grain Boundary
//255=chosen grains near triple point
//50=void

//Potts Model reorientaion for Grain Growth
#include<iostream>
#include<fstream>
#include<time.h>
#include<string.h>
#include<cstdlib>
#include<math.h>
using namespace std;

static int gbx[1000000];
static int gby[1000000];
static int gbz[1000000];

int N[100][100][100];
int N1[100][100][100];
int N2[100][100][100];
int h=0;
int count0=0;
int ng=1000; int gbs=35; int times= ng+1000;
int exchange=0;
int exchange1=0;
int v_count;

double m,n,o;

////////////////////////////////////////////////MAIN FUNCTION///////////////////////////////////////////////////////////////////////////////////

int main()
{
  
  //srand (time(NULL));
  srand (333);
  printf ("Random number: %d\n", rand()%ng);
  
  // Coordinates of ng seeds
  double x[ng];
  double y[ng];
  double z[ng];
  int a,b,c,d,w,e,r,index1=0;
  
  
  ofstream fout;
  ifstream fin;
  int i;
  //////////////////////////////////////////SELECTING ng RANDOM GRAIN CENTERS///////////////////////////////
  for(i=0; i<ng; i++)
  {
    x[i]=(double)(rand()%100);
    y[i]=(double)(rand()%100);
    z[i]=(double)(rand()%100);
    cout<<x[i]<<","<<y[i]<<","<<z[i]<<endl;
  }
  
  
  
  //////////////////////////////////// initial assigning of all voxels as '0'
  
  for(b=0; b<100; b++)
    for(c=0; c<100; c++)
      for(d=0; d<100; d++)
      {
        N[b][c][d]=0;
      }
      double dist,small=1000;
  
  /////////////////////////////planting the seeds
  /*for(a=0; a<ng;a++)
  
  {w=x[a];e=y[a];r=z[a];N[w][e][r]=a;
  for(int i=-1;i<1;i++)
  for(int j=-1;j<1;j++)
  for(int k=-1;k<1;k++)
  {b=w;
  c=e;
  d=r;
  
  if((b+i>0)&&(c+j>0)&&(d+k>0)&&(b+i<100)&&(c+j<100)&&(d+k<100))
  N[w+i][e+j][r+k]=a;
  }
  }
  */
  
  //planting the seeds
  for(a=0; a<ng; a++)
  {
    w=x[a];
    e=y[a];
    r=z[a];
    N[w][e][r]=a;
  }
  
  
  
  /////////////////////////////////////////////Finding shortest seed for each voxel
  for(b=0; b<100; b++)
    for(c=0; c<100; c++)
      for(d=0; d<100; d++)
      {
        for(e=0; e<ng; e++)
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
      
      int b1,c1,d1;
  int volume[ng];
  for(b1=0; b1<ng; b1++)
    volume[b1]=0;
  for(b1=0; b1<100; b1++)
    for(c1=0; c1<100; c1++)
      for(d1=0; d1<100; d1++)
      {
        for(d=0; d<ng; d++)
        {
          
          if (d==N[b1][c1][d1])
            volume[d]++;
        }
      }
      
      ///////////////////////////// initial structure in a file initial.doc
      ofstream file2;
  file2.open("initial.doc");
  for(b=0; b<100; b++)
    for(c=0; c<100; c++)
      for(d=0; d<100; d++)
      {
        
        file2<<b<<" "<<c<<" "<<" "<<d<<" "<<N[b][c][d]*10 <<"   "<<endl;
      }
      
      file2.close();
  cout<<"INITAL STRUCTURE COPIED"<<endl;
  
  
  //////////////////////////////////////Grain volume of each grains
  fout.open("count500.doc");
  int sum=0;
  for(b=0; b<ng; b++)
  {
    fout<<b<<"           "<<volume[b]<<endl;
    sum=sum+volume[b];
  }
  
  cout<<"total sum is"<<sum<<endl;
  
  
  
  ////////////////////////////////////////////////////creating binary structure
  //double layer grain boundary is 1 rest are 20
  //gbx,gby,gbz stores all the grain boundary coordinates
  for(b=1; b<100; b++)
    for(c=1; c<100; c++)
      for(d=1; d<100; d++)
      {
        for(int i=-1; i<1; i++)
          for(int j=-1; j<1; j++)
            for(int k=-1; k<1; k++)
            {
              if(N[b][c][d]!=N[b+i][c+j][d+k])
              {
                gbx[h]=b;
                gby[h]=c;
                gbz[h]=d;
                h++;
                break;
              }
            }
      }
      
      // h is the length of number grain boundary voxels out of 10^6
      cout<<"number of Grain Boundary pixels "<<h<<endl;
  // storing 1 at  grain boundary values
  
  for(int i=0; i<h; i++)
  {
    b=gbx[i];
    c=gby[i];
    d=gbz[i];
    N[b][c][d]=1;
  }
  // storing 20 at non grain boundary values
  for(b=0; b<100; b++)    for(c=0; c<100; c++)       for(d=0; d<100; d++)
  {
    if (N[b][c][d]!=1)
    {
      N[b][c][d]=20;
    }
  }
  
  
  
  //////////////////////////////////////////////Remove Grain Boundary Issues
  
  int tmax,t;
  
  for(int b=1; b<100; b++)
    for(int c=1; c<100; c++)
      for(int d=1; d<100; d++)
      {
        
        t=0;
        for(int i=-10; i<10; i++)
          for(int j=-10; j<10; j++)
            for(int k=-10; k<10; k++)
            {
              if((b+i>0)&&(c+j>0)&&(d+k>0)&&(b+i<100)&&(c+j<100)&&(d+k<100))
                if(N[b+i][c+j][d+k]==1)//check if neighbor is a GB
                {
                  t++;
                  
                  //cout<<t<<endl;
                  
                }
            }
            
            
            if(t>tmax)// large grain boundary area
            {
              tmax=t;
              b1=b;
              c1=c;
              d1=d;
              if (tmax>7000)
                goto L13;
            }
      }
      
      L13:
        
        cout<<"tmax is       "<<tmax<<endl<<b1<<"     "<<c1<<"     "<<d1<<endl;
  
  
  for(int i=-80; i<80; i++)
    for(int j=-80; j<80; j++)
      for(int k=-80; k<80; k++)
        
      {
        
        if((b1+i+1>0)&&(c1+j+1>0)&&(d1+k+1>0)&&(b1+i+1<100)&&(c1+j+1<100)&&(d1+k+1<100))
          if((N[b1+i+1][c1+j+1][d1+k+1]!=20) && (N[b1+i+1][c1+j][d1+k]!=20) &&(N[b1+i][c1+j+1][d1+k]!=20) &&(N[b1+i][c1+j][d1+k+1]!=20) &&(N[b1+i+1][c1+j+1][d1+k]!=20) &&(N[b1+i][c1+j+1][d1+k+1]!=20) &&(N[b1+i+1][c1+j][d1+k+1]!=20)
               && (N[b1+i-1][c1+j-1][d1+k-1]!=20) && (N[b1+i-1][c1+j][d1+k]!=20) &&(N[b1+i][c1+j-1][d1+k]!=20) &&(N[b1+i][c1+j][d1+k-1]!=20) &&(N[b1+i-1][c1+j-1][d1+k]!=20) &&(N[b1+i][c1+j-1][d1+k-1]!=20) &&(N[b1+i-1][c1+j][d1+k-1]!=20))
            
            N[b1+i][c1+j][d1+k]=200;
          
      }
      
      
      
      for(b=0; b<100; b++)
        for(c=0; c<100; c++)
          for(d=0; d<100; d++)
          {
            if (N[b][c][d]==200)
            {
              N[b][c][d]=20;
            }
          }
          
          ofstream binary;
  binary.open("Binary.doc");
  for(b=0; b<100; b++)
    for(c=0; c<100; c++)
      for(d=0; d<100; d++)
      {
        binary<<b<<" "<<c<<" "<<" "<<d<<" "<<N[b][c][d] <<"   "<<endl;
      }
      binary.close();
  
  cout<<"Binary files copied"<<endl;
  
  int dir;
  double dotpro[27];//a grain can have 27 possible GB nerighbors
  //int t=0;// vount of GB neighbors
  int success=0;
  int gx[20],gy[20],gz[27];//keep a track of GB neighbors locations
  //int times=10; //number of runs
  int count1=0;
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////find a triple point. How to fond a triple point?
  //triple point has maximum number of GB neighbors
  
  int x1,y1,z1;
  
  for(int b1=5; b1<100; b1++)
    for(int c=5; c<100; c++)
      for(int d=5; d<10; d++)
      {
        
        t=0;
        for(int i=-1; i<2; i++)
          for(int j=-1; j<2; j++)
            for(int k=-1; k<2; k++)
            {
              if(N[b1+i][c+j][d+k]==1)//check if neighbor is a GB
              {
                t++;
                //cout<<t<<endl;
              }
            }
            
            
            if(t>20)// triple boundary;
              {
              cout<<"           "<<b1<<"         "<<c<<"            "<<d<<endl;
              cout<<"found  a triple point";
              x1=b1;
              y1=c;
              z1=d;
              cout<<"           "<<b1<<"         "<<c<<"            "<<d<<endl;
              goto L1;
              }
      }
      
      L1:
        cout<<"           "<<x1<<"         "<<y1<<"            "<<z1<<endl;
  int t1=t;
  
  
  //////////////////////////////////count GB in n2
  
  int countgb=0;
  for(b=0; b<100; b++)
    for(c=0; c<100; c++)
      for(d=0; d<100; d++)
      {
        if(N[b][c][d]==1)
        {
          N2[b][c][d]=1;
          countgb++;
        }
      }
      
      cout<<"countgb is  "<<countgb<<endl;
  
  
  x1=5;
  y1=7;
  z1=5;
  
  
  
  
  
  
  
  
  
  
  //////////////////////////////////////////////////////////////////////////// Tin diffusion along the grain boundaries
  ////KMC process
  int count5=0;
  int tin_x[100];
  int tin_y[100];
  int tin_z[100];
  int tin_x1[100];
  int tin_y1[100];
  int tin_z1[100];
  //times=10;
  double prob,r_num;
  t=0;
  int success1[35];
  /////////////////////////////finding 35 grains in 125 neighbors of triple point
  ///need to make sure that they have atleast one GB neighbor
  
  
  for(int i=-2; i<=2; i++)
    for(int j=-2; j<=2; j++)
      for(int k=-2; k<=2; k++)
      {
        if(x1+i>0 && x1+i<100 && y1+j>0 && y1+j<100 && z1+k>0 &&  z1+k<100)
          if(N[x1+i][y1+j][z1+k]==20)
          {
            /////////////Ensure the tin voxel chosen has atleast one GB neighbor
            for(int i1=-1; i1<2; i1++)
              for(int j1=-1; j1<2; j1++)
                for(int k1=-1; k1<2; k1++)
                {
                  if(N[x1+i+i1][y1+j+j1][z1+k+k1]==1)//check if neighbor is a GB
                  {
                    b=x1+i;
                    c=y1+j;
                    d=z1+k;
                    N[b][c][d]=255;// assign 255 for tin near triple point
                    N1[b][c][d]=255;
                    N2[b][c][d]=255;
                    tin_x[count5]=b;//keep track of all their locations
                    tin_y[count5]=c;
                    tin_z[count5]=d;
                    count5++; //initialy we consider only 35 tin atoms
                    cout<<" grain near triple point  "<<" count   "<<count5<<"  index  "<<x1+i<<"     "<<y1+j<<"    "<<z1+k<<"    "<<" GB for this grain  "<<"  index   "<<x1+i+i1<<"    "<<y1+j+j1<<"    "<<z1+k+k1<<"    "<<endl;
                    
                    goto L3;// if chosen grain has a GB go to next grain
                  }
                }
                L3:
                  //N[b][c][d]=100;
                  // giving 100 index to chosen grain
                  if (count5==gbs)// after  35 tin grains are found near original grain exit loop
                    goto L2;
          }
          
      }
      
      L2:
        ////////////////////////////After finding the 16 grains.They need to be diffused to the anode end.
        ////////////for each grain find a GB neighbor and diffuse one by one
        //Ensure chosen pixel is the chosen  grain
        
        //x1=5;
        //  y1=5;
        //z1=2;
        
        for(int a=0; a<35; a++)
        {
          tin_x1[a]=tin_x[a];
          tin_y1[a]=tin_y[a];
          tin_z1[a]=tin_z[a];
          
        }
      

          
        for(int a1=0; a1<times; a1++)
        {
          for(int a=0; a<35; a++) ////////////////////////////////////////// move each chosen sn grain induvidually 10 steps
          {
            if (N[tin_x[a]][tin_y[a]][tin_z[a]]==255)
            {
              //  cout<<"Grain number is        "<<a<<"     run number          "<<a1<<endl;
              count1++;
              for (int s1=0; s1<27; s1++) //////initilize all dot products as zero
              {
                dotpro[s1]=0;
                gx[s1]=0;
                gy[s1]=0;
                gz[s1]=0;
              }
              
              ///////////////////////checking 26 neighbors of chosen grain for grain boundaries
              for(int i=-1; i<2; i++)
                for(int j=-1; j<2; j++)
                  for(int k=-1; k<2; k++)
                  {
                    if(tin_x[a]+i>0 && tin_x[a]+i<100 && tin_y[a]+j>0 && tin_y[a]+j<100 && tin_z[a]+k>0 &&tin_z[a]+k<100)
                      if(N[tin_x[a]+i][tin_y[a]+j][tin_z[a]+k]==1)//check if neighbor is a GB
                      {
                        dotpro[t]=2*i;
                        t++;
                        gx[t]=i;
                        gy[t]=j;
                        gz[t]=k ;
                        
                      }
                  }
                  
                  //////////////////////////////////////Calculate scaling factor = sum of all the probability of jumping.
                  double  sum =0;
              for(int s1=0; s1<=t; s1++)
              {
                sum+=exp(dotpro[s1]);
              }
              dir=(int)(rand()%(26));
              if (dir>=t)
              {
                dir=(int)(rand()%(t+1));// pick a random direction
                prob=4*(exp(dotpro[dir]))/(sum);// calculate transition probability of jump
                r_num=((double)rand() / (double)(RAND_MAX));//divide it by scaling factor
                int x1=tin_x[a]+gx[dir];
                int y1=tin_y[a]+gy[dir];
                int z1=tin_z[a]+gz[dir];
                
                /////////////////////////////////////////////Exchange GB pixel and grain positions.
                ////also update tin position in diffusion tin matrix
                if(prob>r_num)
                {
                  //cout<<"      Number of grain boundary neighbors "<<t<< "   chosen GB "<<dir<<"  Dot product value  "<<dotpro[dir]<<"  Scaling factor "<<sum<<"   Transition probability   :"<<prob<<"  Random number chosen  "<<r_num<<"  success"<<endl;
                  //cout<<"old and new  "<<b<<"  "<<c<<"  "<<d<<"  "<<tin_x[a]+gx[dir]<<"  "<<c+gy[dir]<<"  "<<d+gz[dir]<<endl;
                  success1[a]++;
                  N[tin_x[a]][tin_y[a]][tin_z[a]]=1;// current  position = GB
                  N1[x1][y1][z1]=255;
                  N2[x1][y1][z1]=255;
                  N[x1][y1][z1]=255;//new position =grain
                  //cout<<N[tin_x[a]][tin_y[a]][tin_z[a]]<<"       "<<      N[tin_x[a]+gx[dir]][tin_y[a]+gy[dir]][tin_z[a]+gz[dir]]<<endl;
                  //cout<<N[tin_x[a]][tin_y[a]][tin_z[a]]<<"       "<<      N[x1][y1][z1]<<endl;
                  //cout<<"GRAIN Exchange SUCCESS    "<<tin_x[a]<<"      "<<tin_y[a]<<"      "<<tin_z[a]<<"      "<<"    index      "<<N[x1][y1][z1]<<"   new grain position assumed         "<<x1<<"    "<<y1<<"    "<<z1<<endl;
                  
                  tin_x[a]=x1;
                  tin_y[a]=y1;
                  tin_z[a]=z1;
                }}
              else
              {
                // cout<<" No GRAIN Exchange      "<<tin_x[a]+gx[dir]<<"      "<<tin_y[a]+gy[dir]<<"         "<<tin_z[a]+gz[dir]<< "          "<<N[tin_x[a]+gx[dir]][tin_y[a]+gy[dir]][tin_z[a]+gz[dir]]<<endl;
              }
              prob=0;
              r_num=0;
              t=0;
            }
            else
              
            {
              //   cout<<"                               condition not met   "<<tin_x[a]<<"      "<<tin_y[a]<<"         "<<tin_z[a]<< "          "<<N[tin_x[a]][tin_y[a]][tin_z[a]]<<endl;
              break;
            }
          }
          
          
         
          
        }
          
        
        
        
        for(int a=0; a<35; a++)
        {
          cout<< "Grain Number"<<a<<"     succesful attempts to diffuse      "<<success1[a]<<endl;
        }
        
        
        double displacement=0;
  double distance=0;
  
  for(int a=0; a<35; a++)
  {
    N2[tin_x[a]][tin_y[a]][tin_z[a]]=50;
    N[tin_x[a]][tin_y[a]][tin_z[a]]=50;//current position of grains=50
    cout<<"Grain number"<<a<<"   final positions  "<<tin_x[a]<<"      "<<tin_y[a]<<"         "<<tin_z[a]<< "          "<<N[tin_x[a]][tin_y[a]][tin_z[a]]<<endl;
    N2[tin_x1[a]][tin_y1[a]][tin_z1[a]]=150;//original posirtion of grains=void=150
    
    cout<<"Difference is   :"<<tin_x[a]-tin_x1[a]<<"     "<<tin_y[a]-tin_y1[a]<<"      "<<tin_z[a]-tin_z1[a]<<endl;
    
    displacement+=tin_x[a]-tin_x1[a];
    
    distance+= sqrt(pow(tin_x[a]-tin_x1[a],2) + pow(tin_y[a]-tin_y1[a],2)+pow(tin_z[a]-tin_z1[a],2));
    
  }
  
  
  
  
  
  
  
  
  
  
  
  cout<<"NET displacement is:     "<< (displacement/35)<<endl;
  cout<<"NET distance is:     "<< (distance/35)<<endl;        
  cout<<"NUMBER OF identfied grains(x,y,z less than 100)     ===       "<<count1<<endl;
  cout<<"NUMBER OF SUCCESsFUL transitions ===       "<<success<<endl;
  cout<<"The value of t1 is"<<t1<<endl;
  
  ofstream diffused;
  diffused.open("diff_structure.doc");
  for(int b=0; b<100; b++)
    for(int c=0; c<100; c++)
      for(int d=0; d<100; d++)
      {
        diffused<<b<<" "<<c<<" "<<" "<<d<<" "<<N2[b][c][d] <<"   "<<endl;
      }
      diffused.close();
  
}


