#ifndef __THREAD_POOL__
#define __THREAD_POOL__

#include "Runnable.h"
#include <boost/thread.hpp>

namespace CppSpec {

class ThreadPool {
private:
    class Consumer {
    public:
        template<typename Iterator>
        Consumer(Iterator begin, Iterator end) : specs(begin, end), threads(0) {}
        
        Runnable* getSpec() {
            boost::lock_guard<boost::mutex> lock(specsLock);
            if (specs.empty()) {
                return NULL;
            }
            Runnable* spec = specs.back();
            specs.pop_back();
            return spec;
        }
        
        void addResult(const SpecResult& result) {
            boost::lock_guard<boost::mutex> lock(resultLock);
            results.push_back(result);
            cond.notify_one();
        }
        
        void operator()() {
            incrementThreadCount();
            Runnable* spec = getSpec();
            while (spec != NULL) {
                SpecResult result = (*spec)();
                addResult(result);
                spec = getSpec();
            }      
            decrementThreadCount();
        }
        
        bool isReady() const {
            return threads == 0 && results.empty();
        }
        
    private:
        void incrementThreadCount() {
            boost::lock_guard<boost::mutex> lock(threadCountLock);
            ++threads;
        }
        
        void decrementThreadCount() {
            boost::lock_guard<boost::mutex> lock(threadCountLock);
            --threads;
        }
        
    public:
        std::vector<SpecResult> results;
        boost::mutex resultLock;
        boost::condition_variable cond;
        
    private:
        std::vector<Runnable*> specs;
        boost::mutex specsLock;
        int threads;
        boost::mutex threadCountLock;
    };
    
public:
    template<typename InputIterator>
    //void start(const std::vector<Runnable*> specs, Reporter& reporter) {
    void start(InputIterator begin, InputIterator end, Reporter& reporter) {
        if (std::distance(begin, end) == 0) {
            return;
        }
        
        Consumer consumer(begin, end);
        int coreCount(boost::thread::hardware_concurrency());
        for (int i = 0; i < std::max(1, coreCount); ++i) {
            threads.push_back(new boost::thread(boost::ref(consumer)));
        }

        while (true) {
            boost::unique_lock<boost::mutex> lock(consumer.resultLock);
            while(consumer.results.empty()) {
                consumer.cond.wait(lock);
            }
            SpecResult res = consumer.results.back();
            consumer.results.pop_back();
            lock.unlock();
            reporter.addSpecification(res);
            if (consumer.isReady()) {
                break;
            }
        }
        for (std::vector<boost::thread*>::const_iterator it = threads.begin(); it != threads.end(); ++it) {
            (*it)->join();
            delete *it;
        }
    }
    
private:
    std::vector<boost::thread*> threads;
};
    
}

#endif // __THREAD_POOL__