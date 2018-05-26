/********************************************************************\
* Laboratory Exercise COMP 7300/06                                   *
* Author: Group 18                                                   *
* Date  : November 30, 2017                                          *
* File  : myInitializeMatrix.c  for Lab3                             *
\*******************************************************************/


/********************************************************************\
*                    Global system headers                           *
\********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>

/******************************************************************\
*                  Global data types                               *
\******************************************************************/
typedef double          Timestamp;
typedef double          Period;

/**********************************************************************\
*                      Global definitions                              *
\**********************************************************************/
#define DIMENSION    	 40000
#define PRINTDIM         7 // Dimension of matrix to display
#define NUMBER_TESTS     7
#define ROWWISE          0 
#define COLUMNWISE       1

/**********************************************************************\
*                      Global data                              		*
\**********************************************************************/
Timestamp StartTime;
double    Matrix[DIMENSION][DIMENSION];
Period    Max[6],Min[6],Avg[6];
unsigned int MaxIndex[2],MinIndex[2];
/**********************************************************************\
*                        Function prototypes                           *
\**********************************************************************/
Timestamp   Now();
void        InitializeMatrixRowwise();
void        TransposeMatrix();
void        DisplayUpperQuandrant(unsigned dimension);

int main(){
  Timestamp StartInitialize;
  Period    testTime;
  unsigned int i,j,nbreTests;

  // Global Initialization
  StartTime       = Now();  

  nbreTests       = NUMBER_TESTS;
  Max[ROWWISE]    = 0.00;
  Max[COLUMNWISE] = 0.00;

  Min[ROWWISE]    = 10000.00;
  Min[COLUMNWISE] = 10000.00;

  Avg[ROWWISE]    = 0.00;
  Avg[COLUMNWISE] = 0.00;

  // Matrix Initialization
  printf("Be patient! Initializing............\n\n");
  for (j = 1; j <= nbreTests; j++){
    for (i = ROWWISE; i <= COLUMNWISE; i++){
      StartInitialize = Now(); //Begin the clock
	InitializeMatrixRowwise();  //Initialize Matrix row wise
	TransposeMatrix(); //Transpose the initialize matrix
       testTime = Now() - StartInitialize;  //Get the duration took by both the functions
      if (testTime > Max[i]){		//Calculate max time and min time and index generating them
	Max[i] = testTime;
	MaxIndex[i] = j;
      }
      if (testTime < Min[i]){
        Min[i] = testTime;
	MinIndex[i] = j;
      }
      Avg[i] += testTime;
    }
    printf("%3d: Initialize & Transpose Time Max[%2d]=%7.6f Min[%2d]=%7.6f Avg=%7.6f\n", 			//Display the max time, min time and averages
	   j,MaxIndex[ROWWISE],Max[ROWWISE],MinIndex[ROWWISE],
	   Min[ROWWISE],Avg[ROWWISE]/j);
    DisplayUpperQuandrant(PRINTDIM);
  }
}



/*********************************************************************\
 * Input    : None                                                    *
 * Output   : Returns the current system time                         *
\*********************************************************************/
Timestamp Now(){
  struct timeval tv_CurrentTime;
  gettimeofday(&tv_CurrentTime,NULL);
  return( (Timestamp) tv_CurrentTime.tv_sec + (Timestamp) tv_CurrentTime.tv_usec / 1000000.0-StartTime);
}


/*********************************************************************\                   
* Input    : None                                                     *                                
* Output   : None                                                     * 
* Function : Initialize a matrix rowwise                              *            
\*********************************************************************/
void      InitializeMatrixRowwise(){
 int i,j;
  double x;
  x = 0.0;
  for (i = 0; i < DIMENSION; i++){
    for (j = 0; j < DIMENSION; j++){	
      if (i >= j){
	Matrix[i][j] = x;
	x += 1.0;
      } else
	Matrix[i][j] = 1.0;
	}
  }
}

/*********************************************************************\                        
* Input    : None                                                     *             
* Output   : None                                                     *         
* Function : Transpose a Matrix initialized by previous funtions      *              
\*********************************************************************/
void      TransposeMatrix(){
int i,j,k,l;
int blocksize;															//Variable to store block size
blocksize = 40000;
for (i = 0; i < DIMENSION; i += blocksize) {							//Iterate the outer loop till dimension and increment till block size
    for (j = 0; j < i; j += blocksize) { 								//Iterate the inner loop till Previous loop and increment till blocksize
        // transpose the block beginning at [i,j]
        for (k = i; k < i + blocksize && k < DIMENSION; ++k) {			//Iterate the block outer loop till block size and also just not to go out of range check to be within dimension
            for (l = j; l < j + blocksize && l <= k; ++l) { 			//Iterate the block inner loop till block size and till previous loop
				float temp = Matrix[l][k];
				Matrix[l][k] = Matrix[k][l];							//Swap the variables using a temporary variables in order to get transpose of matrix
				Matrix[k][l] = temp;
				
            }
        }
    }
}
}
/*********************************************************************\                
* Input    : dimension (first n lines/columns)                        *  
* Output   : None                                                     *   
* Function : Initialize a matrix columnwise                           *                        
\*********************************************************************/
void      DisplayUpperQuandrant(unsigned dimension){
  int i,j;

  printf("\n\n********************************************************\n");
  for (i = 0; i < dimension; i++){
    printf("[");
    for (j = 0; j < dimension; j++){
      printf("%8.1f ",Matrix[i][j]);
    }    
    printf("]\n");
  }
  printf("***************************************************************\n\n");
}
