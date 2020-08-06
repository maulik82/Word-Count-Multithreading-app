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


/**
* Ex2 - calculates word count of mulitple streams in multiple threads
*/
void ex2() {

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
