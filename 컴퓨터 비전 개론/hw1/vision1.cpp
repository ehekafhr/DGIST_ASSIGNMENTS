#include <iostream>
#include <math.h>
#define ROW 512
#define COL 512

unsigned char readimage[ROW * COL], writeimage[ROW * COL], buffer[ROW * COL];
void changeintensity(int val)
{
	int i, j;
	int temp;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) {
			temp = (int)readimage[i * COL + j] + val;
			if (temp < 0) temp = 0;
			if (temp > 255) temp = 255;
			buffer[i * COL + j] = temp;
		}
}
void imagenormalize(unsigned char inimg[])
{
	int i, j, min = 255, max = 0;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) {
			if (min > inimg[i * COL + j]) min = inimg[i * COL + j];
			if (max < inimg[i * COL + j]) max = inimg[i * COL + j];
		}
	std::cout << min << " " << max;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) {
			inimg[i * COL + j] = (int)(255.0 * (inimg[i * COL + j] - min) /
				(double)(max - min));
		}
}

void sobel1d(unsigned char out[], unsigned char in[]) {
	int i, j, k, m;
	int sumx = 0, sumy = 0, val = 0;
	int xwin[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int ywin[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	for (i = 1; i < ROW - 1; i++)
		for (j = 1; j < COL - 1; j++) {
			sumx = sumy = 0;
			for (k = -1; k <= 1; k++)
				for (m = -1; m <= 1; m++) {
					sumx += in[(i + k) * COL + (j + m)] * xwin[k + 1][m + 1];
					sumy += in[(i + k) * COL + (j + m)] * ywin[k + 1][m + 1];
				}
			val = 2.0 * (abs(sumx) + abs(sumy));
			if (val > 255) val = 255;
			out[i * COL + j] = val;
		}
}
void median(unsigned char out[][COL], unsigned char image[][COL], int size)
{
	int i, j;
	int k, l;
	int first, search, temp, count;
	int* med = new int[size * size];
	for (i = (int)(size / 2); i < ROW - (int)(size / 2); i++)
		for (j = (int)(size / 2); j < COL - (int)(size / 2); j++) {
			count = 0;
			for (k = -1 * (int)(size / 2); k <= (int)(size / 2); k++)
				for (l = -1 * (int)(size / 2); l <= (int)(size / 2); l++)
					med[count++] = image[i + k][j + l];
			for (first = 0; first < size * size - 1; first++)
				for (search = first + 1; search < size * size; search++)
					if (med[search] > med[first]) {
						temp = med[search];
						med[search] = med[first];
						med[first] = temp;
					}
			out[i][j] = med[12];
		}
	delete[] med;
}

void average(unsigned char out[][COL], unsigned char image[][COL], int size)
{
	int i, j;
	int k, l;
	int temp ;
	for (i = (int)(size / 2); i < ROW - (int)(size / 2); i++)
		for (j = (int)(size / 2); j < COL - (int)(size / 2); j++) {
			int temp = 0;
			for (k = -1 * (int)(size / 2); k <= (int)(size / 2); k++)
				for (l = -1 * (int)(size / 2); l <= (int)(size / 2); l++) {
					temp += image[i + k][j + l];
				}
			temp /= size*size;
			out[i][j] = temp;
		}
}

void sobel(unsigned char out[][COL], unsigned char in[][COL]) {
	int i, j, k, m;
	int sumx = 0, sumy = 0, val = 0;
	int xwin[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int ywin[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	for (i = 1; i < ROW - 1; i++)
		for (j = 1; j < COL - 1; j++) {
			sumx = sumy = 0;
			for (k = -1; k <= 1; k++)
				for (m = -1; m <= 1; m++) {
					sumx += in[(i + k)][(j + m)] * xwin[k + 1][m + 1];
					sumy += in[(i + k)][(j + m)] * ywin[k + 1][m + 1];
				}
			if (sumx < 0) {
				sumx = -sumx;
			}
			if (sumy < 0) {
				sumy = -sumy;
			}
			val = 2 * (sumx+sumy);
			if (val > 255) val = 255;
			out[i][j] = val;
		}
}

int main()
{
	char readfilename[30]{};
	std::cin >> readfilename;
	char writefilename[30]{};
	std::cin >> writefilename;
	char header[2048];
	FILE* fpread, * fpwrite;
	fpread = fopen(readfilename, "rb");
	fpwrite = fopen(writefilename, "wb");
	if (fpread == NULL || fpwrite == NULL) { printf("\nFile Open Error"); return 0; }
	fread(header, 1, 1078, fpread); // image has been vertically inversed(upside down) by the header information
	fread(readimage, 1, ROW * COL, fpread);
	changeintensity(0);
	//imagenormalize(buffer);
	unsigned char input[512][512];
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			input[i][j] = readimage[512 * i + j];
		}
	}
	unsigned char tempoutput1[512][512];
	median(tempoutput1, input, 5);
	unsigned char output[512][512];
	sobel(output, tempoutput1);
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			buffer[512 * i + j] = output[i][j];
		}
	}
	fwrite(header, 1, 1078, fpwrite);
	fwrite(buffer, 1, ROW * COL, fpwrite);
	fclose(fpread);
	fclose(fpwrite);
	return 0;
}

