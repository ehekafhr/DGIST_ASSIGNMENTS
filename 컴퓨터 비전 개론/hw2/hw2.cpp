#include <iostream>
#include <math.h>
#define ROW 256
#define COL 256
#include <fstream>
using namespace std;
unsigned char readimage[ROW * COL * 3], writeimage[ROW * COL * 3], buffer[ROW * COL * 3];
double pi = 3.142592;


/// <summary>
/// filters
/// </summary>
float sharpen_filter[9] = { 0,1,0,1,-4,1,0,1,0 };
float average_filter[9] = { 0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1 };
float laplacian_filter[9] = { 1,1,1,1,-8,1,1,1,1 };
struct Pixel {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

void Pins(Pixel p, int x, int y, unsigned char cimg[]) {
	int base = 3 * (x + y * ROW);
	cimg[base + 2] = p.r;
	cimg[base + 1] = p.g;
	cimg[base] = p.b;
}

Pixel retP(int x, int y, unsigned char gimg[]) {
	Pixel p;
	int base = 3 * (x + y * ROW);
	p.r = gimg[base + 2];
	p.g = gimg[base + 1];
	p.b = gimg[base];
	return p;
}



void imaghistogram(unsigned char inimg[]) {
	int i, j, r;
	int temp;
	unsigned int histo[256];
	double pdf[256], cdf[256], s;
	for (i = 0; i < 256; i++) histo[i] = 0;
	for (i = 0; i < ROW * 3; i++)
		for (j = 0; j < COL * 3; j++)
			//change
			histo[0] = 0;
	for (i = 0; i < 256; i++) {
		pdf[i] = histo[i] / (double)(ROW * 3 * COL * 3);
		if (i == 0) cdf[i] = pdf[i];
		else cdf[i] = cdf[i - 1] + pdf[i];
	}
	for (i = 0; i < ROW * 3; i++)
		for (j = 0; j < COL * 3; j++) {
			r = readimage[i * COL * 3 + j];
			s = 255.0 * cdf[r];
			buffer[i * COL * 3 + j] = int(s + 0.5);
		}
}

Pixel curr_convolution3(int x, int y, float* filter, unsigned char gimg[]) {
	float r = 0;
	float g = 0;
	float b = 0;
	//y=-1
	int inpval = x + (y - 1) * ROW - 1;

	//-1,-1
	if (y > 0 && x > 0) {
		float filt = filter[0];
		Pixel i1 = retP(x - 1, y - 1, gimg);
		r += i1.r * filt;
		g += i1.g * filt;
		b += i1.b * filt;
	}
	//-1,0
	if (x > 0) {
		float filt = filter[1];
		Pixel i1 = retP(x - 1, y, gimg);
		r += i1.r * filt;
		g += i1.g * filt;
		b += i1.b * filt;
	}
	//-1,1
	if (x > 0 && y < ROW - 1) {
		float filt = filter[2];
		Pixel i1 = retP(x - 1, y + 1, gimg);
		r += i1.r * filt;
		g += i1.g * filt;
		b += i1.b * filt;
	}

	//0,-1
	if (y > 0) {
		float filt = filter[3];
		Pixel i1 = retP(x, y - 1, gimg);
		r += i1.r * filt;
		g += i1.g * filt;
		b += i1.b * filt;
	}
	//0,0
	float filt = filter[4];
	Pixel i1 = retP(x, y, gimg);
	r += i1.r * filt;
	g += i1.g * filt;
	b += i1.b * filt;
	//0,1
	if (y < COL - 1) {
		float filt = filter[5];
		Pixel i1 = retP(x, y + 1, gimg);
		r += i1.r * filt;
		g += i1.g * filt;
		b += i1.b * filt;
	}

	//1,-1
	if (x < COL - 1 && y>0) {
		float filt = filter[6];
		Pixel i1 = retP(x + 1, y - 1, gimg);
		r += i1.r * filt;
		g += i1.g * filt;
		b += i1.b * filt;
	}
	//1,0
	if (x < COL - 1) {
		float filt = filter[7];
		Pixel i1 = retP(x + 1, y, gimg);
		r += i1.r * filt;
		g += i1.g * filt;
		b += i1.b * filt;
	}
	//1,1
	if (y < ROW - 1 && x < COL - 1) {
		float filt = filter[8];
		Pixel i1 = retP(x + 1, y + 1, gimg);
		r += i1.r * filt;
		g += i1.g * filt;
		b += i1.b * filt;
	}

	if (r < 0) r = 0;
	else if (r > 255)r = 255;
	if (g < 0) g = 0;
	else if (g > 255) g = 255;
	if (b < 0) b = 0;
	else if (b > 255) b = 255;

	Pixel p;
	memset(&p, 0, sizeof(p));

	p.r = (unsigned char)r;
	p.g = (unsigned char)r;
	p.b = (unsigned char)b;
	return p;
}

void convolution3(unsigned char cimg[], unsigned char gimg[], float* filter) {
	int i, j;
	for (int j = 0; j < COL; j++) {
		for (int i = 0; i < ROW; i++) {
			Pixel p = curr_convolution3(i, j, filter, gimg);
			Pins(p, i, j, cimg);
		}
	}
}
//붉은색 추출
void justred(unsigned char gimg[]) {
	for (int i = 0; i < ROW * COL * 4; i += 3) {
		gimg[i + 0] = 0;
		gimg[i + 1] = 0;
	}
}
void minmaxnormalizationr(unsigned char gimg[]) {
	int min = 255;
	int max = 0;
	for (int i = 0; i < ROW * COL * 4; i += 3) {
		//red
		if (gimg[i + 2] < min) min = gimg[i + 2];
		if (gimg[i + 2] > max) max = gimg[i + 2];
	}
	float rate = 255 / (max - min);
	for (int i = 0; i < ROW * COL * 4; i += 3) {
		float temp = gimg[i + 2] * rate;
		gimg[i + 2] = (unsigned char)temp;
	}
}

void minmaxnormalizationg(unsigned char gimg[]) {
	int min = 255;
	int max = 0;
	for (int i = 0; i < ROW * COL * 4; i += 3) {
		//red
		if (gimg[i + 2] < min) min = gimg[i + 2];
		if (gimg[i + 2] > max) max = gimg[i + 2];
	}
	float rate = 0;
	if (max - min != 0) {
		rate = 255 / (max - min);
	}

	for (int i = 0; i < ROW * COL * 4; i += 3) {
		float temp = gimg[i + 2] * rate;
		gimg[i + 2] = (unsigned char)temp;
	}
}

void minmaxnormalizationb(unsigned char gimg[]) {
	int min = 255;
	int max = 0;
	for (int i = 0; i < ROW * COL * 4; i += 3) {
		//red
		if (gimg[i] < min) min = gimg[i];
		if (gimg[i] > max) max = gimg[i];
	}
	float rate = 0;
	if (max != min) {
		rate = 255 / (max - min);
	}
	for (int i = 0; i < ROW * COL * 4; i += 3) {
		float temp = gimg[i] * rate;
		gimg[i] = (unsigned char)temp;
	}
}

void minmaxnormalization(unsigned char gimg[]) {
	minmaxnormalizationr(gimg);
	minmaxnormalizationg(gimg);
	minmaxnormalizationb(gimg);
}
void de(unsigned char gimg[], unsigned char cimg[]) {
	Pixel p9;
	for (int i = 1; i < ROW - 1; i++) {
		for (int j = 1; j < COL - 1; j++) {
			Pixel p0 = retP(i - 1, j - 1, gimg);
			Pixel p1 = retP(i, j - 1, gimg);
			Pixel p2 = retP(i + 1, j - 1, gimg);
			Pixel p3 = retP(i - 1, j, gimg);
			Pixel p4 = retP(i, j, gimg);
			Pixel p5 = retP(i + 1, j, gimg);
			Pixel p6 = retP(i - 1, j + 1, gimg);
			Pixel p7 = retP(i, j + 1, gimg);
			Pixel p8 = retP(i + 1, j + 1, gimg);
			if (p0.r > 180 or p1.r > 180 or p2.r > 180 or p3.r > 180 or p4.r > 180 or p5.r > 180 or p6.r > 180 or p7.r > 180 or p8.r > 180) {
				p9.r = 200;
				p9.g = p4.g;
				p9.b = p4.b;
				Pins(p9, i, j, cimg);
			}
		}
	}
}
static int datas[4];
int whereareyou1(unsigned char gimg[]) {
	int i, j, k;
	int validvalue = 0;
	int ex = 235;
	for (j = 0; j < COL; j++) {
		for (i = 0; i < ROW; i++) {
			Pixel p = retP(i, j, gimg);
			if (p.r > ex) {
				validvalue += 1;
			}
		}
	}
	//cout << "validvalue is: " << validvalue << endl;
	float imm = validvalue * 0.8;
	int size = 0;
	for (size = 32; size < ROW; size += 6) {
		int max = 0;
		int cx = 0;
		int cy = 0;
		//위치를 잡고, 그 위치에서 cnt를 구함.
		//j는 세로 i는 가로 크키
		for (j = 0; j < COL - size; j += 3) {
			for (i = 0; i < ROW - size; i += 3) {
				int cnt = 0;
				bool fir = true;
				for (int r = 0; r < size; r++) {
					for (int s = 0; s < size; s++) {
						Pixel p = retP(r + i, s + j, gimg);
						if (p.r > ex) cnt += 1;
					}
				}
				if (cnt > max) {
					max = cnt;
					cx = i;
					cy = j;
				}
				if (cnt == max and fir) {
					cx = i - (size / 2);
					fir = false;

				}


			}
		}
		if (max >= imm) {
			//cout << "imm is " << imm << " max is " <<max << endl;
			//cout << "x is " << cx << " y is " << cy << endl;
			//cout << "size is" << size << endl;
			Pixel p;
			p.g = 255;
			p.b = 255;
			p.r = 255;
			for (int r = 0; r < size; r++) {
				Pins(p, cx + r, cy, gimg);
				Pins(p, cx, cy + r, gimg);
				Pins(p, cx + size, cy + r, gimg);
				Pins(p, cx + r, cy + size, gimg);
			}
			Pins(p, cx + size, cy + size, gimg);
			Pins(p, 0, 0, gimg);
			datas[0] = size;
			datas[1] = cx;
			datas[2] = cy;
			datas[3] = validvalue;
			return 0;
		}
	}
	return 0;
}

int whereareyou8(unsigned char gimg[]) {
	int i, j, k;
	int validvalue = 0;
	int ex = 180;
	for (j = 0; j < COL; j++) {
		for (i = 0; i < ROW; i++) {
			Pixel p = retP(i, j, gimg);
			if (p.r > ex) {
				validvalue += 1;

			}
		}
	}
	//cout << "validvalue is: " << validvalue << endl;
	float imm = validvalue * 0.95;
	int size = 0;
	for (size = 32; size < ROW; size += 8) {
		int max = 0;
		int cx = 0;
		int cy = 0;
		//위치를 잡고, 그 위치에서 cnt를 구함.
		//j는 세로 i는 가로 크키
		for (j = 0; j < COL - size; j += 3) {
			for (i = 0; i < ROW - size; i += 3) {
				int cnt = 0;
				bool fir = true;
				for (int r = 0; r < size; r++) {
					for (int s = 0; s < size; s++) {
						Pixel p = retP(r + i, s + j, gimg);
						if (p.r > ex) cnt += 1;
					}
				}
				if (cnt > max) {
					max = cnt;
					cx = i;
					cy = j;
				}
				if (cnt == max and fir) {
					cx = i - (size / 6);
					fir = false;

				}


			}
		}
		if (max >= imm) {
			//cout << "imm is " << imm << " max is " << max << endl;
			//cout << "x is " << cx << " y is " << cy << endl;
			//cout << "size is" << size << endl;
			Pixel p;
			p.g = 255;
			p.b = 255;
			p.r = 255;
			for (int r = 0; r < size; r++) {
				Pins(p, cx + r, cy, gimg);
				Pins(p, cx, cy + r, gimg);
				Pins(p, cx + size, cy + r, gimg);
				Pins(p, cx + r, cy + size, gimg);
			}
			Pins(p, cx + size, cy + size, gimg);
			Pins(p, 0, 0, gimg);
			datas[0] = size;
			datas[1] = cx;
			datas[2] = cy;
			datas[3] = validvalue;
			return 0;
		}
	}
	return 0;
}
Pixel medP(int x, int y, unsigned char gimg[]) {
	int i;
	unsigned char r[9]{};
	unsigned char g[9]{};
	unsigned char b[9]{};
	//-1,-1
	if (y > 0 && x > 0) {
		Pixel i1 = retP(x - 1, y - 1, gimg);
		r[0] = i1.r;
		g[0] = i1.g;
		b[0] = i1.b;
	}
	//-1,0
	if (x > 0) {
		Pixel i1 = retP(x - 1, y, gimg);
		r[1] = i1.r;
		g[1] = i1.g;
		b[1] = i1.b;
	}
	//-1,1
	if (x > 0 && y < ROW - 1) {
		Pixel i1 = retP(x - 1, y + 1, gimg);
		r[2] = i1.r;
		g[2] = i1.g;
		b[2] = i1.b;
	}

	//0,-1
	if (y > 0) {
		Pixel i1 = retP(x, y - 1, gimg);
		r[3] = i1.r;
		g[3] = i1.g;
		b[3] = i1.b;
	}
	//0,0
	Pixel i1 = retP(x, y, gimg);
	r[4] = i1.r;
	r[4] = i1.g;
	r[4] = i1.b;
	//0,1
	if (y < COL - 1) {
		Pixel i1 = retP(x, y + 1, gimg);
		r[5] = i1.r;
		g[5] = i1.g;
		b[5] = i1.b;
	}

	//1,-1
	if (x < COL - 1 && y>0) {
		Pixel i1 = retP(x + 1, y - 1, gimg);
		r[6] = i1.r;
		g[6] = i1.g;
		b[6] = i1.b;
	}
	//1,0
	if (x < COL - 1) {
		Pixel i1 = retP(x + 1, y, gimg);
		r[7] = i1.r;
		g[7] = i1.g;
		b[7] = i1.b;
	}
	//1,1
	if (y < ROW - 1 && x < COL - 1) {
		Pixel i1 = retP(x + 1, y + 1, gimg);
		r[8] = i1.r;
		g[8] = i1.g;
		b[8] = i1.b;
	}

	Pixel p;
	memset(&p, 0, sizeof(p));
	//median 구하기
	int cnt = 0;
	unsigned char min = 255;
	while (true) {
		if (cnt == 5) break;
		min = 255;
		int index = 0;
		for (i = 0; i < 9; i++) {
			if (r[i] <= min) {
				min = r[i];
				p.r = min;
				index = i;
			}

		}
		r[index] = 255;
		cnt += 1;
	}
	int cntg = 0;
	unsigned char ming = 255;
	while (true) {
		if (cntg == 5) break;
		min = 255;
		int index = 0;
		for (i = 0; i < 9; i++) {
			if (g[i] <= min) {
				min = g[i];
				p.g = min;
				index = i;
			}

		}
		g[index] = 255;
		cntg += 1;
	}

	int cntb = 0;
	unsigned char minb = 255;
	while (true) {
		if (cntb == 5) break;
		min = 255;
		int index = 0;
		for (i = 0; i < 9; i++) {
			if (b[i] <= min) {
				min = b[i];
				p.b = min;
				index = i;
			}

		}
		b[index] = 255;
		cntb += 1;
	}


	return p;
}

void median(unsigned char cimg[], unsigned char gimg[]) {
	for (int j = 0; j < COL; j++) {
		for (int i = 0; i < ROW; i++) {
			Pixel p = medP(i, j, gimg);
			Pins(p, i, j, cimg);
		}
	}
}

void histogram(unsigned char gimg[]) {
	int i, j;
	int histor[256]{ 0 };
	//count
	for (j = 0; j < COL; j++) {
		for (i = 0; i < ROW; i++) {
			Pixel p = retP(i, j, gimg);
			histor[p.r] += 1;
		}
	}
	//더하기
	int sum = 0;
	for (i = 0; i < 256; i++) {
		sum += i * histor[i];
	}
	//eqialization
	float epsilon = 0;
	if (sum != 0) {
		epsilon = 256 * 256 / sum;
	}

	float cnt = 0;
	int historetr[256]{ 0 };
	for (i = 0; i < 255; i++) {
		cnt += histor[i] * epsilon;
		historetr[i + 1] = (int)cnt;
	}

	for (j = 0; j < COL; j++) {
		for (i = 0; i < ROW; i++) {
			Pixel p = retP(i, j, gimg);
			histor[p.r] += 1;
		}
	}
	//green
	//count
	int histog[256]{ 0 };
	for (j = 0; j < COL; j++) {
		for (i = 0; i < ROW; i++) {
			Pixel p = retP(i, j, gimg);
			histog[p.g] += 1;
		}
	}
	//더하기

	sum = 0;
	for (i = 0; i < 256; i++) {
		sum += i * histog[i];
	}
	//eqialization
	float epsilong = 0;
	if (sum != 0) {
		float epsilong = (256 * 256) / sum;
	}
	cnt = 0;
	int historetg[256]{ 0 };
	for (i = 0; i < 256; i++) {
		cnt += histog[i] * epsilong;
		historetg[i] = (int)cnt;
	}

	//breen
	//count
	int histob[256]{ 0 };
	for (j = 0; j < COL; j++) {
		for (i = 0; i < ROW; i++) {
			Pixel p = retP(i, j, gimg);
			histob[p.b] += 1;
		}
	}
	//더하기

	sum = 0;
	for (i = 0; i < 256; i++) {
		sum += i * histob[i];
	}
	//eqialization
	float epsilonb = 0;
	if (sum != 0) {
		float epsilonb = (256 * 256) / sum;
	}
	cnt = 0;
	int historetb[256]{ 0 };
	for (i = 0; i < 256; i++) {
		cnt += histob[i] * epsilonb;
		historetb[i] = (int)cnt;
	}
	for (j = 0; j < COL; j++) {
		for (i = 0; i < ROW; i++) {
			Pixel p = retP(i, j, gimg);
			p.r = historetr[p.r];
			p.g = historetg[p.g];
			p.b = historetb[p.b];
			Pins(p, i, j, gimg);
		}
	}
}

void declear(unsigned char gimg[], int hold) {
	for (int i = 0; i < ROW * COL * 4; i++) {
		if (gimg[i] < hold) gimg[i] = 0;
	}
}

int classfier(int* datas, unsigned char gimg[]) {
	int size = datas[0];
	int cx = datas[1];
	int cy = datas[2];
	int validvalue = datas[3];
	int curvalue = 0;
	//cout << size << endl;

	//cout << cx << endl << cy << endl << validvalue;
	for (int i = cx + 3 * (size / 8); i < (cx + 5 * size / 8); i++) {
		for (int j = cy + 3 * (size / 8); j < (cy + 5 * size / 8); j++) {
			Pixel p = retP(i, j, gimg);
			if (p.r > 140) curvalue += 1;

		}
	}
	float rate = 0;
	if (curvalue != 0) {
		rate = (float)validvalue / (float)curvalue;
	}

	//cout <<"rate is"<< rate << endl;
	if (rate > 11.912) { return 3; }
	else return 2;
}

int classfier2(int* datas, unsigned char gimg[]) {
	int size = datas[0];
	int cx = datas[1];
	int cy = datas[2];
	int validvalue = datas[3];
	int curvalue = 0;
	cout << size << endl;
	cout << cx << endl << cy << endl << validvalue;
	for (int i = cx + (size / 3); i < (cx + 2 * size / 3); i++) {
		for (int j = cy + (size / 3); j < (cy + 2 * size / 3); j++) {
			Pixel p = retP(i, j, gimg);
			if (p.r > 140) {
				curvalue += 1;
			}

		}
	}
	
	float rate = 0;
	if (curvalue != 0) {
		rate = (float)validvalue / (float)curvalue;
	}

	cout << "rate is" << rate << endl;
	cout << "size is" << size << endl;
	
	if (rate < 5.1 and rate != 0) {
		return 1;
	}
	return -1;
}

int class23(int* datas, unsigned char gimg[]) {
	int size = datas[0];
	int cx = datas[1];
	int cy = datas[2];
	int validvalue = datas[3];
	int curvalue = 0;
	return 2;
}
int redgreendie(unsigned char cimg[], unsigned char gimg[]) {
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			Pixel p = retP(i, j, gimg);
			if (p.g > 200 and p.b > 200) {
				return 0;
			}
		}
	}
}

