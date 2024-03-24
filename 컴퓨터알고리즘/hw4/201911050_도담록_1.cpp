#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
int C[4000][4000];
void lcs() {
	string a, b;
	cin >> a;
	cin >> b;
	int n0 = a.length();
	int n1 = b.length();
	int cnt = 0;
	int max = n0;
	char answer[4000]{ 0 };

	if (max < n1) max = n1;
	for (int i = 0; i < max; i++) {
		for (int j = 0; j < max; j++) {
			C[i][j] = 0;
		}
	}
	for (int i = 1; i < n0 + 1; i++) {
		for (int j = 1; j < n1 + 1; j++) {
			if (a[i - 1] == b[j - 1]) {
				C[i][j] = C[i - 1][j - 1] + 1;

				cnt += 1;
			}
			else {
				if (C[i - 1][j] < C[i][j - 1]) {
					C[i][j] = C[i][j - 1];
				}
				else {
					C[i][j] = C[i - 1][j];
				}
			}
		}
		cout << endl;
	}
	for (int i = 0; i < n0 + 1; i++) {
		for (int j = 0; j < n1 + 1; j++) {
			cout << C[i][j] << " ";
		}
		cout << endl;
	}
	int cntx = n0;
	int cnty = n1;
	while (true) {
		if (cnty < 1 or cntx < 1) break;
		if (C[cntx][cnty] == C[cntx - 1][cnty ] + 1 and C[cntx][cnty] == C[cntx][cnty-1]+1) {
			answer[cnt] = b[cnty - 1];
			cnt += 1;
			cnty -= 1;
			cntx -= 1;
		}
		else if (C[cntx][cnty] == C[cntx][cnty - 1]) {
			cnty -= 1;
		}
		else {
			cntx -= 1;
		}
	}
	for (int i = cnt - 1; i >= 0; i--) {
		cout << answer[i];
	}
}
int main()
{	
	cout << "¨ö";
	return 0;
}