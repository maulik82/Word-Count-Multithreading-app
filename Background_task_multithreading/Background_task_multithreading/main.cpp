//
//  main.cpp
//  Background_task_multithreading
//
//  Created by  Maulik Patel on 06/08/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//

#include <iostream>
#include <thread>
#include  <future>
#include <chrono>



void bkg_task(std::future<void> futureObj) {
    
    std::cout << "Bkg task Start" << std::endl;
      while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
      {
          static int i{0};
          std::cout << " Running bck task " << i++  << std::endl;
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
      std::cout << "Bkg task End" << std::endl;
}




bool readTask(){
    std::cout << "Read Task start" << std::endl;
    int count{0};
    for(int i = 0; i<50; i++)
    {
        count +=i;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "\nRead Task complete" << std::endl;
    return true;
}


void bkg_task2() {
    static int i2{0};
    std::cout << " Running bck task2 " << i2++  << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";

    /*
    std::promise<void> exitSignal;   // Create a std::promise object
    std::future<void> futureObj = exitSignal.get_future();      //Fetch std::future object associated with promise
    
    std::future<void> fu_bkg = std::async( std::launch::async, &bkg_task, std::move(futureObj)); // launch bkg task
    std::future<bool> readComplete = std::async( std::launch::async, readTask);  // launch read task
    readComplete.get();

    std::this_thread::sleep_for(std::chrono::seconds(2)); //Wait for 10 sec

    std::cout << "Asking bkg task to Stop" << std::endl;
    exitSignal.set_value(); //Set the value in promise
    std::cout << "Bkg task End" << std::endl;

     */
    
    std::cout << "Reading Again Start" << std::endl;
    std::future<bool> readComplete2 = std::async( std::launch::async, readTask);  // launch read task
    std::cout << "Bkg task2 Start" << std::endl;

    while( readComplete2.wait_for(std::chrono::seconds(1)) != std::future_status::ready )
    {
        bkg_task2();
    }
    std::cout << "Bkg task End" << std::endl;





    return 0;
}
