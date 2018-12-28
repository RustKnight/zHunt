#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "RectF.h"
#include "Vec2.h"


int winWidth = 800;
int winHeight = 600;


class Demo : public olc::PixelGameEngine
{
public:
	Demo()
	{
		sAppName = "RustKnight";
	}



public:

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		return true;
	}
};


int main()
{
	Demo demo;
	if (demo.Construct(winWidth, winHeight, 1, 1))
		demo.Start();
	return 0;
}