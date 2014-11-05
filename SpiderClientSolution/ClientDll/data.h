#pragma once

enum DataType
{
	KEYPRESS = 0,
	MOUSELOG
};

struct KeyPress
{
	int keyCode;
};

struct MouseLog
{
	int x, y;
	int button;
};

struct Data
{
	DataType	t;
	union {
		KeyPress	key;
		MouseLog	mouse;
	}data;
};