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
    SpecRunner();

    void runSpecifications(int argc, char* argv[]);

private:
    OutputStream* createOutputStream(boost::program_options::variables_map& args);
    Reporter* createReporter(boost::program_options::variables_map& args, OutputStream& outputStream);
    void runSpecs(const std::vector<std::string>& specifications, Reporter* reporter);

private:
    SpecRunner(const SpecRunner&);
    SpecRunner& operator=(const SpecRunner&);

};

}

#endif /*SPECRUNNER_H_*/
