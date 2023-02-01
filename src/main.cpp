#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;
template <typename T> 
class TSQueue
{
    private:
     queue<T> q;
     mutable mutex mut;
     condition_variable cv;
    public:
        TSQueue()
        {}
        TSQueue(TSQueue<T> const& otherQ)
        {
            //lock_guard lg(otherQ.mut);
            //q = otherQ;
        }
        void push(T el)
        {
            lock_guard<mutex> lg(mut); 
            q.push(el);
            cv.notify_one();
        }
        //TESTED 
        void wait_and_pop(T& value)
        {
            unique_lock ul(mut);
            cv.wait(ul,[this]{return !q.empty();});
            value = q.front();
            q.pop();
        } 
        // TESTED
        shared_ptr<T> wait_and_pop()
        {
            unique_lock ul(mut);
            cv.wait(ul, [this]{!q.empty();});
            shared_ptr<T> res = make_shared<T>(q.front());
            q.pop();
            return res;
        }
        //TESTED
        bool try_and_pop(T& value)
        {
            lock_guard lg(mut);
            if(q.empty())
                return false;
            value = q.front();
            q.pop();
            return true;
            
        }
        // TESTED
        shared_ptr<T> try_and_pop()
        {
            lock_guard lg(mut);
            if(q.empty())
                return shared_ptr<T>();
            shared_ptr<T> res = make_shared<T>(q.front());
            q.pop();
            return res;
        }
        // TESTED
        bool empty() const
        {
            lock_guard lg(mut);
            return q.empty();
        }
};
void feedQ(TSQueue<string> &tsq)
{
    bool end_found = false;
    while(!end_found)
    {
        std::string el;
        std::cout << "Insert a new word (Type end to finish): ";
        std::cin >> el; 
        tsq.push(el);
        if(el == "end")
            end_found = true;
            
    }
}
void printQ(TSQueue<string> &q)
{
    string val = "";
    while(val!="end")
    {   
        q.wait_and_pop(val);
        cout << "printing q value: " << val << endl;
    }
}
int main()
{
    cout << "Hello world" <<endl;
    TSQueue<string> q;
    thread producer(&feedQ, ref(q));
    thread consumer(&printQ,ref(q));
    producer.join();
    consumer.join();
    cout << "print Completed" << endl;
    return 0;
}