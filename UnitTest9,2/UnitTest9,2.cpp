#include "pch.h"
#include "CppUnitTest.h"
#include "../lab 9.2/lab 9.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest92
{
	TEST_CLASS(UnitTest92)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int N = 1;
			Students* s = new Students[N];
			s[0].surname = "Іваненко";
			s[0].course = 1;
			s[0].speciality = ITIS;
			s[0].grade_physics = 5;
			s[0].grade_programming = 5;
			s[0].grade_math = 5;

			double BestAvg = BestAverage(s, N);
			Assert::AreEqual(BestAvg, 5.0);
		}
	};
}
