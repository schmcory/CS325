#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

//Source (read this): https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/

//max helper function
int max(int a, int b) {
    if(a > b) {
        return a;
    }

    else {
        return b;
    }
}

//knapsack function
//Parameters
    //W = weight of each item in the shopping bag
    //P = price of each item in the shopping bag
    //N = number of items in the shopping bag
    //M = max weight of all the items in the shopping bag
int knapsack(int W[], int P[], int N, int M, vector<int> &v) {

    int K[N + 1][M + 1];

    //2 nested for loops build a table of the total number of items and the max weight
    for(int i = 0; i <= N; i++) {
        for(int j = 0; j <= M; j++) {
            if(i == 0 || j == 0) {
                K[i][j] = 0;
            }

            else if(W[i - 1] <= j) {
                K[i][j] = max(P[i - 1] + K[i - 1][j - W[i - 1]], K[i - 1][j]);
            }

            else {
                K[i][j] = K[i - 1][j];
            }

        }
    }

    //stores the result of knapsack
    int result = K[N][M];
    int m = M;

    for(int n = N; n > 0 && result > 0; n--) {
        if(result == K[n - 1][m]) {
            continue;
        }

        else {
            v.push_back(n);
            result -= P[n - 1];
            m -= W[n - 1];
        }
    }
    return K[N][M];
}

int main()
{
    //ifstream and ofstream to read the file, and output the array to a file
	ifstream readFile;
	ofstream outputFile("results.txt");

	readFile.open("shopping.txt");

        int T; //T is the number of test cases given on line one of the inputfile
        int N; //N is the number of items in each test case
        int P[100]; //P is an integer that corresponds to the price of each item
        int W[100]; //W is an integer corresponds to the weight of the item
        int F; //F is the number of people in each family
        int M; //M is the maximum weight each person in the family can carry
        int x = 1; //incrementer for the test cases
        vector<vector<int> >vec(100);

		//readFile returns the number of test cases from the input file
		readFile >> T;

		//for loop, loops through the number of test cases (i < T)
		for (int i = 0; i < T; i++) {

		    //readFile returns the number of items from the input file
			readFile >> N;

            //nested for loop, loops through the number of items
            //returns the price and weight of each item and places them into arrays
			for(int j = 0; j < N; j++) {
                readFile >> P[j];
                readFile >> W[j];
			}

            //totalPrice is the total price of ALL items the family carries
            int totalPrice = 0;

            //readFile returns the number of family members in the family from the input file
            readFile >> F;

            //nested for loop, loops through the number of family members
            //returns the maximum weight each family member can carry
            for (int k = 0; k < F; k++) {
                //readFile returns the maximum weight each family member can carry
                    readFile >> M;

                    //totalPrice variable initialized as the maximum price of items that can be carried by the current family member
                    //all family members are looped through and added to the total price
                    //function call to shoppingBag returns the price, weight, numItems, and maxWeight of each family member
                    //function call to knapsack puts each family in a vector
                    totalPrice += knapsack(W, P, N, M, vec[k]);
            }


            //prints the number of the test case to the output file
            outputFile << "Test Case " << x << endl;
            x++;

            //prints the totalPrice to the the output file
            //cout << "Total Price " << totalPrice << endl;
            outputFile << "Total Price " << totalPrice << endl;

            //prints the items each family member should take (ex. 1:1) to the output file
            outputFile << "Member Items" << endl;
            for(int n = 0; n < F; n++) {
                sort(vec[n].begin(), vec[n].end());
                //cout << n + 1 << ": ";
                outputFile << n + 1 << ": ";

                for(int m = 0; m < vec[n].size(); m++) {
                    outputFile << vec[n][m] << " ";
                }
                outputFile << endl;
            }
        }

	//close the file streams
	readFile.close();
	outputFile.close();

	return 0;
}
