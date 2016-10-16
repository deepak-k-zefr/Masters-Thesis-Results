// Code for visualization of microstructure
//Input  3d array matrix of grain configuration
//read in the configuration array and 
// print out a binary matrix for visualization in IDL
using namespace std;

#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>

#define rank0 100
#define rank1 100
#define rank2 100

int config[rank0][rank1][rank2];


int main(){
  //int n_dim = 3;

  //int rank[n_dim];
  //cout<<"specificy system size: "<<endl;


  /*
  for(int i=0; i<n_dim; i++)
    {
      cout<<"rank_"<<i<<" = ";
      cin>>rank[i];
    } 
  */
  //the material microstructure...
  
 ofstream fout;
 ifstream fin;
 fin.open("initial.doc");
  
  int tempI, tempJ, tempK;
  double val;

 
  for(int i=0; i<rank0; i++)
    {for(int j=0; j<rank1; j++)
     { for(int k=0; k<rank2; k++)
	{
	  fin>>tempI>>tempJ>>tempK;

	  
cout<<"tempI : "<<tempI<<"  i: "<<i<<endl;
cout<<"tempJ : "<<tempJ<<"  j: "<<j<<endl;
cout<<"tempK : "<<tempK<<"  k: "<<k<<endl;
	
	  
	  
	  fin>>val;
	  //cout<<val<<endl;

	  //if(val>150)
	  config[tempI][tempJ][tempK] = (int)floor(val);
	  //else 
	  //config[tempI][tempJ][tempK] = 0;

	  //print out a particular binary slice...
/*	  if(i==10)
	    {
	      if(val>150)
		fout<<j<<" "<<k<<endl;
	     
	    }*/
	  
	 
	}}}
  fout.close();

  fin.close();

  /*
  //now print out the binary configuration...
  FILE* pFile;
  pFile = fopen("3d_material.dat","wb");
  fwrite(config, sizeof(config[0][0][0]), sizeof(config), pFile);
  fclose(pFile);
  */


  
  fout.open("initial.vtk");

  fout<<"# vtk DataFile Version 2.0"<<endl;
  fout<<"Volume example"<<endl;
  fout<<"ASCII"<<endl;
  fout<<"DATASET STRUCTURED_POINTS"<<endl;
  fout<<"DIMENSIONS "<<rank2<<" "<<rank1<<" "<<rank0<<endl;
  fout<<"ASPECT_RATIO 1 1 1"<<endl;
  fout<<"ORIGIN 0 0 0"<<endl;
  fout<<"POINT_DATA "<<(rank2)*(rank1)*(rank0)<<endl;
  fout<<"SCALARS volume_scalars UNSIGNED_CHAR 1"<<endl;
  fout<<"LOOKUP_TABLE default"<<endl;

  for(int i=0; i<rank0; i++)
    for(int j=0; j<rank1; j++)
      for(int k=0; k<rank2; k++)
	{
	  fout<<config[i][j][k]<<endl;
	cout<<config[i][j][k];
}

  fout.close();

return 0;
}
