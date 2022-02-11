#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

bool arr[52]{ 0 }; // A-K Spades; A-K Hearts; A-K Diamonds; A-K Clubs;
char A[13]{ 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
char B[4]{ 'S', 'H', 'D', 'C' };

bool CheckRoyal() {
	if (((arr[0] == 1) && (arr[9] == 1) && (arr[10] == 1) && (arr[11] == 1) && (arr[12] == 1)) ||
		((arr[13] == 1) && (arr[22] == 1) && (arr[23] == 1) && (arr[24] == 1) && (arr[25] == 1)) ||
		((arr[26] == 1) && (arr[35] == 1) && (arr[36] == 1) && (arr[37] == 1) && (arr[38] == 1)) ||
		((arr[39] == 1) && (arr[48] == 1) && (arr[49] == 1) && (arr[50] == 1) && (arr[51] == 1))) {
		return 1;
	}
	return 0;
}
bool CheckSF() {
	for (short j = 0; j < 4; j++) {
		short k = 0;
		for (short i = j * 13; i < j * 13 + 13; i++) {
			if (arr[i] == 1)
				k++;
			else
				k = 0;
			if (k == 5)
				return 1;
		}
	}
	return 0;
}
bool CheckQuads() {
	short arrQ[13]{ 0 };
	for (int i = 0; i < 52; i++) {
		if (arr[i]) {
			arrQ[i % 13]++;
			if (arrQ[i % 13] == 4)
				return 1;
		}
	}
	return 0;
}
bool CheckFH() {
	bool t = 0;
	bool d = 0;
	short arrFH[13]{ 0 };
	for (int i = 0; i < 52; i++)
		if (arr[i] == 1)
			arrFH[i%13]++;
	for (int i = 0; i < 13; i++) {
		if ((arrFH[i] == 3) && (t == 1))
			return 1;
		if (arrFH[i] == 3)
			t = 1;
		if (arrFH[i] == 2)
			d = 1;
	}
	if (t && d)
		return 1;
	return 0;
}
bool CheckFlush() {
	for (int j = 0; j < 4; j++) {
		short k = 0;
		for (int i = j * 13; i < j * 13 + 13; i++) {
			if (arr[i] == 1)
				k++;
			if (k == 5)
				return 1;
		}
	}
	return 0;
}
bool CheckStraight() {
	bool arrS[13]{ 0 };
	for (short i = 0; i < 52; i++) {
		if (arr[i])
			arrS[i % 13] = true;
	}
	short k = 0;
	for (short i = 0; i < 13; i++) {
		if (arrS[i])
			k++;
		else
			k = 0;
		if (k == 5)
			return 1;
	}
	return 0;
}
bool CheckTOAK() {
	short arrTOAK[13]{ 0 };
	for (int i = 0; i < 52; i++) {
		if (arr[i] == 1) {
			arrTOAK[i % 13]++;
			if (arrTOAK[i % 13] == 3)
				return 1;
		}
	}
	return 0;
}
bool CheckTP() {
	bool arrTP[13]{ 0 };
	bool k = 0;
	for (int i = 0; i < 52; i++) {
		if (arr[i] == 1) {
			if (arrTP[i % 13] == 1) {
				if (k)
					return 1;
				k = 1;
			}
			else arrTP[i % 13] = 1;
		}
	}
	return 0;
}
bool CheckPair() {
	bool arrP[13]{ 0 };
	for (int i = 0; i < 52; i++) {
		if (arr[i] == 1) {
			if (arrP[i % 13] == 1) {
				return 1;
			}
			arrP[i % 13] = 1;
		}
	}
	return 0;
}
string CheckHigh() {
	for (short i = 0; i < 52; i += 13) {
		if (arr[i])
			return "A high";
	}
	for (short j = 12; j > 0; j--) {
		for (short i = j; i < 52; i += 13) {
			if (arr[i]) {
				string rez = "";
				rez += A[arr[j] % 13];
				rez += " high";
				return rez;
			}
		}
	}
	return "Error";
}

string CheckComb() {
	if (CheckRoyal())	
		return "Royal flush";
	if (CheckSF())
		return "Straight flush";
	if (CheckQuads())
		return "Four of a kind";
	if (CheckFH())
		return "Fullhouse";
	if (CheckFlush())
		return "Flush";
	if (CheckStraight())
		return "Straight";
	if (CheckTOAK())
		return "Three of a kind";
	if (CheckTP())
		return "Two pairs";
	if (CheckPair())
		return "One pair";
	return CheckHigh();
}

short GenerateCard() {
	short x = rand() % 52;
	while (arr[x] == 1)
		x = rand() % 52;
	arr[x] = 1;
	return x;
}

void Reset() {
	for (short i = 0; i < 52; i++)
		arr[i] = 0;
}

int main() {
	srand(time(NULL));
	short Hand[2];
	short Board[5];
	long t = 100000;
	long NoC[10]{ 0 };
	for (long i = 0; i < t; i++) {
		Hand[0] = GenerateCard();
		Hand[1] = GenerateCard();
		Board[0] = GenerateCard();
		Board[1] = GenerateCard();
		Board[2] = GenerateCard();
		Board[3] = GenerateCard();
		Board[4] = GenerateCard();

		string Comb = CheckComb();
		if (Comb == "Royal flush")
			NoC[0]++;
		else if (Comb == "Straight flush")
			NoC[1]++;
		else if (Comb == "Four of a kind")
			NoC[2]++;
		else if (Comb == "Fullhouse")
			NoC[3]++;
		else if (Comb == "Flush")
			NoC[4]++;
		else if (Comb == "Straight")
			NoC[5]++;
		else if (Comb == "Three of a kind")
			NoC[6]++;
		else if (Comb == "Two pairs")
			NoC[7]++;
		else if (Comb == "One pair")
			NoC[8]++;
		else
			NoC[9]++;




		Reset();
	}
	cout << "Royal flush: " << (double)(NoC[0]) / t * 100 << " %" << endl;
	cout << "Straight flush: " << (double)(NoC[1]) / t * 100 << " %" << endl;
	cout << "Four of a kind: " << (double)(NoC[2]) / t * 100 << " %" << endl;
	cout << "Fullhouse: " << (double)(NoC[3]) / t * 100 << " %" << endl;
	cout << "Flush: " << (double)(NoC[4]) / t * 100 << " %" << endl;
	cout << "Straight: " << (double)(NoC[5]) / t * 100 << " %" << endl;
	cout << "Three of a kind: " << (double)(NoC[6]) / t * 100 << " %" << endl;
	cout << "Two pairs: " << (double)(NoC[7]) / t * 100 << " %" << endl;
	cout << "One pair: " << (double)(NoC[8]) / t * 100 << " %" << endl;
	cout << "X high: " << (double)(NoC[9]) / t * 100 << " %" << endl;
	cout << endl << "Number of tests: " << t;

	return 0;
}