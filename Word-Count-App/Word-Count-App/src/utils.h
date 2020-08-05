//
//  utils.h
//  GuruSystems
//
//  Created by  Maulik Patel on 04/08/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//

#pragma once
#include <chrono>
#include <random>
#include <string>
#include <thread>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <set>
#include <cctype>
#include <future>
#include <chrono>
#include <mutex>


extern std::vector<std::string> split_string(std::string strToSplit, char delimeter);
extern std::map<std::string, size_t> countWords(std::vector<std::string> const& words);

// Function to swap keys and values of a map and return a vector pair of the swapped values
template <typename K, typename V>
std::vector<std::pair<V, K>>
invertMap2(std::map<K, V> const& myMap)
{
    std::vector<std::pair<V, K> > myvec;
    // traverse the map and pushback the values -> keys
    for (auto const& pair : myMap) {
        myvec.push_back( std::make_pair(pair.second,  pair.first));
    }
    return myvec;
}
  



