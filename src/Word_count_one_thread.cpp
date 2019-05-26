#include <iostream>
#include "boost/filesystem.hpp"
#include "../dependencies/FileProcessor.h"
#include <vector>
#include "boost/locale.hpp"
#include "../dependencies/time_meter.h"
#include "../dependencies/config_reader.h"


int main(int argc, char **argv) {
    if (argc != 2) {
        try {
            auto config_object = config("./config.dat");
        } catch (...) {
            std::cout << "Incorrect number of arguments:" << std::endl << "./Word_count2_multi_thread <config path>" <<std::endl;
            exit(1);
        }
    }
    boost::locale::generator gen;
    std::locale loc = gen("");
    std::locale::global(loc);
    std::wcout.imbue(loc);
    std::ios_base::sync_with_stdio(false);

    auto config_object = config(argv[1]);
    std::string in_file = config_object.get_string("in_file");
    std::string out_file_a = config_object.get_string("out_file_a");
    std::string out_file_n = config_object.get_string("out_file_n");

    std::map<std::string, int> res_map;
    std::vector<std::string> all_text;

    auto start = get_current_time_fenced();
//    Read file
    auto file = boost::filesystem::path(in_file);

    try {
        if (FileProcessor::is_archive(file)) {
            FileProcessor::process_archive(file.string(), all_text);
        } else if (FileProcessor::is_text(file)) {
            FileProcessor::process_file(file.string(), all_text);
        }
    } catch (std::exception &e) {
        std::cout << "Exception was thrown while unarchiving/reading from file, terminating" << std::endl;
        std::cout << e.what();
        return 1;
    }



//    Prepare file for counting
    std::string text_for_processing = all_text[0];
    text_for_processing = boost::locale::normalize(text_for_processing);
    boost::locale::boundary::ssegment_index map(boost::locale::boundary::word,text_for_processing.begin(),text_for_processing.end());
    map.rule(boost::locale::boundary::word_letters);
    all_text.clear();
    auto end = get_current_time_fenced();
    long long time_prepare = to_us(end - start);

//    Words count
    start = get_current_time_fenced();
    for(boost::locale::boundary::ssegment_index::iterator it=map.begin(),e=map.end(); it!=e; ++it)
        res_map[boost::locale::fold_case(it->str())]++;

    end = get_current_time_fenced();
    long long time_count = to_us(end - start);

    
//    Write results
    start = get_current_time_fenced();
    MapProcessor::write_to_file_alphabetic(out_file_a, res_map);
    MapProcessor::write_to_file_quantity(out_file_n, res_map);
    end = get_current_time_fenced();
    long long overall_time = to_us(end-start);
    
    
    std::cout << "[LOAD with SPLIT] T: " << time_prepare << std::endl;
    std::cout << "[COUNT] T: " << time_count << std::endl;
    std::cout << "[OVERALL] T: " << time_prepare + time_count + overall_time<< std::endl;

    return 0;

}