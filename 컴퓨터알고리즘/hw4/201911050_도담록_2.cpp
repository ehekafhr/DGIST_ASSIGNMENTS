#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
int C[1000][2];
int D[1000001];
int main()
{	
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int s, e;
		cin >> s >> e;
		C[i][0] = s;
		C[i][1] = e;
	}
	for (int i = 0; i < 1000001; i++) {
		D[i] = -1;
	}
	for (int i = 0; i < n; i++) {
		if (D[C[i][1]] < C[i][0]) {
			D[C[i][1]] = C[i][0];
		}
	}
	int curtime = 0;
	int cnt = 0;
	for(int i = 0; i < 1000001; i++) {
		if (D[i] >= curtime) {
			curtime = i;
			cnt += 1;
		}
	}
	cout << cnt;
	return 0;
}