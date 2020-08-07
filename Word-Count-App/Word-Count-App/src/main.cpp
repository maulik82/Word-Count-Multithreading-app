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
*/
void ex2() {

    static const int numOfObjects = 10;
    InputStream I[numOfObjects];
    std::future<void> fu[numOfObjects];
    std::vector<std::string> total_words_accumulated;
    std::map<std::string, size_t> totalwordCountMap;

    for( auto i{0}; i< numOfObjects; i++ )
        fu[i] = std::async( std::launch::async, &InputStream::readStream, &I[i]);   // create separate thread for each stream object capture
    
     while( ( fu[0].wait_for(std::chrono::seconds(10)) != std::future_status::ready )    &&
            ( fu[1].wait_for(std::chrono::seconds(10)) != std::future_status::ready )    &&
            ( fu[2].wait_for(std::chrono::seconds(10)) != std::future_status::ready )    &&
            ( fu[3].wait_for(std::chrono::seconds(10)) != std::future_status::ready )    &&
            ( fu[4].wait_for(std::chrono::seconds(10)) != std::future_status::ready )    &&
            ( fu[5].wait_for(std::chrono::seconds(10)) != std::future_status::ready )    &&
            ( fu[6].wait_for(std::chrono::seconds(10)) != std::future_status::ready )    &&
            ( fu[7].wait_for(std::chrono::seconds(10)) != std::future_status::ready )    &&
            ( fu[8].wait_for(std::chrono::seconds(10)) != std::future_status::ready )    &&
            ( fu[9].wait_for(std::chrono::seconds(10)) != std::future_status::ready ) )
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
