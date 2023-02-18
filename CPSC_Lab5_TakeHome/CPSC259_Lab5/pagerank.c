/*Author:       Ruth Tau and Tessa Clement
Student Numbers: 37100518 and 61619698
CS Accounts:     tyy and tessa42
Date:            8 Dec 2022
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"


#define MATRIX "web.txt"
#define BUFSIZE 256
#define VISITED   'Y'
#define UNVISITED 'N'



int get_dimension(FILE* matrix_file);

int main(void) {

    /* Variables */
    Engine* ep = NULL; // A pointer to a MATLAB engine object
    mxArray* Result = NULL;
    mxArray* ConnectivityMatrix = NULL;

    

    char buffer[BUFSIZE + 1];
    double** matrix_new = NULL;
    double matrix_ONE[BUFSIZE * 235];
    int         row = 0;
    int         column = 0;

    /*open file and get matrix*/
    int dimension = 0;
    FILE* matrix_file = NULL;
    matrix_file = fopen(MATRIX, "r");

    //check if file is valid
    if (matrix_file) {
        dimension = get_dimension(matrix_file);
        /* Variables */
        char line_buffer[BUFSIZE];


        /* Allocates memory for correctly-sized maze */

        matrix_new = (double**)calloc(dimension, sizeof(double*));

        for (row = 0; row < dimension; ++row) {

            matrix_new[row] = (double*)calloc(dimension, sizeof(double));
        }

        /* Copies maze file to memory */
        row = 0;
        while (fgets(line_buffer, BUFSIZE, matrix_file)) {
            for (column = 0; column < dimension; ++column) {
                // INSERT CODE HERE (2 lines)
                matrix_new[row][column] = line_buffer[column];

            }
            row++;
        }
    }
    else {
        fprintf(stderr, "Unable to parse maze file: %s\n", MATRIX);
        system("pause");
    }


    if (!(ep = engOpen(NULL))) {
        fprintf(stderr, "\nCan't start MATLAB engine\n");
        system("pause");
        return 1;
    }
    int k = 0;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            matrix_ONE[k] = matrix_new[j][i];
            k++;
        }
    }

    ConnectivityMatrix = mxCreateDoubleMatrix(dimension, dimension, mxREAL);
    memcpy((void*)mxGetPr(ConnectivityMatrix), (void*)matrix_ONE, dimension*dimension* sizeof(double));


    if (engPutVariable(ep, "ConnectivityMatrix", ConnectivityMatrix)) {
        fprintf(stderr, "\nCannot write ConnectivityMatrix to MATLAB \n");
        system("pause");
        exit(1); // Same as return 1;
    }


    if (engEvalString(ep, "ConnectivityMatrix= transpose(ConnectivityMatrix)")) {
        fprintf(stderr, "\nError \n");
        system("pause");
        exit(1);
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

    // display the result

    if ((Result = engGetVariable(ep, "PageRank")) == NULL) {
        fprintf(stderr, "\nFailed to get PageRank\n");
        system("pause");
        exit(1);
    }
    else {
        size_t sizeOfResult = mxGetNumberOfElements(Result);
        int i = 0;
        printf("NODE    RANK\n");
        printf("---    ----\n");

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




int get_dimension(FILE* matrix_file)
{

    int  d = 0;
    char line_buffer[BUFSIZE];

    d = strlen(fgets(line_buffer, BUFSIZE, matrix_file));

    /* You don't need to know this.  It 'resets' the file's internal pointer to the
       beginning of the file. */
    fseek(matrix_file, 0, SEEK_SET);

    /* Checks if text file was created in Windows and contains '\r'
       IF TRUE reduce strlen by 2 in order to omit '\r' and '\n' from each line
       ELSE    reduce strlen by 1 in order to omit '\n' from each line */
    if (strchr(line_buffer, '\r') != NULL) {
        // INSERT CODE HERE (1 line)
        // return ...
        return d - 2;
    }
    else {
        // INSERT CODE HERE (1 line)
        // return ...
        return d - 1;
    }
}

