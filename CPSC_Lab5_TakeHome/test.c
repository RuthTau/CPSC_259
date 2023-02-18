/*Author:       Ruth Tau and Tessa Clement
Student Numbers: 37100518 and 61619698
CS Accounts:     tyy and tessa42
Date:            8 Dec 2022
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"


#define web "web.txt"
#define  BUFSIZE 256

int matrix_dimension(FILE* pointer);
char** read_file(FILE* filepointer, int dimension);

int main(void) {

    /* Variables */
    Engine* ep = NULL; // A pointer to a MATLAB engine object
    mxArray* ConnectivityMatrix= NULL;
    mxArray* Result = NULL;

    /*local variables*/
    FILE* infile = NULL;
    FILE* dim_infile = NULL;
    int error = 0;
    int dimension = 0;
    char** matrix_pointer = NULL;
    double temp_Matrix[BUFSIZE][BUFSIZE];
    double Matrix_One[BUFSIZE * 235]; // one dimension matrix to store temp

    char buffer[BUFSIZE + 1];

    /*sizes*/
    int row = 0;
    int column = 0;
    int i = 0;
    int j = 0;
    int k = 0;

    /* Starts a MATLAB process */
    error = fopen_s(&infile,web, "r");
    if (error == 0) {
        printf("[PASS] File opened\n");
        fopen_s(&dim_infile, web, "r");
    }
    else {
        printf("[FAILED] File not opened\n");
        printf("web.txt is NULL");
    }

    dimension = matrix_dimension(dim_infile); 

    if (dimension > 0) {
        matrix_pointer = read_file(infile, dimension);
        for (row = 0; row < dimension; row++) {
            for (column = 0; column < dimension; column++) {
                temp_Matrix[row][column] = (double)matrix_pointer[row][column] - 48;
            }
        }
    }

    if (infile != NULL) {
        printf("FILE CLOSED\n\n");
        fclose(infile);
    }

   

    if (!(ep = engOpen(NULL))) {
        fprintf(stderr, "\nCan't start MATLAB engine\n");
        system("pause");
        return 1;
    }

    ConnectivityMatrix = mxCreateDoubleMatrix(dimension, dimension, mxREAL);
    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            Matrix_One[k] = temp_Matrix[j][i];
            k++;
        }
        j = 0;
    }
    memcpy((void*)mxGetPr(ConnectivityMatrix), (void*)Matrix_One, dimension*dimension* sizeof(double));
    //lines of commands



    //print connectivity matrix (with same format as the text file: not in the MATLAB form)
    {
        size_t sizeOfConnectivityMatrix = mxGetNumberOfElements(ConnectivityMatrix);
        size_t a = 0;
        size_t b = 0;
        printf("Dimension = %d\n\n", dimension);
        printf("The Connectivity Matrix is:\n\n");
        for (a = 0; a < sizeOfConnectivityMatrix / dimension; a++)
        {
            for (b = 0; b < sizeOfConnectivityMatrix; b += dimension)
            {
                printf(" %1.0f  ", *(mxGetPr(ConnectivityMatrix) + a + b));
            }			  printf("\n");
        }
    }

    printf("\n");

    if (engPutVariable(ep, "ConnectivityMatrix", ConnectivityMatrix)) {
        fprintf(stderr, "\nCannot write ConnectivityMatrix to MATLAB \n");
        system("pause");
        exit(1); // Same as return 1;
    }


    if (engEvalString(ep, "[rows, columns] = size(ConnectivityMatrix)")) {
        fprintf(stderr, "\nError \n");
        system("pause");
        exit(1);
    }


    if (engEvalString(ep, "dimension = size(ConnectivityMatrix, 1)")) {
        fprintf(stderr, "\nError \n");
        system("pause");
        exit(1);
    }


    if (engEvalString(ep, "columnsums = sum(ConnectivityMatrix, 1)")) {
        fprintf(stderr, "\nError \n");
        system("pause");
        exit(1);
    }


    if (engEvalString(ep, "p = 0.85")) {
        fprintf(stderr, "\nError\n");
        system("pause");
        exit(1);
    }


    if (engEvalString(ep, "zerocolumns = find(columnsums~=0)")) {
        fprintf(stderr, "\nError\n");
        system("pause");
        exit(1);
    }


    if (engEvalString(ep, "D = sparse( zerocolumns, zerocolumns, 1./columnsums(zerocolumns), dimension, dimension)")) {
        fprintf(stderr, "\nErro\n");
        system("pause");
        exit(1);
    }


    if (engEvalString(ep, "StochasticMatrix = ConnectivityMatrix * D")) {
        fprintf(stderr, "\nError \n");
        system("pause");
        exit(1);
    }


    if (engEvalString(ep, "[row, column] = find(columnsums==0)")) {
        fprintf(stderr, "\nError\n");
        system("pause");
        exit(1);
    }


    if (engEvalString(ep, "StochasticMatrix(:, column) = 1./dimension")) {
        fprintf(stderr, "\nError\n");
        system("pause");
        exit(1);
    }


    if (engEvalString(ep, "Q = ones(dimension, dimension)")) {
        fprintf(stderr, "\nError\n");
        system("pause");
        exit(1);
    }


    if (engEvalString(ep, "TransitionMatrix = p * StochasticMatrix + (1 - p) * (Q/dimension)")) {
        fprintf(stderr, "\nError\n");
        system("pause");
        exit(1);
    }

    if (engEvalString(ep, "PageRank = ones(dimension, 1)")) {
        fprintf(stderr, "\nError\n");
        system("pause");
        exit(1);
    }


    if (engEvalString(ep, "for i = 1:100 PageRank = TransitionMatrix * PageRank; end")) {
        fprintf(stderr, "\nError\n");
        system("pause");
        exit(1);
    }

    if (engEvalString(ep, "PageRank = PageRank / sum(PageRank)")) {
        fprintf(stderr, "\nError\n");
        system("pause");
        exit(1);
    }

    printf("\nRetrieving Page Ranks....\n\n");

    // display the result

    if ((Result = engGetVariable(ep, "PageRank")) == NULL) {
        fprintf(stderr, "\nFailed to get PageRank\n");
        system("pause");
        exit(1);
    }
    else {
        size_t sizeOfResult = mxGetNumberOfElements(Result);
        int i = 0;
        printf("NODE      RANK\n");
        printf("---     ----\n");

        for (i = 0; i < sizeOfResult; ++i) {
            printf("%d     ", (i + 1));
            printf("%.4f\n", *(mxGetPr(Result) + i));
        }
            
        }

     printf("\n");


    if (engOutputBuffer(ep, buffer, BUFSIZE)) {
        fprintf(stderr, "\nCan't create buffer for MATLAB output\n");
        system("pause");
        return 1;
    }
    buffer[BUFSIZE] = '\0';

    engEvalString(ep, "whos"); // whos is a handy MATLAB command that generates a list of all current variables
    printf("%s\n", buffer);

   
    mxDestroyArray(ConnectivityMatrix);
    mxDestroyArray(Result);


  
    ConnectivityMatrix = NULL;
    Result = NULL;

    if (engClose(ep)) {
        fprintf(stderr, "\nFailed to close MATLAB engine\n");
    }

    system("pause"); // So the terminal window remains open long enough for you to read it
    return 0; // Because main returns 0 for successful completion
   


}



