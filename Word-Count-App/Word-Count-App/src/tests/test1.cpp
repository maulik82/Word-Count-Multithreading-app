
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


TEST_CASE(" EX1 FIRST GIVEN TEST "){


	std::string input = " The cat sat on the mat ";
  std::cout << "Running Test 1 with input " <<input <<  std::endl;
	InputStream I(input, 0, false);
    I.readStream();
    I.calculateWordCount();
    // I.printWordCount();
    std::map<std::string, size_t> expected_out {
        {"the",2},
        {"cat",1},
        {"sat",1},
        {"on",1},
        {"mat",1}
    };

    auto resultMatch = CompareMaps(I.wordCountMap, expected_out);

    if(resultMatch)
      std::cout << "Test 1 passed - OK" << std::endl;

   REQUIRE( resultMatch == true);
   std::cout << "Test 1 completed" << std::endl;


}

TEST_CASE(" EX1 EMPTY STRING TEST "){

  std::string input = "";
  std::cout << "Running Test 2 with input " <<input <<  std::endl;
  InputStream I(input, 0, false);
    I.readStream();
    I.calculateWordCount();
    // I.printWordCount();
    std::map<std::string, size_t> expected_out {    };  // empty output

    auto resultMatch = CompareMaps(I.wordCountMap, expected_out);

    if(resultMatch)
      std::cout << "Test 2 passed - OK" << std::endl;

   REQUIRE( resultMatch == true);
   std::cout << "Test 2 completed" << std::endl;
}

TEST_CASE(" EX2 LONG STRING TEST WITH ZERO DELAY SIMULATION "){

  const char *kExampleText = R"(
    Alice was beginning to get very tired of sitting by her sister on the
    bank, and of having nothing to do: once or twice she had peeped into
    the book her sister was reading, but it had no pictures or
    conversations in it, “and what is the use of a book,” thought Alice
    “without pictures or conversations?”

    So she was considering in her own mind (as well as she could, for the
    hot day made her feel very sleepy and stupid), whether the pleasure of
    making a daisy-chain would be worth the trouble of getting up and
    picking the daisies, when suddenly a White Rabbit with pink eyes ran
    close by her.

    There was nothing so _very_ remarkable in that; nor did Alice think it
    so _very_ much out of the way to hear the Rabbit say to itself, “Oh
    dear! Oh dear! I shall be late!” (when she thought it over afterwards,
    it occurred to her that she ought to have wondered at this, but at the
    time it all seemed quite natural); but when the Rabbit actually _took a
    watch out of its waistcoat-pocket_, and looked at it, and then hurried
    on, Alice started to her feet, for it flashed across her mind that she
    had never before seen a rabbit with either a waistcoat-pocket, or a
    watch to take out of it, and burning with curiosity, she ran across the
    field after it, and fortunately was just in time to see it pop down a
    large rabbit-hole under the hedge.

    In another moment down went Alice after it, never once considering how
    in the world she was to get out again.

    The rabbit-hole went straight on like a tunnel for some way, and then
    dipped suddenly down, so suddenly that Alice had not a moment to think
    about stopping herself before she found herself falling down a very
    deep well)";

  std::string input = kExampleText;
  std::cout << "Running Test 3  " <<  std::endl;
  InputStream I(input, 0, false);
    I.readStream();
    I.calculateWordCount();
    // I.printWordCount();
    std::map<std::string, size_t> expected_out {    
      {"the",15}, 
      {"it",12},
      {"to",11},
      {"a",11},
      {"she",9},
      {"and",9},
      {"of",8},
      {"her",8},
      {"was",6},
      {"in",6},
      {"alice",6},
      {"very",5},
      {"that",4},
      {"so",4},
      {"rabbit",4},
      {"out",4},
      {"or",4},
      {"had",4},
      {"down",4},
      {"with",3},
      {"when",3},
      {"suddenly",3},
      {"on",3},
      {"for",3},
      {"but",3},
      {"at",3},
      {"went",2},
      {"well",2},
      {"way",2},
      {"watch",2},
      {"waistcoatpocket",2},
      {"time",2},
      {"thought",2},
      {"think",2},
      {"then",2},
      {"sister",2},
      {"ran",2},
      {"rabbithole",2},
      {"pictures",2},
      {"once",2},
      {"oh",2},
      {"nothing",2},
      {"never",2},
      {"moment",2},
      {"mind",2},
      {"herself",2},
      {"get",2},
      {"dear",2},
      {"conversations",2},
      {"considering",2},
      {"by",2},
      {"book",2},
      {"before",2},
      {"be",2},
      {"as",2},
      {"after",2},
      {"across",2},
      {"would",1},
      {"worth",1},
      {"world",1},
      {"wondered",1},
      {"without",1},
      {"white",1},
      {"whether",1},
      {"what",1},
      {"use",1},
      {"up",1},
      {"under",1},
      {"twice",1},
      {"tunnel",1},
      {"trouble",1},
      {"took",1},
      {"tired",1},
      {"this",1},
      {"there",1},
      {"take",1},
      {"stupid",1},
      {"straight",1},
      {"stopping",1},
      {"started",1},
      {"some",1},
      {"sleepy",1},
      {"sitting",1},
      {"shall",1},
      {"seen",1},
      {"seemed",1},
      {"see",1},
      {"say",1},
      {"remarkable",1},
      {"reading",1},
      {"quite",1},
      {"pop",1},
      {"pleasure",1},
      {"pink",1},
      {"picking",1},
      {"peeped",1},
      {"own",1},
      {"over",1},
      {"ought",1},
      {"occurred",1},
      {"not",1},
      {"nor",1},
      {"no",1},
      {"natural",1},
      {"much",1},
      {"making",1},
      {"made",1},
      {"looked",1},
      {"like",1},
      {"late",1},
      {"large",1},
      {"just",1},
      {"itself",1},
      {"its",1},
      {"is",1},
      {"into",1},
      {"i",1},
      {"hurried",1},
      {"how",1},
      {"hot",1},
      {"hedge",1},
      {"hear",1},
      {"having",1},
      {"have",1},
      {"getting",1},
      {"found",1},
      {"fortunately",1},
      {"flashed",1},
      {"field",1},
      {"feet",1},
      {"feel",1},
      {"falling",1},
      {"eyes",1},
      {"either",1},
      {"do",1},
      {"dipped",1},
      {"did",1},
      {"deep",1},
      {"day",1},
      {"daisychain",1},
      {"daisies",1},
      {"curiosity",1},
      {"could",1},
      {"close",1},
      {"burning",1},
      {"beginning",1},
      {"bank",1},
      {"another",1},
      {"all",1},
      {"again",1},
      {"afterwards",1},
      {"actually",1},
      {"about",1}
    };  // empty output

    auto resultMatch = CompareMaps(I.wordCountMap, expected_out);

    if(resultMatch)
      std::cout << "Test 3 passed - OK" << std::endl;

   REQUIRE( resultMatch == true);

   std::cout << "Test 3 completed" << std::endl;

}

