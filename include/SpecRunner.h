#ifndef SPECRUNNER_H_
#define SPECRUNNER_H_

#include "CppSpecConfig.h"
#include <string>
#include <vector>

namespace boost {
	namespace program_options {
		class variables_map;
	}
}

namespace CppSpec {

class OutputStream;
class Reporter;

class CppSpec_EXPORT SpecRunner {
public:
    SpecRunner(int argc, char* argv[]);
    virtual ~SpecRunner();

public:
    bool runSpecifications();
    friend class SpecRunnerTestAccessor;

private:
    OutputStream* createOutputStream();
    Reporter* createReporter(OutputStream& outputStream);
    bool runSpecs(const std::vector<std::string>& specifications, Reporter* reporter);

private:
    boost::program_options::variables_map* arguments;
    std::vector<std::string> specificationsToRun;

private:
    SpecRunner(const SpecRunner&);
    SpecRunner& operator=(const SpecRunner&);
};

}

#endif /*SPECRUNNER_H_*/
