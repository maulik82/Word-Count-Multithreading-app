//
//  main.cpp
//  GuruSystems
//
//  Created by  Maulik Patel on 04/08/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//


#include "input_stream.h"

/**
* Ex1 - calculates word count of single stream in single thread
 The InputStream class (declared in input_stream.h) allows a stream of text to be read character-by-character.
 Write code to count the number of occurrences of each word and display the totals. For example:
 Input: "The cat sat on the mat."
 Output:
 the : 2
 cat : 1
 mat : 1
 on : 1
 sat : 1
 The output should be sorted by descending word frequency with ties ordered alphabetically.
*/
void ex1( std::string input ) {
//    std::string input = "The the cat!!1 sat sat  sat sat  on456    the>>>   mat.";
    InputStream I(input, 0, false);
    I.readStream();
    I.calculateWordCount();
    I.printWordCount();
}


/**
* Ex2 - calculates word count of mulitple streams in multiple threads
 By passing in a random seed and the ‘slow’ flag to the constructor, InputStream can simulate
 the delays that might be experienced when reading data over a network.
 Write code that takes 10 InputStream objects and consumes them in parallel.
 It should output intermediate word counts every 10 seconds and a final total at the end.
 The ‘kExampleText’ constant provides some example text to test your implementation against
 */
void ex2() {

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
         std::cout << "\n----------- Intermediate Counts -----------" <<  std::endl;
         for( auto i{0}; i< numOfObjects; i++ )
         {
             I[i].calculateWordCount();         // calculate word count for each stream
             std::unique_lock<std::mutex> locker2(I[i].mu_words_);
             total_words_accumulated.insert( total_words_accumulated.end(), I[i].words_accumulated.begin(), I[i].words_accumulated.end() );  // aggregate  count for all objects
             locker2.unlock();
         }
         totalwordCountMap = countWords( total_words_accumulated );  // update total word count map
         printMap(totalwordCountMap);       // print intermediate map
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
    
    
    
  
    std::cout << "\n----------- Final Counts -----------" <<  std::endl;
    for( auto i{0}; i< numOfObjects; i++ )
    {
        I[i].calculateWordCount();       // calculate word count for each stream
        std::unique_lock<std::mutex> locker2(I[i].mu_words_);
        total_words_accumulated.insert( total_words_accumulated.end(), I[i].words_accumulated.begin(), I[i].words_accumulated.end() );  // aggregate  count for all objects
        locker2.unlock();
    }
    totalwordCountMap = countWords( total_words_accumulated );  // update total word count map
    printMap(totalwordCountMap);    // print intermediate map

}


void Usage(){
    std::cout << "  \
    The program can be invoked by the following command line:         \n   \
    ./Word-Count-App ex1  \"The cat sat on the mat.\"                  \n   \
    where                                                                 \n   \
    •    ex1 runs exercise 1, followed by string to know word count for " << std::endl;
}


/**
* Main - Run two exercises
*/

int main(int argc, const char * argv[]) {
    std::string input = "The the cat!!1 sat sat  sat sat  on456    the>>>   mat.";   // default input
    if (argc == 1)
    {
        std::cout << "You have NOT provided any additional arguments." << std::endl;
        std::cout << "   The program will run with default arguments  \n ";
        std::cout  << "   For custom arguments; please type ./Word-Count-App help"  << std::endl;
    }

    else if (argc == 3)
    {
        if( strcmp(argv[1], "ex1") != 0)  {  Usage(); std::exit(1);   }
        else {   input =  argv[2];  }
    }
    else
    {
        Usage();
    }
    
    std::cout << "Running exercise 1  with input : " << input << std::endl;
    ex1( input );      // Run exercise 1
    std::cout << "\n---------------------" << std::endl;
    std::cout << "Running exercise 2 " << std::endl;
    ex2();      // Run exercise 2

    std::cout << std::endl;
    return 0;
}
