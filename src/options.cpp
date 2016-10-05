#include "options.hpp"

namespace po = boost::program_options;

void ProgramOptions::buildOptions() {
  desc.add_options()
		("help,h", "display help message")
		("method-file,M", po::value<std::string>(&list.methodFile),
		 "Filename of file which contains list of post-processed method information")
		("method-map,P", po::value<std::string>(&list.methodMapFile),
		 "Filename of file mapping method name in order to \"method-file\"")
		("query-file,Q", po::value<std::string>(&list.queryFile),
		 "Filename of file which contains list of queries")
		("gold-set-dir,G", po::value<std::string>(&list.goldSetDirectory),
		 "Directory containing all Gold Set query files")
		("feature-file,F", po::value<std::string>(&list.featureFile),
		 "Filename of file which contains list of features")
		("output-file,O", po::value<std::string>(&list.outputFile)->default_value("VSM_Effectiveness.csv"),
		 "CSV output file");
}

FileList ProgramOptions::getParams() { return list; }

bool ProgramOptions::parseOptions(int ac, char *av[], std::ostream &os) {
  po::store(po::parse_command_line(ac, av, desc), map);
  po::notify(map);
  if (map.count("help") ||
      !(map.count("method-file") && map.count("method-map") &&
        map.count("query-file") && map.count("gold-set-dir") &&
        map.count("feature-file"))) {
    os << desc << std::endl;
    return false;
  }
  return true;
}