TEST_CASE(" EX2 LONG STRING TEST WITH 50ms SIMULATION "){


    std::cout << "Running Test 4 .. May take a while to complete  " <<  std::endl;
    static const int numOfObjects = 1;
    InputStream I[numOfObjects];
    std::future<bool> fu[numOfObjects];
    std::vector<std::string> total_words_accumulated;
    std::map<std::string, size_t> totalwordCountMap;

    for( auto i{0}; i< numOfObjects; i++ )
        fu[i] = std::async( std::launch::async, &InputStream::readStream, &I[i]);   // create separate thread for each stream object capture
       
    volatile bool allThreadsCompleted = true;
    for( auto i{0}; i< numOfObjects; i++ )
    {
        if( fu[i].wait_for(std::chrono::seconds(0)) != std::future_status::ready ){
            allThreadsCompleted = false;
            break;
        }
    }
     
    while( !allThreadsCompleted )
     {
         for( auto i{0}; i< numOfObjects; i++ )
         {
             I[i].calculateWordCount();         // calculate word count for each stream
             std::unique_lock<std::mutex> locker2(I[i].mu_words_);
             total_words_accumulated.insert( total_words_accumulated.end(), I[i].words_accumulated.begin(), I[i].words_accumulated.end() );  // aggregate  count for all objects
             locker2.unlock();
         }
         totalwordCountMap = countWords( total_words_accumulated );  // update total word count map
         total_words_accumulated.clear();   // clear for next use
         std::this_thread::sleep_for(std::chrono::seconds(10));
         allThreadsCompleted = true;
         for( auto i{0}; i< numOfObjects; i++ )
         {
             if( fu[i].wait_for(std::chrono::seconds(0)) != std::future_status::ready ){
                 allThreadsCompleted = false;
                 break;
             }
         }
     }
    
    for( auto i{0}; i< numOfObjects; i++ )
    {
        I[i].calculateWordCount();       // calculate word count for each stream
        std::unique_lock<std::mutex> locker2(I[i].mu_words_);
        total_words_accumulated.insert( total_words_accumulated.end(), I[i].words_accumulated.begin(), I[i].words_accumulated.end() );  // aggregate  count for all objects
        locker2.unlock();
    }
    totalwordCountMap = countWords( total_words_accumulated );  // update total word count map





    // I.printWordCount();
    std::map<std::string, size_t> expected_out {    
      {"the",15}, 
      {"it",12},
      {"to",11},
      {"a",11},
      {"she",9},
      {"and",9},
      {"of",8},
      {"her",8},
      {"was",6},
      {"in",6},
      {"alice",6},
      {"very",5},
      {"that",4},
      {"so",4},
      {"rabbit",4},
      {"out",4},
      {"or",4},
      {"had",4},
      {"down",4},
      {"with",3},
      {"when",3},
      {"suddenly",3},
      {"on",3},
      {"for",3},
      {"but",3},
      {"at",3},
      {"went",2},
      {"well",2},
      {"way",2},
      {"watch",2},
      {"waistcoatpocket",2},
      {"time",2},
      {"thought",2},
      {"think",2},
      {"then",2},
      {"sister",2},
      {"ran",2},
      {"rabbithole",2},
      {"pictures",2},
      {"once",2},
      {"oh",2},
      {"nothing",2},
      {"never",2},
      {"moment",2},
      {"mind",2},
      {"herself",2},
      {"get",2},
      {"dear",2},
      {"conversations",2},
      {"considering",2},
      {"by",2},
      {"book",2},
      {"before",2},
      {"be",2},
      {"as",2},
      {"after",2},
      {"across",2},
      {"would",1},
      {"worth",1},
      {"world",1},
      {"wondered",1},
      {"without",1},
      {"white",1},
      {"whether",1},
      {"what",1},
      {"use",1},
      {"up",1},
      {"under",1},
      {"twice",1},
      {"tunnel",1},
      {"trouble",1},
      {"took",1},
      {"tired",1},
      {"this",1},
      {"there",1},
      {"take",1},
      {"stupid",1},
      {"straight",1},
      {"stopping",1},
      {"started",1},
      {"some",1},
      {"sleepy",1},
      {"sitting",1},
      {"shall",1},
      {"seen",1},
      {"seemed",1},
      {"see",1},
      {"say",1},
      {"remarkable",1},
      {"reading",1},
      {"quite",1},
      {"pop",1},
      {"pleasure",1},
      {"pink",1},
      {"picking",1},
      {"peeped",1},
      {"own",1},
      {"over",1},
      {"ought",1},
      {"occurred",1},
      {"not",1},
      {"nor",1},
      {"no",1},
      {"natural",1},
      {"much",1},
      {"making",1},
      {"made",1},
      {"looked",1},
      {"like",1},
      {"late",1},
      {"large",1},
      {"just",1},
      {"itself",1},
      {"its",1},
      {"is",1},
      {"into",1},
      {"i",1},
      {"hurried",1},
      {"how",1},
      {"hot",1},
      {"hedge",1},
      {"hear",1},
      {"having",1},
      {"have",1},
      {"getting",1},
      {"found",1},
      {"fortunately",1},
      {"flashed",1},
      {"field",1},
      {"feet",1},
      {"feel",1},
      {"falling",1},
      {"eyes",1},
      {"either",1},
      {"do",1},
      {"dipped",1},
      {"did",1},
      {"deep",1},
      {"day",1},
      {"daisychain",1},
      {"daisies",1},
      {"curiosity",1},
      {"could",1},
      {"close",1},
      {"burning",1},
      {"beginning",1},
      {"bank",1},
      {"another",1},
      {"all",1},
      {"again",1},
      {"afterwards",1},
      {"actually",1},
      {"about",1}
    };  // empty output

   // REQUIRE( CompareMaps(totalwordCountMap, expected_out) == true);
    auto resultMatch = CompareMaps(totalwordCountMap, expected_out);

    if(resultMatch)
      std::cout << "Test 4 passed - OK" << std::endl;

   REQUIRE( resultMatch == true);



   std::cout << "Test 4 completed" << std::endl;
}




