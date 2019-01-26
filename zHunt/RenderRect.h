#pragma once



struct RenderRect {

	void get_dim(int xx, int yy, int wwidth, int hheight) {

		x = xx;
		y = yy;
		width = wwidth;
		height = hheight;

		top = y;
		bottom = y + height;
		left = x;
		right = x + width;
	}

	int top = 0;
	int bottom = 0;
	int left = 0;
	int right = 0;

private:
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
};