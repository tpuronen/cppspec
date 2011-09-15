/*
 * Copyright 2007 Timo Puronen
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "SpecRunner.h"
#include "SpecificationRegistry.h"
#include "Reporter.h"
#include "SpecDoxReporter.h"
#include "JUnitReporter.h"
#include "BoostTimer.h"
#include "ConsoleOutputStream.h"
#include "ThreadPool.h"
#include <boost/program_options.hpp>

namespace CppSpec {

class RemoveIfNotToBeRun {
public:
    RemoveIfNotToBeRun(const std::vector<std::string>& specificationsToRun) : specificationsToRun(specificationsToRun) {}
    
    bool operator()(Runnable* runnable) {
        return std::find(specificationsToRun.begin(), specificationsToRun.end(), runnable->getName()) == specificationsToRun.end();
    }
    
private:
    const std::vector<std::string>& specificationsToRun;    
};
    
SpecRunner::SpecRunner(int argc, const char* argv[]) {
    boost::program_options::options_description options("Options");
    options.add_options()
        ("output,o", boost::program_options::value<std::string>(), "define output format. Allowed values: junit console")
        ("no-logs", "do not create log files when using JUnitReporter. No effect on other reporters")
        ("report-dir",  boost::program_options::value<std::string>(), "directory where JUnit reports are created")
        ("specification,s", boost::program_options::value<std::vector<std::string> >(&specificationsToRun),"specification to be run, if multiple specifications will be run, the option can be repeated")
        ("multithreaded,m", "run tests using multiple threads to shorten execution time")
        ("help,h", "show help");
    arguments = new boost::program_options::variables_map();
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, options), *arguments);
    boost::program_options::notify(*arguments);
    if (arguments->count("help")) {
        std::cout << options << std::endl;
        exit(0);
    }
}

SpecRunner::~SpecRunner() {
    delete arguments;
}

int SpecRunner::runSpecifications() {
    return runSpecs(specificationsToRun);
}

OutputStream* SpecRunner::createOutputStream() {
    return new ConsoleOutputStream();
}

Reporter* SpecRunner::createReporter(OutputStream& outputStream) {
    if (arguments->count("output")) {
        const std::string& selectedReporter((*arguments)["output"].as<std::string>());
        if (selectedReporter == "junit") {
            if (arguments->count("no-logs")) {
                return new JUnitReporter();
            } else {
                std::string reportPath(".");
                if (arguments->count("report-dir")) {
                    reportPath = (*arguments)["report-dir"].as<std::string>();
                }
                return new JUnitReporter(reportPath);
            }
        }
    }
    return new SpecDoxReporter(outputStream);
}

bool SpecRunner::runSpecs(const std::vector<std::string>& specificationsToRun) {
    OutputStream* output = createOutputStream();
    Reporter* reporter = createReporter(*output);
    std::vector<Runnable*> specs = SpecificationRegistry::instance().getSpecifications();
    std::vector<Runnable*>::iterator last = specs.end();
    if (!specificationsToRun.empty()) {
        RemoveIfNotToBeRun removeIfNotToBeRun(specificationsToRun);
        last = std::remove_if(specs.begin(), specs.end(), removeIfNotToBeRun);
    }
    int threads(1);
    if (arguments->count("multithreaded")) {
        threads = std::max((unsigned int)1, boost::thread::hardware_concurrency());
    }
    ThreadPool pool(threads);
    pool.start(specs.begin(), last, *reporter);
    
    bool failures = reporter->anyBehaviorFailed();
    delete reporter;
    delete output;
    return failures;
}

}
