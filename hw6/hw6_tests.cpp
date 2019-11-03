/**	This function tests the functions made in linked list collection
*	Carter Mooring
*	CSPC 223 Dr. Bowers
*	hw6
*	hw6_tests.cpp
*	10/30/19
*/

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "linked_list_collection.h"

using namespace std;

// Test 1
TEST(BasicCollectionTest, CorrectSize){
  LinkedListCollection <string, double> c;
  ASSERT_EQ(c.size(), 0);
  c.insert("a", 10.0);
  ASSERT_EQ(c.size(), 1);
  c.insert("b", 20.0);
  ASSERT_EQ(c.size(), 2);
  ASSERT_NE(c.size(), -1);	//Make sure the size doesnt go above..
  ASSERT_NE(c.size(), 3);	//or below the bounds necessary
}

// Test 2
TEST(BasicCollectionTest, InsertAndFind){
  LinkedListCollection <string, double> c;
  double v;
  ASSERT_EQ(c.find("a", v), false);
  c.insert("a", 10.0);
  ASSERT_EQ(c.find("a", v), true);
  ASSERT_EQ(v, 10.0);
  ASSERT_EQ(c.find("b", v), false);
  c.insert("b", 20.0);
  ASSERT_EQ(c.find("b", v), true);
  ASSERT_EQ(v, 20.0);
}

// Test 3
TEST(BasicCollectionTest, RemoveElems){
  LinkedListCollection <string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  double v;
  c.remove("a");
  ASSERT_EQ(c.find("a", v), false);
  c.remove("b");
  ASSERT_EQ(c.find("b", v), false);
  c.remove("c");
  ASSERT_EQ(c.find("c", v), false);
  ASSERT_EQ(c.size(), 0);
}

// Test 4
TEST(BasicCollectionTest, GetKeys) {
  LinkedListCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  vector <string> ks;
  c.keys(ks);
  vector<string>::iterator iter;
  iter = find(ks.begin(), ks.end(), "a");
  ASSERT_NE(iter, ks.end());
  iter = find(ks.begin(), ks.end(), "b");
  ASSERT_NE(iter, ks.end());
  iter = find(ks.begin(), ks.end(), "c");
  ASSERT_NE(iter, ks.end());
  iter = find(ks.begin(), ks.end(), "d");
  ASSERT_EQ(iter, ks.end());
}

// Test 5
TEST(BasicCollectionTest, GetKeyRange) {
  LinkedListCollection<string ,double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  c.insert("d", 40.0);
  c.insert("e", 50.0);
  c.insert("de", 60.0);		//test to make sure it can process 2 char strings
  vector <string > ks;
  c.find("b", "d", ks);
  vector<string>::iterator iter;
  iter = find(ks.begin(), ks.end(), "b");
  ASSERT_NE(iter, ks.end());
  iter = find(ks.begin(), ks.end(), "c");
  ASSERT_NE(iter, ks.end());
  iter = find(ks.begin(), ks.end(), "d");
  ASSERT_NE(iter, ks.end());
  iter = find(ks.begin(), ks.end(), "a");
  ASSERT_EQ(iter, ks.end());
  iter = find(ks.begin(), ks.end(), "e");
  ASSERT_EQ(iter, ks.end());
  iter = find(ks.begin(), ks.end(), "de");
  ASSERT_EQ(iter,ks.end());
}

// Test 6
TEST(BasicCollectionTest, KeySort){
  LinkedListCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("e", 50.0);
  c.insert("c", 30.0);
  c.insert("b", 20.0);
  c.insert("d", 40.0);
  vector <string> sorted_ks;
  c.sort(sorted_ks);
  // check if sort order
  for (int i = 0; i < int(sorted_ks.size()) - 1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}


//Test 7
TEST(BasicCollectionTest, Equal){
  LinkedListCollection <string, double> c;
  c.insert("de", 40.0);			//test to make sure remove works on 2 char strings
  c.insert("t", 67.0);
  double v;
  c.remove("de");
  ASSERT_EQ(c.find("de", v), false);
  c.remove("i");				//test to make sure removing a string that doesnt exist works and doesnt remove anything else instead
  ASSERT_EQ(c.find("t", v), true);
  c.remove("t");
  c.remove("f");
  ASSERT_EQ(c.size(), 0);	//test to make sure when empty and remove is used, the size doesnt go below 0

}

int main(int argc, char** argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
