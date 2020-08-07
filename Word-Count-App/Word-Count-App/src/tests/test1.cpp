
 // test1.cpp
 // TDD

 // Created by  Maulik Patel on 22/07/2020.
 // Copyright © 2020 Maulik Patel. All rights reserved.



#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <cstdlib>
#include "../utils.h"
#include "../input_stream.h"

template <typename T, typename U>
bool CompareMaps(const std::map<std::string,T>& l, const std::map<std::string,U>& r)
{
    return false;  // different types
}

template <typename T>
bool CompareMaps(const std::map<std::string,T>& l, const std::map<std::string,T>& r)
{
  // same types, proceed to compare maps here

  if(l.size() != r.size())
    return false;  // differing sizes, they are not the same

  typename std::map<std::string,T>::const_iterator i, j;
  for(i = l.begin(), j = r.begin(); i != l.end(); ++i, ++j)
  {
    if(*i != *j)
      return false;
  }

  return true;
}


TEST_CASE(" FIRST GIVEN TEST "){

	std::string input = " The cat sat on the mat ";
	InputStream I(input, 0, false);
    I.readStream();
    I.calculateWordCount();

    std::map<std::string, size_t> expected_out {
        {"the",2},
        {"cat",1},
        {"sat",1},
        {"on",1},
        {"mat",1}
    };

   REQUIRE( CompareMaps(I.wordCountMap, expected_out) == true);
}






