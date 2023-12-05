#include "../Medved/Medved.cpp"
#include "pch.h"
#include "CppUnitTest.h"
#include "../Medved/Medved.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MedvedUnitTest
{
	TEST_CLASS(MedvedUnitTest)
	{
	public:

		TEST_METHOD(TestMovement)
		{
			int dir = REST;
			int x = 10;
			int y = 5;

			// Test REST movement
			Movement(dir, x, y);
			Assert::AreEqual(10, x);
			Assert::AreEqual(5, y);

			// Test UP movement
			dir = UP;
			Movement(dir, x, y);
			Assert::AreEqual(10, x);
			Assert::AreEqual(4, y);

			// Test DOWN movement
			dir = DOWN;
			Movement(dir, x, y);
			Assert::AreEqual(10, x);
			Assert::AreEqual(5, y);

			// Test LEFT movement
			dir = LEFT;
			Movement(dir, x, y);
			Assert::AreEqual(9, x);
			Assert::AreEqual(5, y);

			// Test RIGHT movement
			dir = RIGHT;
			Movement(dir, x, y);
			Assert::AreEqual(10, x);
			Assert::AreEqual(5, y);

			// Test border cases
			x = 0;
			y = 0;

			dir = LEFT;
			Movement(dir, x, y);
			Assert::AreEqual(0, x);
			Assert::AreEqual(0, y);

			dir = UP;
			Movement(dir, x, y);
			Assert::AreEqual(0, x);
			Assert::AreEqual(0, y);

			x = WIDTH - 2;
			y = HEIGHT - 1;

			dir = RIGHT;
			Movement(dir, x, y);
			Assert::AreEqual(WIDTH - 2, x);
			Assert::AreEqual(HEIGHT - 1, y);

			dir = DOWN;
			Movement(dir, x, y);
			Assert::AreEqual(WIDTH - 2, x);
			Assert::AreEqual(HEIGHT - 1, y);
		}

		TEST_METHOD(TestChaserMovement)
		{
			int x = 5;
			int y = 5;
			int gx = 8;
			int gy = 10;

			ChaserMovement('o', x, y, gx, gy);
			Assert::AreEqual(6, x);
			Assert::AreEqual(6, y);

			gx = 2;
			gy = 3;

			ChaserMovement('*', x, y, gx, gy);
			Assert::AreEqual(5, x);
			Assert::AreEqual(5, y);
		}

		TEST_METHOD(TestRender)
		{
			// Test render output
			char renderOutput[] =
				"====================\n"
				"| O				|\n"
				"|					|\n"
				"| o				|\n"
				"|					|\n"
				"|					|\n"
				"|					|\n"
				"|					|\n"
				"|					|\n"
				"====================\n";

			std::stringstream stream;
			std::streambuf* oldCout = std::cout.rdbuf(stream.rdbuf());

			int bx = 12;
			int by = 1;
			char bs = 'O';
			int tx = 8;
			int ty = 3;
			char ts = 'o';
			int hx[HUNTERS_COUNT] = { 3, 6, 10, 14 };
			int hy[HUNTERS_COUNT] = { 2, 4, 6, 8 };
			char hs = '*';

			Render(bx, by, bs, tx, ty, ts, hx, hy, hs);

			std::cout.rdbuf(oldCout);
			std::string consoleOutput = stream.str();
			std::string _renderOutput = renderOutput;

			Assert::AreEqual(_renderOutput, consoleOutput);
		}
	};
}
