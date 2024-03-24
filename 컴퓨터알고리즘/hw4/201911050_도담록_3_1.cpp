#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
int C[101][2]; // weight, value;
int K[50000][101];


int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i < n+1; i++) {
		int ni, mi;
		cin >> ni>> mi;
		C[i][0] = ni;
		C[i][1] = mi;
	}
	for (int x = 0; x <= n; x++) {
		K[x][0] = 0;
	}
	for (int i = 0; i <= m; i++) {
		K[0][i] = 0;
	}
	for (int x = 1; x <= m; x++) {
		for (int j = 1; j <= n; j++) {
			K[x][j] = K[x][ j - 1];
			if (C[j][0] <= x) {
				if (K[x][j] < K [x - C[j][0]] [j - 1]+C[j][1]) {
					K[x][j] = K [x - C[j][0]] [j - 1] + C[j][1];
				}
			}
		}
	}
	cout << K[m][n];
	return 0;
}