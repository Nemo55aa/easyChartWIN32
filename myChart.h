#pragma once
#include <stdlib.h>	//malloc

const unsigned int testDnum = 20;
int testdata[testDnum];

typedef struct {
	unsigned int top;
	unsigned int left;
	unsigned int height;
	unsigned int width;
}frame;

class easyChart {
private:
	frame frm;

	int* data;
	int numdata = 20;
	
	char* unitText;
	char* bottomText;
	
	int drawChartFrame(HDC hdc);
	void refleshGraphs(HDC hdc);
public:
	easyChart();
	~easyChart();

	void setframeSize(unsigned int left, unsigned int top, unsigned int width, unsigned int height);

	int setNums(unsigned int num);
	int setData(unsigned int dstIdx, int data);

	void reDraw(HWND hWnd);
};

easyChart::easyChart() {
	data = (int*)malloc(sizeof(int) * numdata);
	setframeSize(10, 10, 100, 130);
#ifdef _DEBUG
	data[0] = 100;
	data[1] = 120;
	data[2] = 110;
	data[3] = 10;
	data[4] = 120;
	data[5] = 150;
	data[6] = 170;
	data[7] = 180;
	data[8] = 210;
#endif // DEBUG


}

easyChart::~easyChart() {
	free(data);
}

void easyChart::setframeSize(unsigned int left, unsigned int top, unsigned int width, unsigned int height) {
	frm.left = left;
	frm.top = top;
	frm.width= width;
	frm.height = height;
}

void easyChart::reDraw(HWND hWnd){
	HDC hdc = GetDC(hWnd);
	drawChartFrame(hdc);
	refleshGraphs(hdc);
	ReleaseDC(hWnd, hdc);
}

int easyChart::drawChartFrame(HDC hdc) {
	Rectangle(hdc, frm.left, frm.top, frm.top + frm.height, frm.left + frm.width);
	return 0;
}

void easyChart::refleshGraphs(HDC hdc) {
	unsigned int idx;
	MoveToEx(hdc, frm.left, frm.top, NULL);
	for (idx = 0; idx < numdata; idx++) {
		LineTo(hdc, frm.left + 15 * idx, data[idx]);
		MoveToEx(hdc, frm.left + 15 * idx, data[idx], NULL);
	}
}