#pragma once
#include <string>

class Map {

public:
	Map () 	
	{
		karte += L"................";
		karte += L"................";
		karte += L"................";
		karte += L"................";
		karte += L"................";  
		karte += L"................";
		karte += L"................";	
		karte += L"................";
		karte += L"................";
		karte += L"................";
	}

public:
	wchar_t get_tile(int x, int y);
	void set_tile(int x, int y, wchar_t c);

	int get_width();
	int get_height();


private:
	std::wstring karte;
	int map_width = 16;
	int map_height = 10;
};