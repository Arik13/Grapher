#include <Windows.h>
#include <cstdio>
#include "GLEW/glew.h"
#include <string>
#pragma once

int width = 900;
int height = 900;

void writeBufferToDisk() {
	const char* filename = "bufferOut.bmp";
  	byte* Buff = new byte[width * height * 3];
	if (!Buff)
		return;

	glReadBuffer(GL_BACK);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, Buff);


	FILE* Out = fopen(filename, "wb");
	if (!Out)
		return;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;

	bitmapFileHeader.bfType = 0x4D42;
	bitmapFileHeader.bfSize = width * height * 3;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits =
		sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biWidth = width - 1;
	bitmapInfoHeader.biHeight = height - 1;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = 24;
	bitmapInfoHeader.biCompression = BI_RGB;
	bitmapInfoHeader.biSizeImage = 0;
	bitmapInfoHeader.biXPelsPerMeter = 0; // ?
	bitmapInfoHeader.biYPelsPerMeter = 0; // ?
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;

	fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, Out);
	fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, Out);

}