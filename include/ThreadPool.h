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
            cond.notify_all();
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
    ThreadPool(int threadCount) : threadCount(threadCount) {}
    
    template<typename InputIterator>
    void start(InputIterator begin, InputIterator end, Reporter& reporter) {
        if (std::distance(begin, end) == 0) {
            return;
        }
        
        Consumer consumer(begin, end);
        for (int i = 0; i < threadCount; ++i) {
            threads.push_back(new boost::thread(boost::ref(consumer)));
        }

        while (true) {
            boost::unique_lock<boost::mutex> lock(consumer.resultLock);
            while(consumer.results.empty()) {
                consumer.cond.wait(lock);
                if (consumer.isReady()) {
                    break;
                }
            }
            if (!consumer.results.empty()) {
              SpecResult res = consumer.results.back();
              consumer.results.pop_back();
              lock.unlock();
              reporter.addSpecification(res);
            }
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
    int threadCount;
};
    
}

#endif // __THREAD_POOL__