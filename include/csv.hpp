#ifndef _CSV_HPP_
#define _CSV_HPP_

#include <iostream>

#include "file_list.hpp"
#include "vsm_types.hpp"

class CSVFile {

public:
  CSVFile(const FileList &, const VSMTypes::DocumentList &,
          const VSMTypes::GoldSet &, const VSMTypes::EffectivenessAllSet &,
          const VSMTypes::EffectivenessBestSet &);

  void write();

  using Line = std::tuple<bool, VSMTypes::QueryID, int, VSMTypes::Document,
                          VSMTypes::Countable, VSMTypes::Countable>;

private:
  std::string fileName;
  std::vector<Line> data;

  void writeLine(std::ostream &, const Line &);
};

#endif /* _CSV_HPP_ */
