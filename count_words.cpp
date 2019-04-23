//
// Created by Vitaliy Vorobyov on 2019-04-23.
//

#include <string>
#include <map>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <fstream>

std::map<std::string, int> words_count(std::string text) {
    std::map<std::string, int> words_counter;

    char chars[] = ".,?!-";

    std::transform(text.begin(), text.end(), text.begin(), ::tolower);


    for (int i = 0; i < strlen(chars); ++i) {
        text.erase(std::remove(text.begin(), text.end(), chars[i]), text.end());
    }

    std::string word;

    for(std::stringstream s(text); s >> word;) {
        std::map<std::string, int>::const_iterator itr = words_counter.find(word);

        if( itr!=words_counter.end() )
        {
            words_counter[word] += 1;
        }else{
            words_counter[word] = 1;
        }
    }

    return words_counter;
}

int main() {

    std::map<std::string, int> test = words_count("This form allows you to generate random text strings. The randomness comes from atmospheric noise, which for many purposes is better than the pseudo-random number algorithms typically used in computer programs.");

    for(auto it = test.cbegin(); it != test.cend(); ++it)
    {
        std::cout << it->first << " " << it->second << "\n";
    }

}
