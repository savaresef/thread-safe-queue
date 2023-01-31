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
            lock_guard lg(otherQ.mut);
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
            cv.wait(ul, [this]{!q.empty;});
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
int main()
{
    cout << "Hello world" <<endl;
    return 0;
}