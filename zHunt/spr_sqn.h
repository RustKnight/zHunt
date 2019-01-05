#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>


using namespace std;



struct spr_sqn {
	spr_sqn() :
		x{ 32167 }, y{ 0 }, w{ 0 }, h{ 0 }
	{}

	spr_sqn(int16_t x_in, int16_t y_in, int16_t w_in, int16_t h_in) :
		x{ x_in }, y{ y_in }, w{ w_in }, h{ h_in }
	{}


	friend ostream& operator << (ostream& os, const spr_sqn& d) {

		os << "x: " << d.x << endl;
		os << "y: " << d.y << endl;
		os << "w: " << d.w << endl;
		os << "h: " << d.h << endl << endl;

		return os;
	}	

	int16_t x;
	int16_t y;
	int16_t w;
	int16_t h;
};

