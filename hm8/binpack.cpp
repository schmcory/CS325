#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <vector>
using namespace std;

//Source (time): https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
//Source (bin-packing): https://www.geeksforgeeks.org/bin-packing-problem-minimize-number-of-used-bins/
//Source (bubble-sort): https://www.geeksforgeeks.org/bubble-sort/

//function prototypes
void firstFit(int [], int, int);
void firstFitDecreasing(int [], int, int);
void bestFit(int [], int, int);

//main function
int main() {
    //ifstream opens file
    ifstream readFile("bin.txt");

    //variable for returning the number of tests in the file
    int test;

    //variable for returning the capacity of each bin for each test case
    int capacity;

    //variable for returning the number of items for each test case
    int size;

    //readFile returns the number of tests in the file
    readFile >> test;

    //for loop traverses through the number of tests in the file
        for(int i = 0; i < test; i++) {

            //readFile returns the capacity of each bin in each test case
            readFile >> capacity;

            //readFile returns the number of items in each test case
            readFile >> size;

            //initialize weight vectors to hold items for each algorithm
            int weightFFD[size];
            int weightFF[size];
            int weightBF[size];

            //for loop traverses through the weights of each item from the file
            for(int n = 0; n < size; n++) {
                //readFile returns the weights of each item in each test case
                readFile >> weightFFD[n];
            }

            //for loop traverses through the weights of each item from the file
            for(int m = 0; m < size; m++) {
                weightFF[m] = weightFFD[m];
                weightBF[m] = weightFFD[m];
            }

            //increments the number of test cases
            cout << "Test Case " << i + 1 << " ";

        /* Start runtime of each algorithm */
            //get starting timepoint
            auto start = chrono::high_resolution_clock::now();

            //unsync the I/O of C and C++
            ios_base::sync_with_stdio(false);

            //function calls to fit algorithms
            firstFit(weightFF, size, capacity);

            //get ending timepoint
            auto end = chrono::high_resolution_clock::now();

            //calculating total time taken by the algorithm
            double time = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

            time *= 1e-9;

            cout << time << " seconds. ";

        /* End runtime of each algorithm */

        /* Start runtime of each algorithm */
            //get starting timepoint
            auto start2 = chrono::high_resolution_clock::now();

            //unsync the I/O of C and C++
            ios_base::sync_with_stdio(false);

            //function calls to fit algorithms
            firstFitDecreasing(weightFFD, size, capacity);

            //get ending timepoint
            auto end2 = chrono::high_resolution_clock::now();

            //calculating total time taken by the algorithm
            double time2 = chrono::duration_cast<chrono::nanoseconds>(end2-start2).count();

            time2 *= 1e-9;

            cout << time2 << " seconds. ";

        /* End runtime of each algorithm */

        /* Start runtime of each algorithm */
            //get starting timepoint
            auto start3 = chrono::high_resolution_clock::now();

            //unsync the I/O of C and C++
            ios_base::sync_with_stdio(false);

            //function calls to fit algorithms
            bestFit(weightBF, size, capacity);

            //get ending timepoint
            auto end3 = chrono::high_resolution_clock::now();

            //calculating total time taken by the algorithm
            double time3 = chrono::duration_cast<chrono::nanoseconds>(end3-start3).count();

            time3 *= 1e-9;

            cout << time3 << " seconds." << endl;

        /* End runtime of each algorithm */
        }
    //close the file stream
    readFile.close();
    return 0;
}

/*
Void firstFit function to find the number of bins required using first fit
Parameters (integer data type)
    weight[]: array variable to store weights of each item to place in a bin
    size: variable to store the number of items to place in a bin
    capacity: variable to store the total weight capacity of of each bin
*/
void firstFit(int weight[], int size, int capacity) {
    //count variable (number of bins) is initialized to zero
    int count = 0;

    //creates an array to store remaining space in bins
    int bin[size];

    //for loop places items into a bin
    for (int i = 0; i < size; i++) {
        int j;
        //nested for loop finds the first bin[j] that fit fit item of weight[i]
       for(j = 0; j < count; j++) {
            //if the capacity of bin j is greater than or equal to the weight of item i
            if(bin[j] >= weight[i]) {
                //decrease the capacity of bin j by the weight of item i
                bin[j] -= weight[i];
                break;
            }
       }
       //if no bin j could accomodate the weight of item i
       if(j == count) {
           //create a new bin
            bin[count] = capacity - weight[i];
            count++;
       }
    }
    cout << "First Fit: " << count << ", ";
}

//Modified bubble sort function sorts array of numbers in descending order
void bubbleSort(int array[], int size) {
    for(int i = 0; i < (size - 1); i++) {
        for(int j = 0; j < size - i - 1; j++) {
           if(array[j] < array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
           }
        }
    }
    /* for testing purposes
    for(int n = 0; n < size; n++) {
        cout << array[n] << " ";
    }
    cout << endl;
    */
}


/*
Void firstFitDecreasing function to find the number of bins required using first fit
Pre-Conditions: Calls the bubbleSort algorithm to sort the weights in descending order
Parameters (integer data type)
    weight[]: array variable to store weights of each item to place in a bin
    size: variable to store the number of items to place in a bin
    capacity: variable to store the total weight capacity of of each bin
*/
void firstFitDecreasing (int weight[], int size, int capacity) {
    //function call to bubbleSort to sort the weights of each item
    bubbleSort(weight, size);

    //count variable (number of bins) is initialized to zero
    int count = 0;

    //creates an array to store remaining space in bins
    int bin[size];

    //for loop places items into a bin
    for (int i = 0; i < size; i++) {
        int j;
        //nested for loop finds the first bin[j] that fit fit item of weight[i]
       for(j = 0; j < count; j++) {
            //if the capacity of bin j is greater than or equal to the weight of item i
            if(bin[j] >= weight[i]) {
                //decrease the capacity of bin j by the weight of item i
                bin[j] -= weight[i];
                break;
            }
       }
       //if no bin j could accomodate the weight of item i
       if(j == count) {
           //create a new bin
            bin[count] = capacity - weight[i];
            count++;
       }
    }
    cout << "First Fit Decreasing: " << count << ", ";
}

/*
Void bestFit function to find the number of bins required using best fit
Parameters (integer data type)
    weight[]: array variable to store weights of each item to place in a bin
    size: variable to store the number of items to place in a bin
    capacity: variable to store the total weight capacity of of each bin
*/
void bestFit(int weight[], int size, int capacity) {
    //count variable (number of bins) is initialized to zero
    int count = 0;

    //creates an array to store remaining space in bins
    int bin[size];

    //for loop places items into a bin
    for (int i = 0; i < size; i++) {
        int j;

    int minimum = capacity + 1;     //intialize the minimum space left in each bin
    int bin_index = 0;              //initalize the index of the best fit bin

        //nested for loop finds the first bin[j] that best fit item of weight[i]
       for(j = 0; j < count; j++) {
            //if the capacity of bin j is greater than or equal to the weight of item i
            //if the capacity of bin j minus the weight of item i is less than the capacity of bin j + 1;
            if(bin[j] >= weight[i] && bin[j] - weight[i] < minimum) {
                //set the best fit bin index to bin j
                bin_index = j;

                //set the minimum space left in each bin to bin j minus the weight of item i
                minimum = bin[j] - weight[i];
            }
       }
        //if no bin could accomdate the weight of item i
       if(minimum == capacity + 1) {
            //create a new one
            bin[count] = capacity - weight[i];
            count++;
       }

       //assign the item i to the best fit bin
       else {
            bin[bin_index] -= weight[i];
       }
    }
    cout << "Best Fit: " << count << ", ";
}
