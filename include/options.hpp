#ifndef _OPTIONS_HPP_
#define _OPTIONS_HPP_

#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include "file_list.hpp"

class ProgramOptions {
public:
  void buildOptions();

  bool parseOptions(int, char **, std::ostream &);

  FileList getParams();

private:
  boost::program_options::variables_map map;
  boost::program_options::options_description desc;

  FileList list;
};

#endif /* _OPTIONS_HPP_ */
