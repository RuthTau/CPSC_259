     /*Author:       Ruth Tau and Tessa Clement
 Student Numbers: 37100518 and 61619698
 CS Accounts:     tyy and tessa42
 Date:            2 Dec 2022
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"


#define  BUFSIZE 256

int main(void) {

    /* Variables */
    Engine* ep = NULL; // A pointer to a MATLAB engine object
    mxArray* testArray = NULL, * result = NULL; // mxArray is the fundamental type underlying MATLAB data
    double time[3][3] = { { 1.0, 2.0, 3.0 }, {4.0, 5.0, 6.0 }, {7.0, 8.0, 9.0 } }; // Our test 'matrix', a 2-D array

    mxArray* testmatrixOne = NULL, * resultOne = NULL;
    double matrixOne[3][3] = {{ 1.0, 4.0, 7.0 }, {2.0, 5.0, 8.0 }, {3.0, 6.0, 9.0 } }; 

    mxArray* testmatrixTwo = NULL, * resultTwo = NULL;
    double matrixTwo[3][3] = { { 2.0, 3.0, 4.0 }, { 2.0, 3.0, 4.0 }, { 2.0, 3.0, 4.0 } };

    mxArray* productResult = NULL;

    /* Starts a MATLAB process */
    if (!(ep = engOpen(NULL))) {
        fprintf(stderr, "\nCan't start MATLAB engine\n");
        system("pause");
        return 1;
    }
    testArray = mxCreateDoubleMatrix(3, 3, mxREAL);
    memcpy((void*)mxGetPr(testArray), (void*)time, 9 * sizeof(double));


    testmatrixOne = mxCreateDoubleMatrix(3, 3, mxREAL);
    memcpy((void*)mxGetPr(testmatrixOne), (void*)matrixOne, 9 * sizeof(double));

    testmatrixTwo = mxCreateDoubleMatrix(3, 3, mxREAL);
    memcpy((void*)mxGetPr(testmatrixTwo), (void*)matrixTwo, 9 * sizeof(double));


    if (engPutVariable(ep, "testArray", testArray)) {
        fprintf(stderr, "\nCannot write test array to MATLAB \n");
        system("pause");
        exit(1); // Same as return 1;
    }

    if (engPutVariable(ep, "testmatrixOne", testmatrixOne)) {
        fprintf(stderr, "\nCannot write matrix One to MATLAB \n");
        system("pause");
        exit(1); // Same as return 1;
    }

    if (engPutVariable(ep, "testmatrixTwo", testmatrixTwo)) {
        fprintf(stderr, "\nCannot write matrix Two to MATLAB \n");
        system("pause");
        exit(1); // Same as return 1;
    }



    if (engEvalString(ep, "testArrayEigen = eig(testArray)")) {
        fprintf(stderr, "\nError calculating eigenvalues  \n");
        system("pause");
        exit(1);
    }


     
    if (engEvalString(ep, "testProductMatrix =  transpose(testmatrixOne) * transpose(testmatrixTwo)")) {
        fprintf(stderr, "\nError calculating product  \n");
        system("pause");
        exit(1);
    }


    // display the result

    if ((resultOne = engGetVariable(ep, "testmatrixOne")) == NULL) {
        fprintf(stderr, "\nFailed to retrieve matrix one vector\n");
        system("pause");
        exit(1);
    }
    else {
        size_t sizeOfResult = mxGetNumberOfElements(resultOne);
        size_t i = 0;
        size_t j = 0;
        printf("The first matrix was:\n");

        for (i = 0; i < sizeOfResult / 3; ++i) {
            for (j = 0; j < sizeOfResult / 3; j++) {
                printf("%f ", *(mxGetPr(resultOne) + i * 3 + j));
            }
            printf("\n");
        }
    }

    if ((resultTwo = engGetVariable(ep, "testmatrixTwo")) == NULL) {
        fprintf(stderr, "\nFailed to retrieve matrix one vector\n");
        system("pause");
        exit(1);
    }
    else {
        size_t sizeOfResult = mxGetNumberOfElements(resultTwo);
        size_t i = 0;
        size_t j = 0;
        printf("The second matrix was:\n");

        for (i = 0; i < sizeOfResult/3; ++i) {
            for (j = 0; j < sizeOfResult / 3; j++) {
                printf("%f ", *(mxGetPr(resultTwo)+ i * 3+ j) );
            }
            printf("\n");
        }

    }

    if ((productResult = engGetVariable(ep, "testProductMatrix")) == NULL) {
        fprintf(stderr, "\nFailed to retrieve matrix one vector\n");
        system("pause");
        exit(1);
    }
    else {
        size_t sizeOfResult = mxGetNumberOfElements(productResult);
        size_t i = 0;
        size_t j = 0;
        printf("The matrix product is:\n");

        for (i = 0; i < sizeOfResult / 3; ++i) {
            for (j = 0; j < sizeOfResult / 3; j++) {
                printf("%f ", *(mxGetPr(productResult) + i * 3 + j));
            }
            printf("\n");
        }

    }


    char buffer[BUFSIZE + 1];

    if (engOutputBuffer(ep, buffer, BUFSIZE)) {
        fprintf(stderr, "\nCan't create buffer for MATLAB output\n");
        system("pause");
        return 1;
    }
    buffer[BUFSIZE] = '\0';

    engEvalString(ep, "whos"); // whos is a handy MATLAB command that generates a list of all current variables
    printf("%s\n", buffer);

    mxDestroyArray(testArray);
    mxDestroyArray(result);
    testArray = NULL;
    result = NULL;
    if (engClose(ep)) {
        fprintf(stderr, "\nFailed to close MATLAB engine\n");
    }

    system("pause"); // So the terminal window remains open long enough for you to read it
    return 0; // Because main returns 0 for successful completion

}
