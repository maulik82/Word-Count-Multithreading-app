//
//  main.cpp
//  GuruSystems
//
//  Created by  Maulik Patel on 04/08/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//


#include "input_stream.h"


//TODO: add usage and run from cmd line
// add make and catch test
// run with multiple objects
// update aggregate and total counts


/**
* Ex1 - calculates word count of single stream in single thread
*/
void ex1() {
    std::string input = "The the cat!!1 sat sat  sat sat  on456    the>>>   mat.";
    InputStream I(input, 0, false);
    I.readStream();
    I.calculateWordCount();
    I.printWordCount();
}


void printMap(  std::map<std::string, size_t>& countMap )
{
      std::vector<std::pair<size_t, std::string>> output_map  = invertMap2(countMap);

    // sort the vector pair to get  results similar to a map
      sort(output_map.begin(),  output_map.end(),    [](std::pair<size_t, std::string>& a,    std::pair<size_t, std::string>& b)
      {
          if (a.first != b.first)
              return a.first > b.first;
          return a.second > b.second;
      });
    
      for (auto it  = output_map.begin();  it != output_map.end();  ++it)
          std::cout << it->second << " : "  << it->first << ", ";
}


/**
* Ex2 - calculates word count of mulitple streams in multiple threads
*/
void ex2() {

    static constexpr int numOfObjects = 2;
    InputStream I[numOfObjects];
    std::future<void> fu[numOfObjects];
    std::vector<std::string> total_words_accumulated;
    std::map<std::string, size_t> totalwordCountMap;

    
    
    for( auto i{0}; i< numOfObjects; i++ )
    {
        fu[i] = std::async( std::launch::async, &InputStream::readStream, &I[i]);
    }
    
     while( ( fu[0].wait_for(std::chrono::seconds(10)) != std::future_status::ready )    &&
            ( fu[1].wait_for(std::chrono::seconds(10)) != std::future_status::ready ) )
     {
         std::cout << "\n----------- Intermediate Counts -----------" <<  std::endl;
         for( auto i{0}; i< numOfObjects; i++ )
         {
             I[i].calculateWordCount();
             std::unique_lock<std::mutex> locker2(I[i].mu_words_);
             total_words_accumulated.insert( total_words_accumulated.end(), I[i].words_accumulated.begin(), I[i].words_accumulated.end() );
             locker2.unlock();
         }
//         for( auto word : total_words_accumulated)
//             std::cout <<  word << ", ";
//         std::cout << std::endl;
         
         totalwordCountMap = countWords( total_words_accumulated );  // update total word count map
         printMap(totalwordCountMap);
         total_words_accumulated.clear();
     }
    std::cout << "\n----------- Final Counts -----------" <<  std::endl;
    for( auto i{0}; i< numOfObjects; i++ )
    {
        I[i].calculateWordCount();
        std::unique_lock<std::mutex> locker2(I[i].mu_words_);
        total_words_accumulated.insert( total_words_accumulated.end(), I[i].words_accumulated.begin(), I[i].words_accumulated.end() );
        locker2.unlock();
    }
    totalwordCountMap = countWords( total_words_accumulated );  // update total word count map
    printMap(totalwordCountMap);
}



/**
* Ex2a - calculates word count of mulitple streams in multiple threads
*/
void ex2a() {

//    Write code that takes 10 InputStream objects and consumes them in parallel. It should output intermediate word counts every 10 seconds and a final total at the end. The ‘kExampleText’ constant provides some example text to test your implementation against

//    std::string input2 = "Alice was beginning to get very tired of sitting by her  sister on the   bank, and of having nothing to do:";
//    InputStream I2(input2, 5, true);
    InputStream I2(kExampleText, 50, true);

    // while reading in progress
    // sleep for 10 seconds and print intermediate counts
    // once reading is complete; join threads and print final counts
    
    std::future<void> fu = std::async( std::launch::async, &InputStream::readStream, &I2  ); // launch read task
    while( fu.wait_for(std::chrono::seconds(10)) != std::future_status::ready )
    {
        std::cout << "\n----------- Intermediate Counts -----------" <<  std::endl;
        I2.calculateWordCount();
        I2.printWordCount();
    }
    std::cout << "\n----------- Final Counts -----------" <<  std::endl;
    I2.calculateWordCount();
    I2.printWordCount();
}




int main(int argc, const char * argv[]) {

    ex1();      // Run example 1
    std::cout << "\n---------------------" << std::endl;
    ex2();      // Run example 2
    std::cout << std::endl;
    return 0;
}
