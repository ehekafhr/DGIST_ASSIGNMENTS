#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <limits>
#include <math.h>
using namespace std;
long long X[101];
long long Q[100][100];
long long main()
{
	long long n;
	cin >> n;

	long long a0, b0;
	cin >> a0 >> b0;
	X[0] = a0; X[1] = b0;

	for (long long i = 1; i < n; i++) {
		long long a, b;
		cin >> a >> b;
		X[i + 1] = b;
	}
	for (long long i = 1; i < n + 1; i++) {
		for (long long j = 1; j < n + 1; j++) {
			Q[i][j] = 9000000000000;
		}
	}
	for (long long i = 1; i <= n; i++) {
		Q[i][i] = 0;
	}
	for (long long l = 2; l <= n + 3; l++) {
		for (long long i = 1; i < n - l + 3; i++) {
			long long j = l + i - 1;
			for (long long k = i; k < j + 1; k++) {
				long long q = Q[i][k] + Q[k + 1][j] + X[i - 1] * X[k] * X[j];

				if (q < Q[i][j]) {
					Q[i][j] = q;
				}
			}
		}

	}


	cout << Q[1][n];
	return 0;
}