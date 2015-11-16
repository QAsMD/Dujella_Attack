// Dujella_Attack.cpp : Defines the entry point for the console application.
//
#pragma once
#include "Dujella_Attack.h"

using namespace std;

ERROR_CODE Dujella_Attack(
	__in LINT E,
	__in LINT N,
	__out LINT *p,
	__out LINT *q,
	__out LINT *D
	)
{
#ifdef DBG_PRINT
	cout << "Starting GWA with:\nE:" << E.decstr() << endl;
	cout << "N:" << N.decstr() << endl;
#endif
	vector<LINT> P;
	vector<LINT> V;
	vector<LINT> H;
	vector<LINT> Z;

	H.push_back(E);
	LINT N_modified = N + 1 - 2 * N.root();
	Z.push_back(N_modified);
	vector<LINT> potential_D;
	vector<LINT> potential_K;
	LINT limitD = root(root(N)) / 3 - 1;

	LINT M = LINT("10110100");
	LINT LC = mexp(M, E, N);
	return SUCCESS;
};
int _tmain(int argc, _TCHAR* argv[])
{
	ERROR_CODE status = UNINITIALIZED;
	vector <LINT> primes_vector;
	LINT E;
	LINT N;
	LINT D;
	LINT P;
	LINT Q;
	LINT origin_D;
	LINT origin_P;
	LINT origin_Q;
	int key_index = 0;

#ifdef KEY_TXT_PRINT
	ofstream FILE;
	string rez = "";
	FILE.open("key for debug.txt");
#endif

	while (1 == 1)
	{
		char choice;

		cout << "\nPlease, choose what option you want:\n";
		cout << "1 - Generate vulnerable keys with specified length and break them\n";
		cout << "2 - Input prepared keys from file keys.txt and test them for being vulnerable\n";
		cout << "3 - Exit\n";

		scanf(" %c", &choice);

		switch (choice) {
		case '1':
		{
			vector<int> keys = { 1024 };//64, 128, 256, 512, 1024, 2048, 4096};

			for (unsigned int counter = 0; counter < keys.size(); counter++)
			{
				status = Prime_Number_Generator(keys[counter], &P, &Q);

				cout << "q-p = " << Q - P << endl;
				LINT mistery_D = LINT(10000);
				if (status != SUCCESS)
					_CrtDbgBreak();
				origin_P = P;
				origin_Q = Q;
				status = Vulnerable_Generator(P, Q, &E, &N, &origin_D);
				if (status != SUCCESS)
					_CrtDbgBreak();

				int time = GetTickCount();

				//status = Dujella_Attack(E, N, &P, &Q, &D);
				D = LINT(1);
				P = LINT(1);
				Q = LINT(1);

				if (status != SUCCESS)
					_CrtDbgBreak();
#ifdef DBG_PRINT
				cout << "The key is: " << D.decstr() << endl;
				cout << "P is " << P.decstr() << endl;
				cout << "Q is " << Q.decstr() << endl;
#endif
				//cout << "\norigin P: " << origin_P.decstr() << endl;
				if (origin_D == D)
					cout << "For key length " << keys[counter] << " Vinere succedeed in " << GetTickCount() - time << " ticks" << endl;
				if ((origin_P == P) && (origin_Q == Q))
					cout << "Primes found correctly" << endl;


#ifdef KEY_TXT_PRINT				
				rez += E.decstr();	
				rez += "\n";
				rez += N.decstr();
				rez += "\n";
				rez += D.decstr();
				rez += "\n\n";
				FILE << rez;
#endif
			}

#ifdef KEY_TXT_PRINT
			FILE.close();
#endif
		}
			break;
		case '2':
		{
			string line_E;
			string line_N;
			ifstream myfile("keys.txt");
			LINT lint_E;
			LINT lint_N;
			LINT output_D;

			if (!myfile.is_open())
			{
				cout << "Couldn't open file, error." << endl;
				goto clean0;
			}

			while (!myfile.eof())
			{
				output_D = KEY_NOT_FOUND;
				getline(myfile, line_E);
				lint_E = LINT(line_E.c_str());
				getline(myfile, line_N);
				lint_N = LINT(line_N.c_str());


#ifdef DBG_PRINT
				cout << "Starting Vinere attack with E: " << lint_E << endl;
				cout << " and N: " << lint_N << endl;
#endif
				int time = GetTickCount();
				status = Dujella_Attack(lint_E, lint_N, &P, &Q, &output_D);
				if (status != SUCCESS)
					_CrtDbgBreak();

				if (output_D != KEY_NOT_FOUND)
				{
					cout << "The key is: " << output_D.decstr() << endl;
					cout << "For key length " << (line_E.length() + line_N.length()) << " Vinere succedeed in " << GetTickCount() - time << " ticks" << endl;
					cout << "P is " << P.decstr() << endl;
					cout << "Q is " << Q.decstr() << endl;
				}
				else
				{
					cout << "The key is not vulnerable to Vinere attack. Moving to next key." << endl;
				}
			}
		}
			break;
		case '3':
		{
			goto clean0;
		}
			break;
		default:
			cout << "Invalid choice specified. Re-enter your choice" << endl;
		}
	}

clean0:
	return 0;
}
