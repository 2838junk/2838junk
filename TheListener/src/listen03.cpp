#include<iostream>
#include<sstream>
#include<fstream>
#include<string>

using namespace std;

#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"
#define DATAFILE_PATH "/home"

/* FUNCTIONS */
unsigned int d[1000];
unsigned int mx0[1000];
unsigned int mx1[1000];
unsigned int mx2[1000];


int InitDataFile(int number){
	//derived from test app readMic04.cpp
	//write code to open a file, read in values sequentially and save them to an array
	int i=0;
	int value=0;

	ifstream datadump;

	datadump.open ("datajunk1.txt");

	while (datadump >> value && value != 0)
	{
		// populate values into m1[], m2[], and m3[] for later use as simulated max peak-to-peak reads
		// d[i] has no use; originally to debug
		mx0[i] = value;
		mx1[i] = 4095 - value;
		mx2[i] = 3000;
		i++;
	}

    datadump.close();
	return 1;
}

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
	int i, j, t;
	int nSeries=20;
	int mSum[3]={0,0,0};
	int m0[20], m1[20], m2[20];
	int mla[3]={0,0,0};
	int msa[3]={0,0,0};
	int msaa;
	int nTimeHack=0;

	/* MAIN CODE */
	// May include code for dataMinder and Assessor;  readADC, readMic and driveMotor can be functions

	// DATA INITIALIZER

	InitDataFile(1);			// PROTO ONLY:  populate data from file into three mx arrays
	// read values into current reading arrays (m1, m2, m3)
	for (j=0;j<nSeries;j++){
		m0[j] = mx0[j];
		m1[j] = mx1[j];
		m2[j] = mx2[j];
	}
	nTimeHack = j;		// PROTO ONLY:  in lieu of real time data, nTimeHack indexes through the canned data.

	// DATA MINDER:  read new values, maintain the arrays, and calculate key metrics

	for (t=nTimeHack;t<25;t++){
		cout << "nTimeHack = " << t << endl;

		for (j=19;j>0; j--){
			m0[j]=m0[j-1];
			m1[j]=m1[j-1];
			m2[j]=m2[j-1];
		}

		m0[0]=mx0[t];
		m1[0]=mx1[t];
		m2[0]=mx2[t];

		for (j=0;j<3;j++) {mSum[j]=0;}
		for (j=0;j<nSeries; j++){
			mSum[0]=mSum[0]+m0[j];
			mSum[1]=mSum[1]+m1[j];
			mSum[2]=mSum[2]+m2[j];
		}
		for (i=0; i<3; i++){
			mla[i]= int (mSum[i]/nSeries);
		}

		msa[0]= int ((m0[0]+m0[1])/2);
		msa[1]= int ((m1[0]+m1[1])/2);
		msa[2]= int ((m2[0]+m2[1])/2);
		msaa = int((msa[0]+msa[1]+msa[2])/3);

		//cout << "msa calc:" << m0[0] << "," << m0[1] << "," << msa[0] << endl;

		//FEEDBACK SECTION
		cout << m0[0] << "," << m0[1] << "," << m0[2] << "," << m0[3] << "," << m0[4] << "," << m0[5] << "," << m0[6] << "," << m0[7] << "," << m0[8] << "," << m0[9] << "," << m0[10] << "," << m0[11] << "," << m0[12] << "," << m0[13] << "," << m0[14] << "," << m0[15] << "," << m0[16] << "," << m0[17] << "," << m0[18] << "," << m0[19] << endl;
		cout << m1[0] << "," << m1[1] << "," << m1[2] << "," << m1[3] << "," << m1[4] << "," << m1[5] << "," << m1[6] << "," << m1[7] << "," << m1[8] << "," << m1[9] << "," << m1[10] << "," << m1[11] << "," << m1[12] << "," << m1[13] << "," << m1[14] << "," << m1[15] << "," << m1[16] << "," << m1[17] << "," << m1[18] << "," << m1[19] << endl;
		cout << m2[0] << "," << m2[1] << "," << m2[2] << "," << m2[3] << "," << m2[4] << "," << m2[5] << "," << m2[6] << "," << m2[7] << "," << m2[8] << "," << m2[9] << "," << m2[10] << "," << m2[11] << "," << m2[12] << "," << m2[13] << "," << m2[14] << "," << m2[15] << "," << m2[16] << "," << m2[17] << "," << m2[18] << "," << m2[19] << endl;
		//cout << "mSum: " << mSum[0] << "," << mSum[1] << "," << mSum[2] << endl;
		cout << "mla: " << mla[0] << "," << mla[1] << "," << mla[2] << "(long average)" << endl;
		cout << "msa: " << msa[0] << "," << msa[1] << "," << msa[2] << "(short average);  MSA Average: " << msaa << endl;
		cout << endl;
	}

	return (1);
}
