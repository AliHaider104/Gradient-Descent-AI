#include<iostream>
#include<conio.h>
#include<fstream>
#include<time.h>
#include<windows.h>
using namespace std;


const int FEATURES = 4;
const int SSIZE = 150;

void setColor(unsigned short color)
{
	// SET THE COLOR ON CONSLOLE FOR GOOD INTERFACE
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

double	COST(double PredictedValues[], int ActualValues[], int size)
{
	double cost = 0;
	for (int i = 0; i < size; i++)
	{
		cost = cost + (PredictedValues[i] - ActualValues[i])*(PredictedValues[i] - ActualValues[i]);
	}
	cost = cost / SSIZE;
	return cost;
}
void	POPULATE(double DATA_SET[][FEATURES], int LABEL[SSIZE])
{
	ifstream fin;
	fin.open("DATA.txt");

	for (int i = 0; i < SSIZE; i++)
	{
		for (int j = 0; j < FEATURES; j++)
		{
			fin >> DATA_SET[i][j];
		}

		if (i <= 49)
			LABEL[i] = 1;
		if (i > 49 && i <= 99)
			LABEL[i] = 2;
		if (i > 99 && i <= 149)
			LABEL[i] = 3;
	}

}
void	PRINT(double DATA_SET[][FEATURES], int LABEL[SSIZE], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << "	";
		for (int j = 0; j < FEATURES; j++)
		{
			cout << DATA_SET[i][j] << "	";
		}

		cout << LABEL[i] << endl;
	}

}
void	PREPARE_DATA(double DATA_SET[][FEATURES], int LABEL[SSIZE], double TRAING_DATA[][FEATURES], int TRAINING_LABEL[SSIZE / 2], double TESTING_DATA[][FEATURES], int TESTING_LABEL[SSIZE / 2])
{
	for (int i = 0; i < SSIZE / 2; i++)
	{
		for (int j = 0; j < FEATURES; j++)
		{
			TRAING_DATA[i][j] = DATA_SET[i][j];
		}
		TRAINING_LABEL[i] = LABEL[i];
	}


	int x = 0, y = 0;

	for (int i = SSIZE / 2; i < SSIZE; i++)
	{
		for (int j = 0; j < FEATURES; j++)
		{
			TESTING_DATA[x][y] = DATA_SET[i][j];
			y++;
		}
		y = 0;
		TESTING_LABEL[x] = LABEL[i];
		x++;
	}
}
void	RANDOMIZED(double DATA_SET[][FEATURES], int LABEL[])
{
	srand(time(0));

	int data1;
	int data2;

	for (int j = 0; j < SSIZE; j++) {

		data1 = rand() % (SSIZE);
		data2 = rand() % (SSIZE);


		for (int i = 0; i < FEATURES; i++)
			swap(DATA_SET[data1][i], DATA_SET[data2][i]);

		swap(LABEL[data1], LABEL[data2]);

	}
}
void	GRADIENT_DESCENT(double DATA_SET[][FEATURES], int Y[], double Y_[], double W[FEATURES + 1])
{
	setColor(15);
	cout << ">>> STARTING TRAINING PHASE\n\n";
	srand(time(0));

	W[0] = (double)rand() / ((double)RAND_MAX / 1);
	W[1] = (double)rand() / ((double)RAND_MAX / 1);
	W[2] = (double)rand() / ((double)RAND_MAX / 1);
	W[3] = (double)rand() / ((double)RAND_MAX / 1);
	W[4] = (double)rand() / ((double)RAND_MAX / 1);

	for (int i = 0; i < SSIZE / 2; i++)
	{
		Y_[i] = W[0] * 1 + W[1] * DATA_SET[i][0] + W[2] * DATA_SET[i][1] + W[3] * DATA_SET[i][2] + W[4] * DATA_SET[i][3];
	}

	double Cost = COST(Y_, Y, SSIZE / 2);

	setColor(15); //W
	cout << "INITIAL COST : ";
	setColor(12); //R
	cout << Cost << endl;

	setColor(15);
	cout << "WEIGHT VECTOR : "; setColor(12);
	cout << "W[0] : " << W[0] << " W[1] : " << W[1] << " W[2] : " << W[2] << " W[3] : " << W[3] << " W[4] : " << W[4] << endl;

	int ITERATION_COUNT = 0;

	int COUNTER = 0;

	while (Cost != 0 && ITERATION_COUNT <= 1000)
	{
		double YY0 = 0.0;
		double YY1 = 0.0;
		double YY2 = 0.0;
		double YY3 = 0.0;
		double YY4 = 0.0;

		for (int i = 0; i < SSIZE / 2; i++)
		{
			YY0 = YY0 + (Y[i] - Y_[i]) * 1;
			YY1 = YY1 + (Y[i] - Y_[i])	* DATA_SET[i][0];
			YY2 = YY2 + (Y[i] - Y_[i])	* DATA_SET[i][1];
			YY3 = YY3 + (Y[i] - Y_[i])	* DATA_SET[i][2];
			YY4 = YY4 + (Y[i] - Y_[i])	* DATA_SET[i][3];
		}

		W[0] = W[0] - (0.01)*(-1)*(YY0) / SSIZE;
		W[1] = W[1] - (0.01)*(-1)*(YY1) / SSIZE;
		W[2] = W[2] - (0.01)*(-1)*(YY2) / SSIZE;
		W[3] = W[3] - (0.01)*(-1)*(YY3) / SSIZE;
		W[4] = W[4] - (0.01)*(-1)*(YY4) / SSIZE;


		for (int i = 0; i < SSIZE / 2; i++)
		{
			Y_[i] = W[0] * 1 + W[1] * DATA_SET[i][0] + W[2] * DATA_SET[i][1] + W[3] * DATA_SET[i][2] + W[4] * DATA_SET[i][3];


		}


		Cost = COST(Y_, Y, SSIZE / 2);

		COUNTER++;
		if (COUNTER == 100)
		{
			setColor(15);
			cout << "\n>>>AFTER " << ITERATION_COUNT + 1 << " ITERATIONS\n\n";
			COUNTER = 0;
			cout << "NEW COST : "; setColor(10);
			cout << Cost << endl; setColor(15);
			cout << "WEIGHT VECTOR : "; setColor(10);
			cout << "W[0] : " << W[0] << " W[1] : " << W[1] << " W[2] : " << W[2] << " W[3] : " << W[3] << " W[4] : " << W[4] << endl;

		}

		ITERATION_COUNT++;

	}
	setColor(15);
	cout << "\n>>> ENDING TRAINING PHASE\n";
}
void	TESTING(double DATA_SET[][FEATURES], int LABEL[], double W[])
{

	setColor(15);
	cout << "\n\n>>> STARTING TESTING PHASE ";
	double Y_[SSIZE / 2];
	for (int i = 0; i < SSIZE / 2; i++)
	{
		Y_[i] = W[0] * 1 + W[1] * DATA_SET[i][0] + W[2] * DATA_SET[i][1] + W[3] * DATA_SET[i][2] + W[4] * DATA_SET[i][3];


		if (Y_[i] <= 1.5)
			Y_[i] = 1;

		if (1.5 < Y_[i] && Y_[i] <= 2.5)
			Y_[i] = 2;

		if (2.5 < Y_[i])
			Y_[i] = 3;

	}

	int NotMatching = 0;
	for (int i = 0; i < SSIZE / 2; i++)
	{


		if (LABEL[i] - Y_[i] != 0)
		{
			NotMatching++;
		}
	}
	cout << "\n\nNUMBER OF MISMATCHES : ";
	setColor(12);
	cout << NotMatching;
}
int main()
{

	double	DATA_SET[SSIZE][FEATURES];
	int		LABEL[SSIZE];

	POPULATE(DATA_SET, LABEL);

	double	TRAINING_DATA[SSIZE / 2][FEATURES];
	int		TRAINING_LABEL[SSIZE / 2];

	double	TESTING_DATA[SSIZE / 2][FEATURES];
	int		TESTING_LABEL[SSIZE / 2];

	RANDOMIZED(DATA_SET, LABEL);

	// RANDOMIZED THE DATA
	PREPARE_DATA(DATA_SET, LABEL, TRAINING_DATA, TRAINING_LABEL, TESTING_DATA, TESTING_LABEL);


	double		Y_[SSIZE / 2];			//GUESS
	double		W[FEATURES + 1];		//WEIGHT VECTOR

	GRADIENT_DESCENT(TRAINING_DATA, TRAINING_LABEL, Y_, W);


	TESTING(TRAINING_DATA, TRAINING_LABEL, W);

	_getch();

}