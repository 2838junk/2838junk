#include<iostream>
#include<sstream>
#include<fstream>
#include<string>

using namespace std;

#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"

/* FUNCTIONS */

int readAnalog(int number){
	// Argument is analog input number (e.g. "0" for AIN0/P9_39);
	// Note: At boot, need to enable BB-ADC in /sys/devices/bone_capemgr.9/slots
	stringstream ss;
	ss << ADC_PATH << number << "_raw";		// Concatenate path to correct analog input
	fstream fs;
	fs.open(ss.str().c_str(), fstream::in);
	fs >> number;							// Re-purpose int number as output of AIN
	fs.close();
	return number;							// Return single read value of AIN#
}

int readMic(int nMic){
	// Argument is microphone number; could be fixed or moving
	// Note:  This should be converted to a time-based loop of greater than 20 ms duration.  One example used 50 ms.
	int i;						// increment
	int samples = 1010;			// number of reads per loop; >> convert to milliseconds?
	int signalMax = 0;			// max/min values from the series
	int signalMin = 4095;
	//char filename;				//just for dumping data to file for analysis & development

	//cout << endl <<  "Starting to read microphone: " << loops << " loops of " << samples << " samples." << endl;

	ofstream datadump;
	datadump.open ("datadump_x.txt");   //open a file to output the data

	// Read a sample series of values from the analog input using readADC(AIN#)
	for (i=0;i<samples;i++){
		int value = readAnalog(nMic);
		if (value>signalMax){
			signalMax=value;
		}
		if (value<signalMin) {
			signalMin = value;
		}
		datadump << value << endl;
    }

	// Calculate average (max?) peak-to-peak value of sample set; calculate any other values?
	int peakToPeak = signalMax - signalMin;
	datadump << "p-p (" << nMic << ") = " << peakToPeak;
	datadump.close();
	return peakToPeak;

	// Return peak-to-peak value
}

int dataMinder(){
	// No argument; called periodically; Might combine with readMic
	// Requests readMic() for each of the available microphones
	// Maintains data arrays;
	// Calculates basic metrics (short average, long average, etc.)
	// Returns success/failure;
	return (1);
}

int driveMotor(int neworientation){
	// Argument is a value that indicates the motor orientation (degree, value, mic#?)
	// Determine path (direction, distance, speed(?)
	// Send commands through GPIO output to move motor
	// Returns success/failure of command issuance
	return (1);
}

int Assessor(){
	// No argument; called periodically;  knows current focus and orientation
	// Determine the loudest orientation
	// Determine if any start triggers occurred
	// Determine if any end triggers occurred, especially for current orientation
	// Determine if the orientation should change
	// If orientation changing, determine new angle and call driveMotor(neworientation)
	// Look for start trigger on any fixed mic
	return (1);
}

int main(){
	/* DEFINITIONS */
	int i;


	/* MAIN CODE */
	// May include code for dataMinder and Assessor;  readADC, readMic and driveMotor can be functions
	return (1);
}
