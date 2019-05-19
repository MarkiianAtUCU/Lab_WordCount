//
// Created by Vitaliy Vorobyov on 2019-04-23.
//

#include <string>
#include <map>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <queue>

//std::map<std::string, int> words_count(std::string text) {
//    std::map<std::string, int> words_counter;
//
//    char chars[] = ".,?!';:\"`~@#$%^&*(()_+=[]{}/><|";
//
//    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
//
//
//    for (int i = 0; i < strlen(chars); ++i) {
//        text.erase(std::remove(text.begin(), text.end(), chars[i]), text.end());
//    }
//
//    std::string word;
//
//    for(std::stringstream s(text); s >> word;) {
//        std::map<std::string, int>::const_iterator itr = words_counter.find(word);
//
//        if( itr!=words_counter.end() )
//        {
//            words_counter[word] += 1;
//        }else{
//            words_counter[word] = 1;
//        }
//    }
//
//    return words_counter;
//}

std::map<std::string, int> words_count(std::stringstream& inp) {
    std::map<std::string, int> words_counter;

    char chars[] = ".,?!';:\"`~@#$%^&*(()_+=[]{}/><|";
    std::string text = inp.str();

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

template<typename T>
class threadsafe_queue
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };
    std::mutex head_mutex;
    std::unique_ptr<node> head;
    std::mutex tail_mutex;
    node* tail;
    node* get_tail()
    {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return tail;
    }
    std::unique_ptr<node> pop_head()
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);

        if(head.get()==get_tail())
        {
            return nullptr;
        }
        std::unique_ptr<node> old_head=std::move(head);
        head=std::move(old_head->next);
        return old_head;
    }
public:
    threadsafe_queue():
            head(new node),tail(head.get())
    {}
    threadsafe_queue(const threadsafe_queue& other)=delete;
    threadsafe_queue& operator=(const threadsafe_queue& other)=delete;
    std::shared_ptr<T> try_pop()
    {
        std::unique_ptr<node> old_head=pop_head();
        return old_head?old_head->data:std::shared_ptr<T>();
    }
    void push(T& new_value)
    {
        std::shared_ptr<T> new_data(
                std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node);
        node* const new_tail=p.get();
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        tail->data=new_data;
        tail->next=std::move(p);
        tail=new_tail;
    }
};




int main() {

    threadsafe_queue<std::stringstream> q;

    std::ifstream file("test.txt");

    std::vector<std::stringstream> vec;

    std::stringstream ss;
    ss.str("Testtting");

    std::stringstream& a = ss;

    vec.push_back(a);

    std::cout << vec.data() << std::endl;


    if (file.is_open()) {
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();

        q.push(ss);

    }

    std::map<std::string, int> test = words_count(*q.try_pop());

    for(auto it = test.cbegin(); it != test.cend(); ++it)
        {
            std::cout << it->first << " " << it->second << "\n";
        }
}
