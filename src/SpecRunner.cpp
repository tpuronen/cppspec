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
#include "Needle/Binder.h"
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>

namespace CppSpec {

class ShouldBeRun {
public:
    explicit ShouldBeRun(const std::vector<std::string>& specificationsToRun) :
        specificationsToRun(specificationsToRun) {
    }

    bool operator()(const std::string& name) {
        return specificationsToRun.empty() ||
            std::find(specificationsToRun.begin(), specificationsToRun.end(), name) != specificationsToRun.end();
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
    OutputStream* outputStream = createOutputStream();
    Needle::Binder::instance().bind<Reporter>(createReporter(*outputStream));
    Needle::Binder::instance().bind<Timer>(new BoostTimer(), "spec");
    Needle::Binder::instance().bind<Timer>(new BoostTimer(), "behavior");
    
    runSpecs(specificationsToRun);
    
    delete outputStream;
    Needle::Inject<Reporter> reporter;
    return reporter->anyBehaviorFailed();
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

void SpecRunner::runSpecs(const std::vector<std::string>& specificationsToRun) {
    ShouldBeRun shouldBeRun(specificationsToRun);
    std::vector<boost::thread*> threads;
    BOOST_FOREACH(Runnable* specification, SpecificationRegistry::instance().getSpecifications()) {
        if(shouldBeRun(specification->getName())) {
            boost::thread* t = new boost::thread(boost::ref(*specification));
            threads.push_back(t);
        }
    }
    BOOST_FOREACH(boost::thread* t, threads) {
        t->join();
        delete t;
    }
}

}