int matrix_dimension(FILE* pointer)
{

    char  line_buffer[BUFSIZE];

    if (fgets(line_buffer, BUFSIZE, pointer))
    {
        return (int)strlen(line_buffer) / 2;
    }
    return 0; //if NULL file*/
}

char** read_file(FILE* file_pointer, int dimension)
{
    //counters
    int i = 0;
    int j = 0;
    int k = 0;
    //allocate mem space for line_buffer
    char line_buffer[BUFSIZE];

    //allocate space for the **
    char** matrix = (char**)calloc(dimension, dimension * sizeof(char));

    //allocate space for each * of the **
    for (i = 0; i < dimension; i++)
    {
        matrix[i] = (char*)calloc(dimension, dimension * sizeof(char));
    }

    //reuse counter
    i = 0;

    //Copies the file, line by line, to line buffer using fgets in a while loop
    while (fgets(line_buffer, BUFSIZE, file_pointer) != NULL && i < dimension)
    {
        for (j = 0; j < dimension * 2 - 1; j++)
        {
            if (line_buffer[j] == '0' || line_buffer[j] == '1')//if element is a valid char ( '1' or '0'), copy into double**
            {
                matrix[i][k] = line_buffer[j];
                k++;
            }
        }
        i++;
        //reuse counters
        j = 0;
        k = 0;
    }
    return matrix;
}
