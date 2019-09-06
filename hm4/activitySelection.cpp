#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

//Sources: https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/

//structure to hold the activity number, start time and finish time
struct Activity {
	int number;
	int start;
	int finish;
};

//bool function to compares the start times of the activities and returns the highest
bool activityCompare(Activity s1, Activity s2) {
	return s1.start > s2.start;
}

//The activity selection last-to-start algorithm
void activitySelection(vector <Activity> &activities, int number){

	//sorts the activities according to start time
	sort(activities.begin(), activities.end(), activityCompare);

	//vector of Activity structure creates results object 
	vector <Activity> results;

	//the first activity always gets selected according to the greedy choice
	results.push_back(activities[0]);

	//for loop scans through the activities to find the optimal solution
	for (int i = 1; i < activities.size(); i++) {
		if(results.back().start >= activities[i].finish) {
			results.push_back(activities[i]);
		}
	}

	//output the results to the console
	cout<<"Set " << number << endl;
	cout<<"Number of activities selected = "<< results.size() << endl;
	cout<<"Activities: ";
		for(int j = results.size() - 1; j >= 0; j--) {
			cout<< results[j].number <<" ";
		}
	cout << endl;
}

//main function
int main() {

	//ifstream opens file
	ifstream readFile("act.txt");

	//number variable corresponds to the number of sets from the file
	int number = 1;

	//while loop scans the entire file
	while(!readFile.eof()) {
		int set;

		//readFile returns the size of the activity sets
		readFile >> set;

		//structure object creates each set from the file
		Activity activity[set];

		//vector of structure Activity with array object of sets from the file
		vector<Activity> activities(set);

		//for loop reads the number, the start time, and the finish time of each activity
		for(int i = 0; i < set; i++) {
			readFile >> activity[i].number;
			readFile >> activity[i].start;
			readFile >> activity[i].finish;

			activities[i] = activity[i];
		}

		//function call to activitySelection sorts the activities according to start time and number of sets
		activitySelection(activities, number);

		//increments number of sets
		number++;
    }

	//close the file stream
	readFile.close();
	return 0;
}
