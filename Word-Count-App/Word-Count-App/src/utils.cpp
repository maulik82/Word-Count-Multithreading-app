//
//  utils.cpp
//  GuruSystems
//
//  Created by  Maulik Patel on 04/08/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//

#include "utils.h"
/*
std::string split implementation by using delimiter as a character.
*/
std::vector<std::string> split_string(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
       splittedStrings.push_back(item);
    return splittedStrings;
}


std::map<std::string, size_t> countWords(std::vector<std::string> const& words)
{
    auto wordCount = std::map<std::string, size_t>{};
    for (auto const& word : words)
        ++wordCount[word];
    return wordCount;
}


