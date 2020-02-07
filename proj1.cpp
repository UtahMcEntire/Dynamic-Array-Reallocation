// Utah McEntire
// CSCI 3110-001
// Project #1
// Due: 09/06/19
// Purpose: This program dynamically allocates an array then
// reallocates it a percentage larger as the array reaches
// its capacity

#include <iostream>
#include <fstream>
#include <cassert>
#include <array>
#include <cstdlib>
using namespace std;

int* allocateArray(int* arr, int* size, double percentage);
double calcAvg(int* arr, int numofvalues);

int main() {

	int *arr=NULL, *size=0;
	int initialSize, index = 0; // Declare initial values of variables
	double average = 0;
	float percentage, nextnum;
	
	ifstream myIn;
	ofstream myOut;
	myIn.open("nums.txt"); // Input filename
	myOut.open("out.txt"); // Output filename
	assert(myIn);
	assert(myOut);

	myIn >> initialSize; // Priming reads of size and percentage
	myIn >> percentage;
	percentage++;
	size = &initialSize;

	if (((initialSize % 50) == 0) && initialSize >= 100 && initialSize <= 350) { //Validation of initial array size
		arr = allocateArray(arr, size, percentage); // Initial array allocation
		cout << initialSize << endl; // Validation of initial array size
		myOut << initialSize << endl;

		while (myIn>>nextnum) { //4. File processing loop
			arr[index] = nextnum;
			index++;
			if (index == *size) { //If the current array is full:
				cout << index << " " << calcAvg(arr, index) << endl; //Output ntermediate averages to screen
				myOut << index << " " << calcAvg(arr, index) << endl; //Output ntermediate averages to output file
				arr = allocateArray(arr, size, percentage); // Subsequent array allocation
			}
		}
		
		// Outputs the final size of the array, number of items in array, average of all numbers
		cout << *size << " " << index << " " << calcAvg(arr, index) << endl;
		myOut << *size << " " << index << " " << calcAvg(arr, index) << endl;
	}
	else { // Initial size input was not divisible by 50 or not between 100-350
		cout << "Error" << endl;
		return 1;
	}

	delete[] arr;
	arr = NULL;
	myIn.close(); // Close the opened files
	myOut.close();
	return 0;
}

// Will allocate initial array according to specified size (first line in file) then
// will move the values to a larger array when previous reaches capacity and delete
// the old array.
int* allocateArray(int* arr, int* size, double percentage) {
	int temp = *size * (percentage); // Stores new size in the integer "temp"
	
	if (arr == NULL) {
		arr = new int[*size]; //Initial allocation
		return arr; //Initial return
	}
	else {
		int* newarr = new int[temp]; // Subsequent allocation with new size
		for (int i = 0; i < *size; i++) { //Subsequent allocation (copy)
			newarr[i] = arr[i];
		}
		*size = temp;
		delete[] arr; //Subsequent allocation (deallocation) of old array memory
		return newarr; //Subsequent allocation (modified and returned values)
	}
}

// Will calculate the average of all values in given array and return that average.
double calcAvg(int* arr, int numofvalues) {
	int i = 0;
	double sum = 0;
	for (i; i < numofvalues; i++) {
		sum += arr[i]; //Adding all elements in array to sum
	}
	return (sum / i); //Returns sum/num of elements entered
}
