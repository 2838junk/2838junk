#include <iostream>

using namespace std;


/* FUNCTIONS */

int readADC(int nAIN){
	// Argument is analog input number (e.g. "0" for AIN0/P9_39)
	// Concatenate path and read value
	// Return single read value of AIN#
}

int readMic(int nMic){
	// Argument is microphone number
	// Read a sample series of values from the analog input using readADC(AIN#)
	// Calculate average (max?) peak-to-peak value of sample set; calculate any other values?
	// Return peak-to-peak value
}

int dataMinder(){
	// No argument; called periodically; Might combine with readMic
	// Requests readMic() for each of the available microphones
	// Maintains data arrays;
	// Calculates basic metrics (short average, long average, etc.)
	// Returns success/failure;
}

int driveMotor(int neworientation){
	// Argument is a value that indicates the motor orientation (degree, value, mic#?)
	// Determine path (direction, distance, speed(?)
	// Send commands through GPIO output to move motor
	// Returns success/failure of command issuance
}

int Assessor(){
	// No argument; called periodically;  knows current focus and orientation
	// Determine the loudest orientation
	// Determine if any start triggers occurred
	// Determine if any end triggers occurred, especially for current orientation
	// Determine if the orientation should change
	// If orientation changing, determine new angle and call driveMotor(neworientation)
	// Look for start trigger on any fixed mic
}

int main(){
	/* DEFINITIONS */
	int i;


	/* MAIN CODE */
	// May include code for dataMinder and Assessor;  readADC, readMic and driveMotor can be functions

}
