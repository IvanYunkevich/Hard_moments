#include "pch.h"
#include "hw1.h"
#include <fstream>

TEST(PhoneBook, FileRead)
{
	ifstream file("PhoneBook.txt");
	ASSERT_NO_THROW(PhoneBook book(file));
	file.close();
}

TEST(PhoneBook, GetNumber)
{
	ifstream file("PhoneBook.txt");
	PhoneBook book(file);
	auto answer = book.GetPhoneNumber("Zaitsev");
	EXPECT_TRUE("+125(44)4164751");
	file.close();
}

TEST(PhoneBook, SortByPhone) 
{
	ifstream file("PhoneBook.txt");
	PhoneBook book(file);
	ASSERT_NO_THROW(book.SortByName());
	file.close();
}
TEST(PhoneBook, SortByName) 
{
	ifstream file("PhoneBook.txt");
	PhoneBook book(file);
	ASSERT_NO_THROW(book.SortByPhone());
	file.close();
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}