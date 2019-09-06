#include <iostream>
#include <fstream>
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
    //ifstream and ofstream to read the file, and output the array to a file
	ifstream readFile("data.txt");
	ofstream outputFile("stooge.out");

	while (!readFile.eof())
	{
		int size;
		int* array;

		//readFile returns the size of the array from the file
		readFile >> size;

		//allocates memory for the size of the array from the file
		array = new int[size];

		//creates a tempArray
		int tempArray;
		for (int i = 0; i < size; i++)
		{
			readFile >> tempArray;
			array[i] = tempArray;
		}


		//Function call to stoogeSort to order the array elements from lowest to highest
		stoogeSort(array, 0, size - 1);


		//exports the array elements to the outputFile
		for (int i = 0; i < size; i++)
		{
			outputFile << array[i] << " ";
		}
		outputFile << endl;

		//frees the memory of the array
		delete[] array;
	}

	//close the file streams
	readFile.close();
	outputFile.close();

	return 0;
}

