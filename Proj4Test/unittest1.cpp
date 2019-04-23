#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\SEE554-Proj4\main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Proj4Test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(fillarray_test)
		{
			int *array = (int *)malloc((1024) * sizeof(int));
			fill_array(array);
			Assert::IsNotNull(&array);
		}

		TEST_METHOD(sumthread_test)
		{
			int *array = (int *)malloc((1024) * sizeof(int));
			void *id = NULL;
			void *expected_output = sum_thread(id, array);
			
			Assert::IsNull(expected_output);
		}

		TEST_METHOD(finalsum_test)
		{
			int sum = print_sum(32);
			Assert::AreEqual(32, sum) ;
		}

	};
}