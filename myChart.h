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

typedef struct {
	unsigned int x;
	unsigned int y;
}vect2d;

typedef struct {
	vect2d begin;
	vect2d end;
}line;

class easyChart {
private:
	frame frm;

	unsigned int* data;
	unsigned int numdata;

	char* unitText;
	char* bottomText;

	bool isInFrame(unsigned int data);

	int drawChartFrame(HDC hdc);
	void refleshGraphs(HDC hdc);
	/*void drawline(HDC hdc, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
	void drawline(HDC hdc, vect2d begin, vect2d end);
	void drawline(HDC hdc, line l);*/
public:
	easyChart();
	~easyChart();

	void setframeSize(unsigned int left, unsigned int top, unsigned int width, unsigned int height);

	//int setNums(unsigned int num);
	//int setData(unsigned int dstIdx, int data);
	unsigned int getnumdata();
	void appendData(unsigned int setdata);

	void getdatasStr(char* str);
	void getdatasStr(LPWSTR* str);
	LPWSTR getdatasStr();


	void reDraw(HWND hWnd);
};

easyChart::easyChart() {
#ifdef _DEBUG
	numdata = 10;

	data = (unsigned int*)malloc(sizeof(unsigned int) * numdata);
	setframeSize(10, 10, 100, 130);

	data[0] = 100;
	data[1] = 120;
	data[2] = 110;
	data[3] = 10;
	data[4] = 120;
	data[5] = 150;
	data[6] = 170;
	data[7] = 180;
	data[8] = 210;
	data[9] = 220;

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

unsigned int easyChart::getnumdata() {
	return easyChart::numdata;
}

void easyChart::appendData(unsigned int setdata) {
	// まずは元あるdataを退避
	unsigned int *tmp;
 	tmp = (unsigned int*)malloc(sizeof(unsigned int) * (numdata));
	(void)memcpy(tmp, easyChart::data, sizeof(unsigned int) * numdata);

	// 一度開放して、
	free(data);

	// 追加された分のサイズを増やして確保しなおす
	numdata++;
	easyChart::data = (unsigned int*)malloc(sizeof(unsigned int) * (numdata));
	// 退避したdataを再び入れなおす
	(void)memcpy(easyChart::data, tmp, sizeof(unsigned int) * numdata);
	free(tmp);

	// append操作本体
	easyChart::data[numdata - 1] = setdata;
}
//
//LPWSTR easyChart::getdatasStr() {
//	char tmpstr[255];
//	wsprintf((LPWSTR)tmpstr, L"data :%d, %d, %d, %d, %d, %d, %d, %d", 
//		data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]);
//	return ((LPWSTR)tmpstr);
//}


//// y軸上に入りそうなdot単位のデータがフレームから飛び出さないか判断
//bool easyChart::isInFrame(unsigned int data) {
//	return (data > frm.height) ? false : true;
//}
//
//// データ（dot単位）がフレームからはみ出そうだったらデータを何分のいちする
//bool fitinData(unsigned int data) {
//
//}
//
//void easyChart::drawline(HDC hdc, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
//	MoveToEx(hdc, x1, y1, NULL);
//	LineTo(hdc, x2, y2);
//}
//
//void easyChart::drawline(HDC hdc, vect2d begin, vect2d end) {
//	easyChart::drawline(hdc, begin.x, begin.y, end.x, end.y);
//}
//
//void easyChart::drawline(HDC hdc, line l) {
//	easyChart::drawline(hdc, l.begin, l.end);
//}