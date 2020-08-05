//
//  main.cpp
//  GuruSystems
//
//  Created by  Maulik Patel on 04/08/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//


#include "input_stream.h"


int main(int argc, const char * argv[]) {

    std::string input = "The the cat!!1 sat sat  sat sat  on456    the>>>   mat.";
    InputStream I(input, 0, false);
    I.readStream();
    I.calculateAndPrintWordCount();

    std::cout << "---------------------" << std::endl;
    
//    By passing in a random seed and the ‘slow’ flag to the constructor, InputStream can simulate the delays that might be experienced when reading data over a network.
//    Write code that takes 10 InputStream objects and consumes them in parallel. It should output intermediate word counts every 10 seconds and a final total at the end. The ‘kExampleText’ constant provides some example text to test your implementation against
//
    
    std::string input2 = "Alice was beginning to get very tired of sitting by her  sister on the   bank, and of having nothing to do:";
    InputStream I2(input2, 5, true);
//    InputStream I2(kExampleText, 5, true);
    
//    std::thread th1( &InputStream::calculateWordCount, &I2 );
//    th1.join();
    I2.readStream();
    I2.calculateWordCount();
    I2.printWordCount();

    

//    I2.calculateWordCount();

    std::cout << std::endl;
    return 0;
}