int main()
{
	unsigned char* buffer1 = new unsigned char[ROW * COL * 4];
	unsigned char* buffer2 = new unsigned char[ROW * COL * 4];
	unsigned char* buffer3 = new unsigned char[ROW * COL * 4];
	unsigned char* buffer4 = new unsigned char[ROW * COL * 4];
	unsigned char* buffer5 = new unsigned char[ROW * COL * 4];
	unsigned char* buffer6 = new unsigned char[ROW * COL * 4];
	unsigned char* buffer7 = new unsigned char[ROW * COL * 4];
	unsigned char* buffer8 = new unsigned char[ROW * COL * 4];
	unsigned char* buffer9 = new unsigned char[ROW * COL * 4];
	char readfilename[30] = "2-d.bmp";
	char writefilename[30] = "2-dout.bmp";
	char header[2048];
	FILE* fpread, * fpwrite;
	fpread = fopen(readfilename, "rb");
	fpwrite = fopen(writefilename, "wb");
	if (fpread == NULL || fpwrite == NULL) { printf("\nFile Open Error"); return 0; }
	fread(header, 1, 54, fpread); // image has been vertically inversed(upside down) by the header information
	fread(readimage, 3, ROW * COL, fpread);


	/*
	histogram(readimage);
	declear(readimage, 5);
	median(buffer1, readimage);
	median(buffer2, buffer1);
	convolution3(buffer3, buffer2, sharpen_filter);

	median(buffer3, buffer2);
	median(buffer4, buffer3);
	convolution3(buffer, buffer4, laplacian_filter);


	*/

	//1 classfying
	declear(readimage, 20);
	median(buffer, readimage);
	minmaxnormalization(buffer);
	//histogram(buffer);
	declear(buffer, 235);
	//whereareyou1(buffer);
	whereareyou1(buffer);


	median(buffer, readimage);
	minmaxnormalization(buffer);
	whereareyou8(buffer);
	//2와 3 구분
	int val = classfier2(datas, buffer);
	if (val == 1) {
		cout << 1 << endl;
	}
	val = classfier(datas, buffer);
	cout << val;

	//"어떤 점"에서 사각형 만들어서 그 안에 얼마나 들어있는가? 판단. 3에서 제일 많고, 2, 1 순일 것

	fwrite(header, 1, 54, fpwrite);
	fwrite(buffer, 3, ROW * COL, fpwrite);
	fclose(fpread);
	fclose(fpwrite);
	return 0;
}