#pragma once
#include "Utility\common.hpp"
#include <memory>
#include <vector>

typedef struct _INTERNAL_DATA_ 
{
	union _My_Union
	{
		unsigned char *_raw;
		
		struct _RGBA_
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		}*rgba;

		struct _RGB_
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
		}*rgb;

		struct _CYMK_
		{
			unsigned char c;
			unsigned char y;
			unsigned char m;
			unsigned char k;
		}*cymk;

		struct _GREYSCALE_
		{
			unsigned char k;
		}*greyscale;
	}_data;

	const int _size;
	const int _height;
	const int _width;
	const int _channels;
	const uint format = 0;

}internal_data;

class Image
{
private:
	internal_data* _image_data;

public:
	Image(unsigned char *data, int width, int height, int channels, int size)
	{}

	Image(string name)
	{

	}

	int height() const { return _image_data->_height; }
	int width() const { return _image_data->_width; }
	int channels() const { return _image_data->_channels; }
};

class ImageLoader
{
private:
public:
	ImageLoader();  
	~ImageLoader();
	internal_data* load(string name) { return new internal_data(); }

}