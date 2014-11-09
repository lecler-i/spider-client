#pragma once

enum DataType
{
	NONE = 0,
	KEYPRESS,
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
	DWORD		pid;
	DataType	t;
	union {
		KeyPress	key;
		MouseLog	mouse;
	}data;
};