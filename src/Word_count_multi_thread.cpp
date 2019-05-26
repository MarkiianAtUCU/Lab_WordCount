#include <iostream>
#include "boost/filesystem.hpp"
#include "../dependencies/FileProcessor.h"
#include <vector>
#include "boost/locale.hpp"
#include "../dependencies/time_meter.h"
#include "../dependencies/config_reader.h"
#include <thread>
#include <mutex>
#include <boost/iterator/distance.hpp>

void process (std::mutex & mtx, std::vector<std::string> & data, long from, long to, std::vector<std::map<std::string, int>> & res) {

    std::map<std::string, int> res_map;
    for(; from < to; from++)
        res_map[boost::locale::fold_case(data[from])]++;

    mtx.lock();
    res.push_back(res_map);
    mtx.unlock();

}

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
    int num_threads = config_object.get_int("num_threads");

    std::mutex mtx;
    std::map<std::string, int> res_map;
    std::vector<std::map<std::string, int>> threads_result;
    std::vector<std::string> all_text;
    std::vector<std::thread> all_threds;

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
    for(boost::locale::boundary::ssegment_index::iterator it=map.begin(),e=map.end(); it!=e; ++it) {
        all_text.push_back(it -> str());
    }

    auto end = get_current_time_fenced();
    long long time_prepare = to_us(end - start);

//    Words count
    auto size = all_text.size();
    auto block_size = size / num_threads;

    start = get_current_time_fenced();
    for (int i = 0; i < num_threads-1; ++i) {
        all_threds.emplace_back(process, std::ref(mtx), std::ref(all_text), i * block_size, (i + 1) * block_size, std::ref(threads_result));
    }
    all_threds.emplace_back(process, std::ref(mtx), std::ref(all_text), (num_threads-1) * block_size, size ,std::ref(threads_result));

    std::cout << all_threds.size();

    for (auto & entry : all_threds)
        entry.join();

    end = get_current_time_fenced();
    long long time_count = to_us(end - start);

    for (auto & entry : threads_result) {
        MapProcessor::merge_maps(res_map, entry);
        entry.clear();
    }

    std::cout << "[LOAD with SPLIT] T: " << time_prepare << std::endl;
    std::cout << "[COUNT] T: " << time_count << std::endl;
    std::cout << "[OVERALL] T: " << time_prepare + time_count << std::endl;

//    Write results
    MapProcessor::write_to_file_alphabetic(out_file_a, res_map);
    MapProcessor::write_to_file_quantity(out_file_n, res_map);
    return 0;

}