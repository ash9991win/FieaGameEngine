#include "pch.h"
#include "CppUnitTest.h"
#include"Datum.h"
#include<string>
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;
namespace TestLibraryDesktop
{
	TEST_CLASS(DatumTest)
	{
	public:
#if defined(DEBUG) || defined(_DEBUG)

		TEST_METHOD_INITIALIZE(HASHMAP_INIT)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}
		TEST_METHOD_CLEANUP(HASH_CLEANUP)
		{
			_CrtMemState endMemState, diffMemState;

			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}
#endif
		TEST_METHOD(DATUM_COPY)
		{
			Datum TestIntDatum1;
			Datum TestIntDatum2(Datum::DatumType::INTEGER,1);
			int TestIntArray[] = { 1,2,3,4 };
			TestIntDatum1.SetStorage(TestIntArray, 4);
			TestIntDatum2 = TestIntDatum1;
			Assert::IsTrue(TestIntDatum1 == TestIntDatum2);
			Assert::ExpectException<std::exception>([&TestIntDatum1] {TestIntDatum1.Clear(); });
			Datum TestIntDatum3;
			TestIntDatum3.PushBack(1);
			TestIntDatum3.PushBack(2);
			TestIntDatum3.PushBack(3);
			Datum TestIntDatum4 = TestIntDatum3;
			Assert::IsTrue(TestIntDatum4 == TestIntDatum3);

			Datum TestFloatDatum1;
			Datum TestFloatDatum2(Datum::DatumType::FLOAT, 1);
			float TestFloatArray[] = { 1.1f,2.2f,3.3f,4.4f };
			TestFloatDatum1.SetStorage(TestFloatArray, 4);
			TestFloatDatum2 = TestFloatDatum1;
			Assert::IsTrue(TestFloatDatum1 == TestFloatDatum2);
			Assert::ExpectException<std::exception>([&TestFloatDatum1] {TestFloatDatum1.Clear(); });
			Datum TestFloatDatum3;
			TestFloatDatum3.PushBack(1.1f);
			TestFloatDatum3.PushBack(2.2f);
			TestFloatDatum3.PushBack(3.3f);
			Datum TestFloatDatum4 = TestFloatDatum3;
			Assert::IsTrue(TestFloatDatum4 == TestFloatDatum3);


			Datum TestStringDatum1;
			Datum TestStringDatum2(Datum::DatumType::STRING, 1);
			std::string TestStringArray[] = { "Test","String" };
			TestStringDatum1.SetStorage(TestStringArray, 2);
			TestStringDatum2 = TestStringDatum1;
			Assert::IsTrue(TestStringDatum1 == TestStringDatum2);
			Assert::ExpectException<std::exception>([&TestStringDatum1] {TestStringDatum1.Clear(); });
			Datum TestStringDatum3;
			TestStringDatum3.PushBack("A");
			TestStringDatum3.PushBack("B");
			TestStringDatum3.PushBack("C");
			Datum TestStringDatum4 = TestStringDatum3;
			Assert::IsTrue(TestStringDatum4 == TestStringDatum3);
			TestStringDatum4.Clear();

			glm::vec4 TestVector1(1.0f,2.0f,3.0f,4.0f);
			Datum TestVectorDatum1;
			Datum TestVectorDatum2(Datum::DatumType::VECTOR, 1);
			TestVectorDatum1.SetStorage(&TestVector1, 1);
			TestVectorDatum2 = TestVectorDatum1;
			Assert::IsTrue(TestVectorDatum1 == TestVectorDatum2);
			Assert::ExpectException<std::exception>([&TestVectorDatum1] {TestVectorDatum1.Clear(); });
			Datum TestVectorDatum3;
			TestVectorDatum3.PushBack(TestVector1);
			Datum TestVectorDatum4 = TestVectorDatum3;
			Assert::IsTrue(TestVectorDatum4 == TestVectorDatum3);

			Datum TestMatrixDatum1;
			Datum TestMatrixDatum2(Datum::DatumType::MATRIX, 1);
			glm::mat4 TestMatrixArray;
			TestMatrixDatum1.SetStorage(&TestMatrixArray, 1);
			TestMatrixDatum2 = TestMatrixDatum1;
			Assert::IsTrue(TestMatrixDatum1 == TestMatrixDatum2);
			Assert::ExpectException<std::exception>([&TestMatrixDatum1] {TestMatrixDatum1.Clear(); });
			Datum TestMatrixDatum3;
			TestMatrixDatum3.PushBack(TestMatrixArray);
			Datum TestMatrixDatum4 = TestMatrixDatum3;

			Datum TestRTTIDatum1;
			Datum TestRTTIDatum2(Datum::DatumType::POINTER, 1);
			RTTI *TestRtti = nullptr;
			TestRTTIDatum1.SetStorage(&TestRtti, 1);
			TestRTTIDatum2 = TestRTTIDatum1;
			Assert::IsTrue(TestRTTIDatum1 == TestRTTIDatum2);
			Assert::ExpectException<std::exception>([&TestRTTIDatum1] {TestRTTIDatum1.Clear(); });
			Datum TestRTTIDatum3;
			TestRTTIDatum3.PushBack(TestRtti);
			Datum TestRTTIDatum4 = TestRTTIDatum3;
		}
		TEST_METHOD(DATUM_MOVE)
		{
			int TestInt1 = 1;
			int TestInt2 = 2;
			float TestFloat1 = 1.0f;
			float TestFloat2 = 2.0f;
			RTTI* TestRTTI1 = nullptr;
			std::string TestString1 = "Test1";
			std::string TestString2 = "Test2";
			glm::vec4 TestVector1(1.0f, 2.0f, 3.0f, 4.0f);
			glm::vec4 TestVector2(5.0f, 6.0f, 7.0f, 8.0f);
			glm::mat4 TestMatrix1(TestVector1,TestVector1,TestVector1,TestVector1);
			glm::mat4 TestMatrix2(TestVector2, TestVector2, TestVector2, TestVector2);
			Datum TestIntDatum1;
			TestIntDatum1.PushBack(TestInt1);
			TestIntDatum1.PushBack(TestInt2);
			Datum TestIntDatum2 = std::move(TestIntDatum1);
			Assert::AreEqual(TestIntDatum2.GetSize(), 2U);
			Assert::AreEqual(TestIntDatum1.GetSize(), 0U);
			Datum TestIntDatum3;
			TestIntDatum3 = std::move(TestIntDatum2);
			Assert::AreEqual(TestIntDatum3.GetSize(), 2U);
			Assert::AreEqual(TestIntDatum2.GetSize(), 0U);

			Datum TestFloatDatum1;
			TestFloatDatum1.PushBack(TestFloat1);
			TestFloatDatum1.PushBack(TestFloat2);
			Datum TestFloatDatum2 = std::move(TestFloatDatum1);
			Assert::AreEqual(TestFloatDatum2.GetSize(), 2U);
			Assert::AreEqual(TestFloatDatum1.GetSize(), 0U);
			Datum TestFloatDatum3;
			TestFloatDatum3 = std::move(TestFloatDatum2);
			Assert::AreEqual(TestFloatDatum3.GetSize(), 2U);
			Assert::AreEqual(TestFloatDatum2.GetSize(), 0U);

			Datum TestStringDatum1;
			TestStringDatum1.PushBack(TestString1);
			TestStringDatum1.PushBack(TestString2);
			Datum TestStringDatum2 = std::move(TestStringDatum1);
			Assert::AreEqual(TestStringDatum2.GetSize(), 2U);
			Assert::AreEqual(TestStringDatum1.GetSize(), 0U);
			Datum TestStringDatum3;
			TestStringDatum3 = std::move(TestStringDatum2);
			Assert::AreEqual(TestStringDatum3.GetSize(), 2U);
			Assert::AreEqual(TestStringDatum2.GetSize(), 0U);

			Datum TestVectorDatum1;
			TestVectorDatum1.PushBack(TestVector1);
			TestVectorDatum1.PushBack(TestVector2);
			Datum TestVectorDatum2 = std::move(TestVectorDatum1);
			Assert::AreEqual(TestVectorDatum2.GetSize(), 2U);
			Assert::AreEqual(TestVectorDatum1.GetSize(), 0U);
			Datum TestVectorDatum3;
			TestVectorDatum3 = std::move(TestVectorDatum2);
			Assert::AreEqual(TestVectorDatum3.GetSize(), 2U);
			Assert::AreEqual(TestVectorDatum2.GetSize(), 0U);

			Datum TestMatrixDatum1;
			TestMatrixDatum1.PushBack(TestMatrix1);
			TestMatrixDatum1.PushBack(TestMatrix2);
			Datum TestMatrixDatum2 = std::move(TestMatrixDatum1);
			Assert::AreEqual(TestMatrixDatum2.GetSize(), 2U);
			Assert::AreEqual(TestMatrixDatum1.GetSize(), 0U);
			Datum TestMatrixDatum3;
			TestMatrixDatum3 = std::move(TestMatrixDatum2);
			Assert::AreEqual(TestMatrixDatum3.GetSize(), 2U);
			Assert::AreEqual(TestMatrixDatum2.GetSize(), 0U);

			Datum TestRTTIDatum1;
			TestRTTIDatum1.PushBack(TestRTTI1);
			Datum TestRTTIDatum2 = std::move(TestRTTIDatum1);
			Assert::AreEqual(TestRTTIDatum2.GetSize(), 1U);
			Assert::AreEqual(TestRTTIDatum1.GetSize(), 0U);
			Datum TestRTTIDatum3;
			TestRTTIDatum3 = std::move(TestRTTIDatum2);
			Assert::AreEqual(TestRTTIDatum3.GetSize(), 1U);
			Assert::AreEqual(TestRTTIDatum2.GetSize(), 0U);
		}
		TEST_METHOD(DATUM_SETTYPE)
		{
			Datum TestIntDatum1;
			TestIntDatum1.SetType(Datum::DatumType::INTEGER);
			Assert::IsTrue(TestIntDatum1.Type() == Datum::DatumType::INTEGER);
			Assert::ExpectException<std::exception>([&TestIntDatum1] {TestIntDatum1.SetType(Datum::DatumType::FLOAT); });

			Datum TestFloatDatum1;
			TestFloatDatum1.SetType(Datum::DatumType::FLOAT);
			Assert::IsTrue(TestFloatDatum1.Type() == Datum::DatumType::FLOAT);
			Assert::ExpectException<std::exception>([&TestFloatDatum1] {TestFloatDatum1.SetType(Datum::DatumType::INTEGER); });

			Datum TestStringDatum1;
			TestStringDatum1.SetType(Datum::DatumType::STRING);
			Assert::IsTrue(TestStringDatum1.Type() == Datum::DatumType::STRING);
			Assert::ExpectException<std::exception>([&TestStringDatum1] {TestStringDatum1.SetType(Datum::DatumType::FLOAT); });

			Datum TestVectorDatum1;
			TestVectorDatum1.SetType(Datum::DatumType::VECTOR);
			Assert::IsTrue(TestVectorDatum1.Type() == Datum::DatumType::VECTOR);
			Assert::ExpectException<std::exception>([&TestVectorDatum1] {TestVectorDatum1.SetType(Datum::DatumType::FLOAT); });

			Datum TestMatrixDatum1;
			TestMatrixDatum1.SetType(Datum::DatumType::MATRIX);
			Assert::IsTrue(TestMatrixDatum1.Type() == Datum::DatumType::MATRIX);
			Assert::ExpectException<std::exception>([&TestMatrixDatum1] {TestMatrixDatum1.SetType(Datum::DatumType::FLOAT); });

			Datum TestRTTIDatum1;
			TestRTTIDatum1.SetType(Datum::DatumType::POINTER);
			Assert::IsTrue(TestRTTIDatum1.Type() == Datum::DatumType::POINTER);
			Assert::ExpectException<std::exception>([&TestRTTIDatum1] {TestRTTIDatum1.SetType(Datum::DatumType::FLOAT); });
		}
		TEST_METHOD(DATUM_ASSIGNMENT)
		{
			int TestInt1 = 1;
			float TestFloat1 = 1.0f;
			RTTI* TestRTTI1 = nullptr;
			std::string TestString1 = "Test1";
			std::string TestString2 = "Test2";
			glm::vec4 TestVector1(1.0f, 2.0f, 3.0f, 4.0f);
			glm::vec4 TestVector2(5.0f, 6.0f, 7.0f, 8.0f);
			glm::mat4 TestMatrix1(TestVector1, TestVector1, TestVector1, TestVector1);
			glm::mat4 TestMatrix2(TestVector2, TestVector2, TestVector2, TestVector2);

			Datum TestIntDatum;
			TestIntDatum = TestInt1;
			Assert::IsTrue(TestIntDatum.Type() == Datum::DatumType::INTEGER);
			Assert::ExpectException<std::exception>([&]{TestIntDatum.operator=(TestFloat1); });

			Datum TestFloatDatum;
			TestFloatDatum = TestFloat1;
			Assert::IsTrue(TestFloatDatum.Type() == Datum::DatumType::FLOAT);
			Assert::ExpectException<std::exception>([&] {TestFloatDatum.operator=(TestInt1); });

			Datum TestStringDatum;
			TestStringDatum = TestString1;
			Assert::IsTrue(TestStringDatum.Type() == Datum::DatumType::STRING);
			Assert::ExpectException<std::exception>([&] {TestStringDatum.operator=(TestFloat1); });

			Datum TestMatrixDatum;
			TestMatrixDatum = TestMatrix1;
			Assert::IsTrue(TestMatrixDatum.Type() == Datum::DatumType::MATRIX);
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum.operator=(TestFloat1); });

			Datum TestVectorDatum;
			TestVectorDatum = TestVector1;
			Assert::IsTrue(TestVectorDatum.Type() == Datum::DatumType::VECTOR);
			Assert::ExpectException<std::exception>([&] {TestVectorDatum.operator=(TestFloat1); });

			Datum TestRTTIDatum;
			TestRTTIDatum = TestRTTI1;
			Assert::IsTrue(TestRTTIDatum.Type() == Datum::DatumType::POINTER);
			Assert::ExpectException<std::exception>([&] {TestRTTIDatum.operator=(TestFloat1); });
		}
		TEST_METHOD(DATUM_CLEAR)
		{
			int TestInt1 = 1;
			float TestFloat1 = 1.0f;
			RTTI* TestRTTI1 = nullptr;
			std::string TestString1 = "Test1";
			std::string TestString2 = "Test2";
			glm::vec4 TestVector1(1.0f, 2.0f, 3.0f, 4.0f);
			glm::vec4 TestVector2(5.0f, 6.0f, 7.0f, 8.0f);
			glm::mat4 TestMatrix1(TestVector1, TestVector1, TestVector1, TestVector1);
			glm::mat4 TestMatrix2(TestVector2, TestVector2, TestVector2, TestVector2);

			Datum TestIntDatum1;
			TestIntDatum1.PushBack(TestInt1);
			Datum TestIntDatum2;
			TestIntDatum2.SetStorage(&TestInt1, 1);
			TestIntDatum1.Clear();
			Assert::AreEqual(TestIntDatum1.GetSize(), 0U);
			Assert::ExpectException<std::exception>([&TestIntDatum2] {TestIntDatum2.Clear(); });

			Datum TestFloatDatum1;
			TestFloatDatum1.PushBack(TestFloat1);
			Datum TestFloatDatum2;
			TestFloatDatum2.SetStorage(&TestFloat1, 1);
			TestFloatDatum1.Clear();
			Assert::AreEqual(TestFloatDatum1.GetSize(), 0U);
			Assert::ExpectException<std::exception>([&TestFloatDatum2] {TestFloatDatum2.Clear(); });

			Datum TestStringDatum1;
			TestStringDatum1.PushBack(TestString1);
			Datum TestStringDatum2;
			TestStringDatum2.SetStorage(&TestString1, 1);
			TestStringDatum1.Clear();
			Assert::AreEqual(TestStringDatum1.GetSize(), 0U);
			Assert::ExpectException<std::exception>([&TestStringDatum2] {TestStringDatum2.Clear(); });

			Datum TestVectorDatum1;
			TestVectorDatum1.PushBack(TestVector1);
			Datum TestVectorDatum2;
			TestVectorDatum2.SetStorage(&TestVector1, 1);
			TestVectorDatum1.Clear();
			Assert::AreEqual(TestVectorDatum1.GetSize(), 0U);
			Assert::ExpectException<std::exception>([&TestVectorDatum2] {TestVectorDatum2.Clear(); });

			Datum TestMatrixDatum1;
			TestMatrixDatum1.PushBack(TestMatrix1);
			Datum TestMatrixDatum2;
			TestMatrixDatum2.SetStorage(&TestMatrix1, 1);
			TestMatrixDatum1.Clear();
			Assert::AreEqual(TestMatrixDatum1.GetSize(), 0U);
			Assert::ExpectException<std::exception>([&TestMatrixDatum2] {TestMatrixDatum2.Clear(); });

			Datum TestRTTIDatum1;
			TestRTTIDatum1.PushBack(TestRTTI1);
			Datum TestRTTIDatum2;
			TestRTTIDatum2.SetStorage(&TestRTTI1, 1);
			TestRTTIDatum1.Clear();
			Assert::AreEqual(TestRTTIDatum1.GetSize(), 0U);
			Assert::ExpectException<std::exception>([&TestRTTIDatum2] {TestRTTIDatum2.Clear(); });
		}
		TEST_METHOD(DATUM_COMPARE)
		{
			int TestInt1 = 1;
			int TestInt2 = 2;
			float TestFloat1 = 1.0f;
			float TestFloat2 = 2.0f;
			RTTI* TestRTTI1 = nullptr;
			std::string TestString1 = "Test1";
			std::string TestString2 = "Test2";
			glm::vec4 TestVector1(1.0f, 2.0f, 3.0f, 4.0f);
			glm::vec4 TestVector2(5.0f, 6.0f, 7.0f, 8.0f);
			glm::mat4 TestMatrix1(TestVector1, TestVector1, TestVector1, TestVector1);
			glm::mat4 TestMatrix2(TestVector2, TestVector2, TestVector2, TestVector2);

			Datum TestIntDatum1;
			TestIntDatum1.PushBack(TestInt1);
			Datum TestIntDatum2 = TestIntDatum1;
			Assert::IsTrue(TestIntDatum1 == TestIntDatum2);
			Datum TestIntDatum3;
			TestIntDatum3.PushBack(TestInt2);
			Assert::IsTrue(TestIntDatum1 != TestIntDatum3);

			Datum TestFloatDatum1;
			TestFloatDatum1.PushBack(TestFloat1);
			Datum TestFloatDatum2 = TestFloatDatum1;
			Assert::IsTrue(TestFloatDatum1 == TestFloatDatum2);
			Datum TestFloatDatum3;
			TestFloatDatum3.PushBack(TestFloat2);
			Assert::IsTrue(TestFloatDatum1 != TestFloatDatum3);

			Datum TestStringDatum1;
			TestStringDatum1.PushBack(TestString1);
			Datum TestStringDatum2 = TestStringDatum1;
			Assert::IsTrue(TestStringDatum1 == TestStringDatum2);
			Datum TestStringDatum3;
			TestStringDatum3.PushBack(TestString2);
			Assert::IsTrue(TestStringDatum1 != TestStringDatum3);

			Datum TestMatrixDatum1;
			TestMatrixDatum1.PushBack(TestMatrix1);
			Datum TestMatrixDatum2 = TestMatrixDatum1;
			Assert::IsTrue(TestMatrixDatum1 == TestMatrixDatum2);
			Datum TestMatrixDatum3;
			TestMatrixDatum3.PushBack(TestMatrix2);
			Assert::IsTrue(TestMatrixDatum1 != TestMatrixDatum3);

			Datum TestVectorDatum1;
			TestVectorDatum1.PushBack(TestVector1);
			Datum TestVectorDatum2 = TestVectorDatum1;
			Assert::IsTrue(TestVectorDatum1 == TestVectorDatum2);
			Datum TestVectorDatum3;
			TestVectorDatum3.PushBack(TestVector2);
			Assert::IsTrue(TestVectorDatum1 != TestVectorDatum3);

			Datum TestRTTIDatum1;
			TestRTTIDatum1.PushBack(TestRTTI1);
			Datum TestRTTIDatum2 = TestRTTIDatum1;
			Assert::IsTrue(TestRTTIDatum1 == TestRTTIDatum2);
			Datum TestRTTIDatum3;
			TestRTTIDatum3.PushBack(TestRTTI1);
			Assert::IsTrue(!(TestRTTIDatum1 != TestRTTIDatum3));

		}
		TEST_METHOD(DATUM_SET)
		{
			int TestInt1 = 1;
			int TestInt2 = 2;
			float TestFloat1 = 1.0f;
			float TestFloat2 = 2.0f;
			RTTI* TestRTTI1 = nullptr;
			std::string TestString1 = "Test1";
			std::string TestString2 = "Test2";
			glm::vec4 TestVector1(1.0f, 2.0f, 3.0f, 4.0f);
			glm::vec4 TestVector2(5.0f, 6.0f, 7.0f, 8.0f);
			glm::mat4 TestMatrix1(TestVector1, TestVector1, TestVector1, TestVector1);
			glm::mat4 TestMatrix2(TestVector2, TestVector2, TestVector2, TestVector2);

			Datum TestIntDatum;
			TestIntDatum.Set(TestInt1);
			Assert::IsTrue(TestIntDatum.GetSize() == 1U);
			TestIntDatum.Set(TestInt2, 1U);
			Assert::IsTrue(TestIntDatum.GetSize() == 2U);
			Assert::ExpectException<std::exception>([&] {TestIntDatum.Set(TestInt1, 5); });
			Assert::ExpectException<std::exception>([&] {TestIntDatum.Set(TestFloat1); });

			Datum TestFloatDatum;
			TestFloatDatum.Set(TestFloat1);
			Assert::IsTrue(TestFloatDatum.GetSize() == 1U);
			TestFloatDatum.Set(TestFloat2, 1U);
			Assert::IsTrue(TestFloatDatum.GetSize() == 2U);
			Assert::ExpectException<std::exception>([&] {TestFloatDatum.Set(TestFloat1, 5); });
			Assert::ExpectException<std::exception>([&] {TestFloatDatum.Set(TestInt1); });

			Datum TestStringDatum;
			TestStringDatum.Set(TestString1);
			Assert::IsTrue(TestStringDatum.GetSize() == 1U);
			TestStringDatum.Set(TestString2, 1U);
			Assert::IsTrue(TestStringDatum.GetSize() == 2U);
			Assert::ExpectException<std::exception>([&] {TestStringDatum.Set(TestString1, 5); });
			Assert::ExpectException<std::exception>([&] {TestStringDatum.Set(TestFloat1); });

			Datum TestMatrixDatum;
			TestMatrixDatum.Set(TestMatrix1);
			Assert::IsTrue(TestMatrixDatum.GetSize() == 1U);
			TestMatrixDatum.Set(TestMatrix2, 1U);
			Assert::IsTrue(TestMatrixDatum.GetSize() == 2U);
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum.Set(TestMatrix1, 5); });
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum.Set(TestFloat1); });

			Datum TestVectorDatum;
			TestVectorDatum.Set(TestVector1);
			Assert::IsTrue(TestVectorDatum.GetSize() == 1U);
			TestVectorDatum.Set(TestVector2, 1U);
			Assert::IsTrue(TestVectorDatum.GetSize() == 2U);
			Assert::ExpectException<std::exception>([&] {TestVectorDatum.Set(TestVector1, 5); });
			Assert::ExpectException<std::exception>([&] {TestVectorDatum.Set(TestFloat1); });

			Datum TestRTTIDatum;
			TestRTTIDatum.Set(TestRTTI1);
			Assert::IsTrue(TestRTTIDatum.GetSize() == 1U);
			TestRTTIDatum.Set(TestRTTI1, 1U);
			Assert::IsTrue(TestRTTIDatum.GetSize() == 2U);
			Assert::ExpectException<std::exception>([&] {TestRTTIDatum.Set(TestRTTI1, 5); });
			Assert::ExpectException<std::exception>([&] {TestRTTIDatum.Set(TestFloat1); });

		}
		TEST_METHOD(DATUM_SETFROMSTRING)
		{
			std::string TestInt1 = "1";
			std::string TestFloat1 = "1.4f";
			std::string TestMatrix1 = "1.0f 2.0f 3.0f 4.0f 5.0f 6.0f 7.0f 8.0f 9.0f 10.0f 11.0f 12.0f 13.0f 14.0f 15.0f 16.0f";
			std::string TestString1 = "Test1";
			std::string TestVector1= "1.0f 2.0f 3.0f 4.0f";

			Datum TestIntDatum;
			Assert::ExpectException<std::exception>([&] {TestIntDatum.SetFromString(TestInt1); });
			TestIntDatum.SetType(Datum::DatumType::INTEGER);
			TestIntDatum.SetFromString(TestInt1);
			Assert::IsTrue(TestIntDatum.GetSize() == 1U);
			Assert::ExpectException<std::exception>([&] {TestIntDatum.SetFromString(TestFloat1,Datum::DatumType::FLOAT); });

			Datum TestFloatDatum;
			Assert::ExpectException<std::exception>([&] {TestFloatDatum.SetFromString(TestFloat1); });
			TestFloatDatum.SetType(Datum::DatumType::FLOAT);
			TestFloatDatum.SetFromString(TestFloat1);
			Assert::IsTrue(TestFloatDatum.GetSize() == 1U);
			Assert::ExpectException<std::exception>([&] {TestFloatDatum.SetFromString(TestFloat1, Datum::DatumType::INTEGER); });

			Datum TestStringDatum;
			Assert::ExpectException<std::exception>([&] {TestStringDatum.SetFromString(TestString1); });
			TestStringDatum.SetType(Datum::DatumType::STRING);
			TestStringDatum.SetFromString(TestString1);
			Assert::IsTrue(TestStringDatum.GetSize() == 1U);
			Assert::ExpectException<std::exception>([&] {TestStringDatum.SetFromString(TestFloat1, Datum::DatumType::FLOAT); });

			Datum TestVectorDatum;
			Assert::ExpectException<std::exception>([&] {TestVectorDatum.SetFromString(TestVector1); });
			TestVectorDatum.SetType(Datum::DatumType::VECTOR);
			TestVectorDatum.SetFromString(TestVector1);
			Assert::IsTrue(TestVectorDatum.GetSize() == 1U);
			Assert::ExpectException<std::exception>([&] {TestVectorDatum.SetFromString(TestFloat1, Datum::DatumType::FLOAT); });

			Datum TestMatrixDatum;
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum.SetFromString(TestMatrix1); });
			TestMatrixDatum.SetType(Datum::DatumType::MATRIX);
			TestMatrixDatum.SetFromString(TestMatrix1);
			Assert::IsTrue(TestMatrixDatum.GetSize() == 1U);
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum.SetFromString(TestFloat1, Datum::DatumType::FLOAT); });
		}
		TEST_METHOD(DATUM_TOSTRING)
		{
			int TestInt1 = 1;
			float TestFloat1 = 1.0f;
			std::string TestString1 = "Test1";
			glm::vec4 TestVector1(1.0f, 2.0f, 3.0f, 4.0f);
			glm::vec4 TestVector2(5.0f, 6.0f, 7.0f, 8.0f);
			glm::mat4 TestMatrix1(TestVector1, TestVector1, TestVector1, TestVector1);
			glm::mat4 TestMatrix2(TestVector2, TestVector2, TestVector2, TestVector2);

			Datum TestInt;
			Assert::ExpectException<std::exception>([&] {TestInt.ToString(); });
			TestInt.PushBack(TestInt1);
			std::string TestIntString = TestInt.ToString();
			Assert::IsTrue(TestIntString == "1");

			Datum TestFloat;
			Assert::ExpectException<std::exception>([&] {TestFloat.ToString(); });
			TestFloat.PushBack(TestFloat1);
			std::string TestFloatString = TestFloat.ToString();


			Datum TestString;
			Assert::ExpectException<std::exception>([&] {TestString.ToString(); });
			TestString.PushBack(TestString1);
			std::string TestStringString = TestString.ToString();


			Datum TestVector;
			Assert::ExpectException<std::exception>([&] {TestVector.ToString(); });
			TestVector.PushBack(TestVector1);
			std::string TestVectorString = TestVector.ToString();


			Datum TestMatrix;
			Assert::ExpectException<std::exception>([&] {TestMatrix.ToString(); });
			TestMatrix.PushBack(TestMatrix1);
			std::string TestMatrixString = TestMatrix.ToString();
		}
		TEST_METHOD(DATUM_RESERVE)
		{
			int TestInt1 = 1;
			float TestFloat1 = 1.0f;
			std::string TestString1 = "Test1";
			glm::vec4 TestVector1(1.0f, 2.0f, 3.0f, 4.0f);
			glm::vec4 TestVector2(5.0f, 6.0f, 7.0f, 8.0f);
			glm::mat4 TestMatrix1(TestVector1, TestVector1, TestVector1, TestVector1);
			glm::mat4 TestMatrix2(TestVector2, TestVector2, TestVector2, TestVector2);
			RTTI* TestRTTI1 = nullptr;
			Datum TestIntDatum1;
			Assert::ExpectException<std::exception>([&] {TestIntDatum1.Reserve(4); });
			TestIntDatum1.SetType(Datum::DatumType::INTEGER);
			TestIntDatum1.Reserve(5U, true);
			Assert::IsTrue(TestIntDatum1.GetSize() == 5U);
			TestIntDatum1.SetStorage(&TestInt1, 1);
			Assert::ExpectException<std::exception>([&] {TestIntDatum1.Reserve(4); });

			Datum TestFloatDatum1;
			Assert::ExpectException<std::exception>([&] {TestFloatDatum1.Reserve(4); });
			TestFloatDatum1.SetType(Datum::DatumType::FLOAT);
			TestFloatDatum1.Reserve(5U, true);
			Assert::IsTrue(TestFloatDatum1.GetSize() == 5U);
			TestFloatDatum1.SetStorage(&TestFloat1, 1);
			Assert::ExpectException<std::exception>([&] {TestFloatDatum1.Reserve(4); });

			Datum TestStringDatum1;
			Assert::ExpectException<std::exception>([&] {TestStringDatum1.Reserve(4); });
			TestStringDatum1.SetType(Datum::DatumType::STRING);
			TestStringDatum1.Reserve(5U, true);
			Assert::IsTrue(TestStringDatum1.GetSize() == 5U);
			TestStringDatum1.SetStorage(&TestString1, 1);
			Assert::ExpectException<std::exception>([&] {TestStringDatum1.Reserve(4); });

			Datum TestVectorDatum1;
			Assert::ExpectException<std::exception>([&] {TestVectorDatum1.Reserve(4); });
			TestVectorDatum1.SetType(Datum::DatumType::VECTOR);
			TestVectorDatum1.Reserve(5U, true);
			Assert::IsTrue(TestVectorDatum1.GetSize() == 5U);
			TestVectorDatum1.SetStorage(&TestVector1, 1);
			Assert::ExpectException<std::exception>([&] {TestVectorDatum1.Reserve(4); });

			Datum TestMatrixDatum1;
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum1.Reserve(4); });
			TestMatrixDatum1.SetType(Datum::DatumType::MATRIX);
			TestMatrixDatum1.Reserve(5U, true);
			Assert::IsTrue(TestMatrixDatum1.GetSize() == 5U);
			TestMatrixDatum1.SetStorage(&TestMatrix1, 1);
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum1.Reserve(4); });

			Datum TestRTTIDatum1;
			Assert::ExpectException<std::exception>([&] {TestRTTIDatum1.Reserve(4); });
			TestRTTIDatum1.SetType(Datum::DatumType::POINTER);
			TestRTTIDatum1.Reserve(5U, true);
			Assert::IsTrue(TestRTTIDatum1.GetSize() == 5U);
			TestRTTIDatum1.SetStorage(&TestRTTI1, 1);
			Assert::ExpectException<std::exception>([&] {TestRTTIDatum1.Reserve(4); });

		}
		TEST_METHOD(DATUM_REMOVE)
		{
			int TestInt1 = 1;
			int TestInt2 = 2;
			float TestFloat1 = 1.0f;
			float TestFloat2 = 2.0f;
			std::string TestString1 = "Test1";
			std::string TestString2 = "Test2";
			glm::vec4 TestVector1(1.0f, 2.0f, 3.0f, 4.0f);
			glm::vec4 TestVector2(5.0f, 6.0f, 7.0f, 8.0f);
			glm::mat4 TestMatrix1(TestVector1, TestVector1, TestVector1, TestVector1);
			glm::mat4 TestMatrix2(TestVector2, TestVector2, TestVector2, TestVector2);
			RTTI* TestRTTI1 = nullptr;
			RTTI* TestRTTI2 = nullptr;

			Datum TestIntDatum;
			TestIntDatum.Remove(4);
			Assert::IsTrue(TestIntDatum.GetSize() == 0U);
			TestIntDatum.PushBack(TestInt1);
			TestIntDatum.PushBack(TestInt2);
			TestIntDatum.Remove(0);
			Assert::IsTrue(TestIntDatum.Get<int>() == TestInt2);
			Assert::IsTrue(TestIntDatum.GetSize() == 1U);
			TestIntDatum.SetStorage(&TestInt1, 1);
			Assert::ExpectException<std::exception>([&] {TestIntDatum.Remove(2); });

			Datum TestFloatDatum;
			TestFloatDatum.Remove(4);
			Assert::IsTrue(TestFloatDatum.GetSize() == 0U);
			TestFloatDatum.PushBack(TestFloat1);
			TestFloatDatum.PushBack(TestFloat2);
			TestFloatDatum.Remove(0);
			Assert::IsTrue(TestFloatDatum.Get<float>() == TestFloat2);
			Assert::IsTrue(TestFloatDatum.GetSize() == 1U);
			TestFloatDatum.SetStorage(&TestFloat1, 1);
			Assert::ExpectException<std::exception>([&] {TestFloatDatum.Remove(2); });

			Datum TestStringDatum;
			TestStringDatum.Remove(4);
			Assert::IsTrue(TestStringDatum.GetSize() == 0U);
			TestStringDatum.PushBack(TestString1);
			TestStringDatum.PushBack(TestString2);
			TestStringDatum.Remove(0);
			Assert::IsTrue(TestStringDatum.Get<std::string>() == TestString2);
			Assert::IsTrue(TestStringDatum.GetSize() == 1U);
			TestStringDatum.SetStorage(&TestString1, 1);
			Assert::ExpectException<std::exception>([&] {TestStringDatum.Remove(2); });

			Datum TestVectorDatum;
			TestVectorDatum.Remove(4);
			Assert::IsTrue(TestVectorDatum.GetSize() == 0U);
			TestVectorDatum.PushBack(TestVector1);
			TestVectorDatum.PushBack(TestVector2);
			TestVectorDatum.Remove(0);
			Assert::IsTrue(TestVectorDatum.Get<glm::vec4>() == TestVector2);
			Assert::IsTrue(TestVectorDatum.GetSize() == 1U);
			TestVectorDatum.SetStorage(&TestVector1, 1);
			Assert::ExpectException<std::exception>([&] {TestVectorDatum.Remove(2); });

		/*	Datum TestMatrixDatum;
			TestMatrixDatum.Remove(4);
			Assert::IsTrue(TestMatrixDatum.GetSize() == 0U);
			TestMatrixDatum.PushBack(TestMatrix1);
			TestMatrixDatum.PushBack(TestMatrix2);
			TestMatrixDatum.Remove(0);
			Assert::IsTrue(TestMatrixDatum.Get<glm::mat4>() == TestMatrix2);
			Assert::IsTrue(TestMatrixDatum.GetSize() == 1U);
			TestMatrixDatum.SetStorage(&TestMatrix1, 1);
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum.Remove(2); });
*/
			TestRTTI1;
			TestRTTI2;
			//Datum TestRTTIDatum;
			//TestRTTIDatum.Remove(4);
			//Assert::IsTrue(TestRTTIDatum.GetSize() == 0U);
			//TestRTTIDatum.PushBack(TestRTTI1);
			//TestRTTIDatum.PushBack(TestRTTI2);
			//TestRTTIDatum.Remove(0);
			//Assert::IsTrue(TestRTTIDatum.Get<RTTI*>() == TestRTTI2);
			//Assert::IsTrue(TestRTTIDatum.GetSize() == 1U);
			//TestRTTIDatum.SetStorage(&TestRTTI1, 1);
			//Assert::ExpectException<std::exception>([&] {TestRTTIDatum.Remove(2); });
		}
		TEST_METHOD(DATUM_POPBACK)
		{
			int TestInt1 = 1;
			int TestInt2 = 2;
			float TestFloat1 = 1.0f;
			float TestFloat2 = 2.0f;
			std::string TestString1 = "Test1";
			std::string TestString2 = "Test2";
			glm::vec4 TestVector1(1.0f, 2.0f, 3.0f, 4.0f);
			glm::vec4 TestVector2(5.0f, 6.0f, 7.0f, 8.0f);
			glm::mat4 TestMatrix1(TestVector1, TestVector1, TestVector1, TestVector1);
			glm::mat4 TestMatrix2(TestVector2, TestVector2, TestVector2, TestVector2);
			RTTI* TestRTTI1 = nullptr;
			RTTI* TestRTTI2 = nullptr;

			Datum TestIntDatum;
			TestIntDatum.PopBack();
			Assert::IsTrue(TestIntDatum.GetSize() == 0U);
			TestIntDatum.PushBack(TestInt1);
			TestIntDatum.PushBack(TestInt2);
			TestIntDatum.PopBack();
			Assert::IsTrue(TestIntDatum.GetSize() == 1U);
			TestIntDatum.SetStorage(&TestInt1, 1);
			Assert::ExpectException<std::exception>([&] {TestIntDatum.PopBack(); });

			Datum TestFloatDatum;
			TestFloatDatum.PopBack();
			Assert::IsTrue(TestFloatDatum.GetSize() == 0U);
			TestFloatDatum.PushBack(TestFloat1);
			TestFloatDatum.PushBack(TestFloat2);
			TestFloatDatum.PopBack();
			Assert::IsTrue(TestFloatDatum.GetSize() == 1U);
			TestFloatDatum.SetStorage(&TestFloat1, 1);
			Assert::ExpectException<std::exception>([&] {TestFloatDatum.PopBack(); });

			Datum TestStringDatum;
			TestStringDatum.PopBack();
			Assert::IsTrue(TestStringDatum.GetSize() == 0U);
			TestStringDatum.PushBack(TestString1);
			TestStringDatum.PushBack(TestString2);
			TestStringDatum.PopBack();
			Assert::IsTrue(TestStringDatum.GetSize() == 1U);
			TestStringDatum.SetStorage(&TestString1, 1);
			Assert::ExpectException<std::exception>([&] {TestStringDatum.PopBack(); });

			Datum TestVectorDatum;
			TestVectorDatum.PopBack();
			Assert::IsTrue(TestVectorDatum.GetSize() == 0U);
			TestVectorDatum.PushBack(TestVector1);
			TestVectorDatum.PushBack(TestVector2);
			TestVectorDatum.PopBack();
			Assert::IsTrue(TestVectorDatum.GetSize() == 1U);
			TestVectorDatum.SetStorage(&TestVector1, 1);
			Assert::ExpectException<std::exception>([&] {TestVectorDatum.PopBack(); });

			Datum TestMatrixDatum;
			TestMatrixDatum.PopBack();
			Assert::IsTrue(TestMatrixDatum.GetSize() == 0U);
			TestMatrixDatum.PushBack(TestMatrix1);
			TestMatrixDatum.PushBack(TestMatrix2);
			TestMatrixDatum.PopBack();
			Assert::IsTrue(TestMatrixDatum.GetSize() == 1U);
			TestMatrixDatum.SetStorage(&TestMatrix1, 1);
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum.PopBack(); });

			Datum TestRTTIDatum;
			TestRTTIDatum.PopBack();
			Assert::IsTrue(TestRTTIDatum.GetSize() == 0U);
			TestRTTIDatum.PushBack(TestRTTI1);
			TestRTTIDatum.PushBack(TestRTTI2);
			TestRTTIDatum.PopBack();
			Assert::IsTrue(TestRTTIDatum.GetSize() == 1U);
			TestRTTIDatum.SetStorage(&TestRTTI1, 1);
			Assert::ExpectException<std::exception>([&] {TestRTTIDatum.PopBack(); });

		}
		TEST_METHOD(DATUM_PUSHBACK)
		{
			int TestInt1 = 1;
			float TestFloat1 = 1.0f;
			std::string TestString1 = "Test1";
			std::string TestString2 = "Test2";
			glm::vec4 TestVector1(1.0f, 2.0f, 3.0f, 4.0f);
			glm::vec4 TestVector2(5.0f, 6.0f, 7.0f, 8.0f);
			glm::mat4 TestMatrix1(TestVector1, TestVector1, TestVector1, TestVector1);
			glm::mat4 TestMatrix2(TestVector2, TestVector2, TestVector2, TestVector2);
			RTTI* TestRTTI1 = nullptr;

			Datum TestIntDatum;
			TestIntDatum.PushBack(TestInt1);
			Assert::IsTrue(TestIntDatum.Type() == Datum::DatumType::INTEGER);
			Assert::IsTrue(TestIntDatum.GetSize() == 1U);
			Assert::ExpectException<std::exception>([&] {TestIntDatum.PushBack(TestFloat1); });

			Datum TestFloatDatum;
			TestFloatDatum.PushBack(TestFloat1);
			Assert::IsTrue(TestFloatDatum.Type() == Datum::DatumType::FLOAT);
			Assert::IsTrue(TestFloatDatum.GetSize() == 1U);
			Assert::ExpectException<std::exception>([&] {TestFloatDatum.PushBack(TestInt1); });

			Datum TestStringDatum;
			TestStringDatum.PushBack(TestString1);
			Assert::IsTrue(TestStringDatum.Type() == Datum::DatumType::STRING);
			Assert::IsTrue(TestStringDatum.GetSize() == 1U);
			Assert::ExpectException<std::exception>([&] {TestStringDatum.PushBack(TestFloat1); });

			Datum TestVectorDatum;
			TestVectorDatum.PushBack(TestVector1);
			Assert::IsTrue(TestVectorDatum.Type() == Datum::DatumType::VECTOR);
			Assert::IsTrue(TestVectorDatum.GetSize() == 1U);
			Assert::ExpectException<std::exception>([&] {TestVectorDatum.PushBack(TestFloat1); });

			Datum TestMatrixDatum;
			TestMatrixDatum.PushBack(TestMatrix1);
			Assert::IsTrue(TestMatrixDatum.Type() == Datum::DatumType::MATRIX);
			Assert::IsTrue(TestMatrixDatum.GetSize() == 1U);
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum.PushBack(TestFloat1); });

			Datum TestRTTIDatum;
			TestRTTIDatum.PushBack(TestRTTI1);
			Assert::IsTrue(TestRTTIDatum.Type() == Datum::DatumType::POINTER);
			Assert::IsTrue(TestRTTIDatum.GetSize() == 1U);
			Assert::ExpectException<std::exception>([&] {TestRTTIDatum.PushBack(TestFloat1); });

		}
		TEST_METHOD(DATUM_GET)
		{
			int TestInt1 = 1;
			float TestFloat1 = 1.0f;
			std::string TestString1 = "Test1";
			std::string TestString2 = "Test2";
			glm::vec4 TestVector1(1.0f, 2.0f, 3.0f, 4.0f);
			glm::vec4 TestVector2(5.0f, 6.0f, 7.0f, 8.0f);
			glm::mat4 TestMatrix1(TestVector1, TestVector1, TestVector1, TestVector1);
			glm::mat4 TestMatrix2(TestVector2, TestVector2, TestVector2, TestVector2);
			RTTI* TestRTTI1 = nullptr;

			Datum TestIntDatum1;
			Assert::ExpectException<std::exception>([&] {TestIntDatum1.Get<int>(); });
			TestIntDatum1.PushBack(TestInt1);
			Assert::IsTrue(TestIntDatum1.Get<int>() == TestInt1);
			const Datum TestIntDatum2 = TestIntDatum1;
			Assert::ExpectException<std::exception>([&] {TestIntDatum2.Get<int>(5); });
			Assert::IsTrue(TestIntDatum2.Get<int>() == TestInt1);

			Datum TestFloatDatum1;
			Assert::ExpectException<std::exception>([&] {TestFloatDatum1.Get<float>(); });
			TestFloatDatum1.PushBack(TestFloat1);
			Assert::IsTrue(TestFloatDatum1.Get<float>() == TestFloat1);
			const Datum TestFloatDatum2 = TestFloatDatum1;
			Assert::ExpectException<std::exception>([&] {TestFloatDatum2.Get<float>(5); });
			Assert::IsTrue(TestFloatDatum2.Get<float>() == TestFloat1);

			Datum TestStringDatum1;
			Assert::ExpectException<std::exception>([&] {TestStringDatum1.Get<float>(); });
			TestStringDatum1.PushBack(TestString1);
			Assert::IsTrue(TestStringDatum1.Get<std::string>() == TestString1);
			const Datum TestStringDatum2 = TestStringDatum1;
			Assert::ExpectException<std::exception>([&] {TestStringDatum2.Get<float>(5); });
			Assert::IsTrue(TestStringDatum2.Get<std::string>() == TestString1);

			Datum TestVectorDatum1;
			Assert::ExpectException<std::exception>([&] {TestVectorDatum1.Get<glm::vec4>(); });
			TestVectorDatum1.PushBack(TestVector1);
			Assert::IsTrue(TestVectorDatum1.Get<glm::vec4>() == TestVector1);
			const Datum TestVectorDatum2 = TestVectorDatum1;
			Assert::ExpectException<std::exception>([&] {TestVectorDatum2.Get<glm::vec4>(5); });
			Assert::IsTrue(TestVectorDatum2.Get<glm::vec4>() == TestVector1);

			Datum TestMatrixDatum1;
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum1.Get<glm::mat4>(); });
			TestMatrixDatum1.PushBack(TestMatrix1);
			Assert::IsTrue(TestMatrixDatum1.Get<glm::mat4>() == TestMatrix1);
			const Datum TestMatrixDatum2 = TestMatrixDatum1;
			Assert::ExpectException<std::exception>([&] {TestMatrixDatum2.Get<glm::mat4>(5); });
			Assert::IsTrue(TestMatrixDatum2.Get<glm::mat4>() == TestMatrix1);

			Datum TestRTTIDatum1;
			Assert::ExpectException<std::exception>([&] {TestRTTIDatum1.Get<RTTI*>(); });
			TestRTTIDatum1.PushBack(TestRTTI1);
			Assert::IsTrue(TestRTTIDatum1.Get<RTTI*>() == TestRTTI1);
			const Datum TestRTTIDatum2 = TestRTTIDatum1;
			Assert::ExpectException<std::exception>([&] {TestRTTIDatum2.Get<RTTI*>(5); });
			Assert::IsTrue(TestRTTIDatum2.Get<RTTI*>() == TestRTTI1);
		}
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif
	};
#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState DatumTest::sStartMemState;
#endif
}