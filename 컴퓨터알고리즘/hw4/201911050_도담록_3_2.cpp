#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
int C[1000][3]; // weight, value, 썼는가;
int K[1001]; // cap.
int countC[50001];
int countK[50001];
//물건들을 value가 큰 것부터 내림차순으로 정리
//cap가 작은 knapsack부터 올라가며
int main()
{
	for (int i = 0; i < 1000; i++) {
		C[i][2] = 0; //안씀
	}
	//n=item 수. m= knapsack 수.
	int n, m;
	cin >> n >> m;
	//C에 물건들 넣기. C[k][0]은 weight, [1]은 value!
	for (int i = 0; i < n; i++) {
		int ni, mi;
		cin >> ni >> mi;
		C[i][0] = ni;
		C[i][1] = mi;
	}
	//bubblesort로 정렬
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j<n-1-i; j++) {
			if (C[j][1] < C[j+1][1]) { 
				int jval = C[j][1];
				int jwei = C[j][0];
				C[j][1] = C[j + 1][1];
				C[j][0] = C[j + 1][0];
				C[j + 1][1] = jval;
				C[j + 1][0] = jwei;

			}
		}
	}
	//K에 물건들 넣기(오름차순 정렬)
	for (int i = 0; i < 50001; i++) {
		countK[i] = 0;
	}
	for (int i = 0; i < m; i++){
		int capacity;
		cin >> capacity;
		countK[capacity] += 1;
	}
	int cntK = 0;
	for (int i = 0; i < 50001; i++) {
		while (countK[i] != 0) {
			K[cntK] = i;
			countK[i] -= 1;
			cntK += 1;
		}
	}
	int ans = 0;//ans
	for (int i = 0; i<m; i++) {
		for (int j = 0; j < n; j++) {
			if (K[i] >= C[j][0] and C[j][2] == 0) {
				C[j][2] = 1;
				ans += C[j][1];
				break;
			}
		}
	}
	cout << ans;
	return 0;
}