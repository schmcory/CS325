#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//stoogeSort function starts splits the array into thirds
//1 - if the lowest value (index 0) is greater than highest value (index high), swap them
//2 - sort the initial 2/3 of the array
//3 - sort the last 2/3 of the array
//4 - sort the last 2/3 of the array again (checks to make sure all numbers were travesered)
void stoogeSort(int array[], int low, int high)
{

    //if the lowest number is greater than the higher number, move forward
    if(low >= high) {
        return;
    }

    //if the first element in the array is smaller than the next element, swap them and pass them into the temp array
    if(array[low] > array[high]) {
        int tempArray = array[low];
        array[low] = array[high];
        array[high] = tempArray;
    }

    //if there are more than two elements in the array
    if(high - low + 1 > 2) {
        int m = (high - low + 1)/3;

        //recursively sort the first 2/3 of the elements
        stoogeSort(array, low, high - m);

        //recursively sort the last 2/3 of the elements
        stoogeSort(array, low + m, high);

        //recursively sort last 2/3 elements again (checks to confirm all elements were passed through)
        stoogeSort(array, low, high - m);
    }
}


int main()
{
    //seed the time
    srand(time(0));

    int n = 10000;
    int *array;

		//allocates memory for the size of the array from the file
		array = new int[n];

		//for loop inputs the random numbers between 0 and 10,000 into the array
		for (int i = 0; i < n ; i++)
		{
            int tempArray = rand() % 10000 + 1;
			array[i] = tempArray;
		}

        clock_t start;
        start = clock();

		//Function call to mergeSort to order the array elements from lowest to highest
		stoogeSort(array, 0, n - 1);

        start = clock() - start;
        cout << endl << endl;
        cout << setprecision(2) << fixed;
        cout << "Size of array : " << n << endl;
        cout << "Run time: " << double(start)/CLOCKS_PER_SEC << " seconds " << endl;

		//frees the memory of the array
		delete[] array;
        return 0;
}

