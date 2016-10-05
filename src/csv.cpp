#include <algorithm>
#include <fstream>

#include "csv.hpp"

CSVFile::CSVFile(const FileList &fileList,
                 const VSMTypes::DocumentList &docList,
                 const VSMTypes::GoldSet &goldSet,
                 const VSMTypes::EffectivenessAllSet &allRanks,
                 const VSMTypes::EffectivenessBestSet &bestRanks)
    : fileName(fileList.outputFile), data() {
  // build feature list
  for (const auto &goldLine : goldSet) {
    VSMTypes::QueryID id = goldLine.first;
    const auto &docs = goldLine.second;
    bool firstLine = true;
    for (const auto &doc : docs) {
      auto posItr = std::find(std::begin(docList), std::end(docList), doc);
      int pos =
          ((posItr == docList.end()) ? -1 : (1 + (posItr - docList.begin())));
      VSMTypes::Countable all = allRanks.at(id).at(doc);
      VSMTypes::Countable best = bestRanks.at(id);
      data.emplace_back(firstLine, id, pos, doc, all, best);
      firstLine = false;
    }
  }
}

void CSVFile::write() {
  std::ofstream outFile(fileName);
  for (const auto &line : data) {
    writeLine(outFile, line);
  }
  outFile.close();
}

void CSVFile::writeLine(std::ostream &out, const Line &line) {
  const auto &firstLine = std::get<0>(line);
  const auto &query = std::get<1>(line);
  const auto &id = std::get<2>(line);
  const auto &name = std::get<3>(line);
  const auto &rank = std::get<4>(line);
  const auto &best = std::get<5>(line);
  if (std::get<0>(line)) // first line
  {
    out << query;
  }
  out << '\t' << id << '\t' << name << '\t';
  if (rank > 0) {
    out << rank;
  }
  out << '\t';
  if (firstLine && best > 0) {
    out << best;
  }
  out << '\n';
}
