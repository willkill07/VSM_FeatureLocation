#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "file_loader.hpp"

FileLoader::FileLoader(FileList list) {
  _matrix = buildMatrix(list.methodMapFile, list.methodFile);

  _queries = buildQueries(list.queryFile, list.featureFile);

  _goldSet = buildGoldSet(list.goldSetDirectory);

  _documentList = buildDocumentList(list.methodMapFile);
}

VSMTypes::Queries FileLoader::queries() { return _queries; }

VSMTypes::TermDocumentMatrix FileLoader::matrix() { return _matrix; }

VSMTypes::GoldSet FileLoader::goldSet() { return _goldSet; }

VSMTypes::DocumentList FileLoader::documentList() { return _documentList; }

std::vector<FileLoader::Token>
FileLoader::splitLine(const FileLoader::Line line) {
  std::vector<FileLoader::Token> tokenized;
  std::istringstream ss(line);
  std::copy(std::istream_iterator<FileLoader::Token>(ss),
            std::istream_iterator<FileLoader::Token>(),
            std::back_inserter(tokenized));
  return tokenized;
}

VSMTypes::Queries FileLoader::buildQueries(const FileLoader::FileName ids,
                                           const FileLoader::FileName info) {
  VSMTypes::Queries result;
  std::ifstream idFile(ids);
  std::ifstream infoFile(info);
  std::string idLine, infoLine;
  while (std::getline(idFile, idLine) && std::getline(infoFile, infoLine)) {
    VSMTypes::QueryID qid = std::stoi(idLine);
    auto tokens = splitLine(infoLine);
    VSMTypes::Query q;
    for (auto t : tokens) {
      ++q[t];
    }
    result.emplace(qid, q);
  }
  return result;
}

VSMTypes::TermDocumentMatrix
FileLoader::buildMatrix(const FileLoader::FileName names,
                        const FileLoader::FileName info) {
  VSMTypes::TermDocumentMatrix result;
  std::ifstream nameFile(names);
  std::ifstream infoFile(info);
  std::string nameLine, infoLine;
  while (std::getline(nameFile, nameLine) && std::getline(infoFile, infoLine)) {
    VSMTypes::MatrixRow<VSMTypes::Countable> row;
    auto tokens = splitLine(infoLine);
    for (auto t : tokens) {
      ++row[t];
    }
    result.emplace(nameLine, row);
  }
  return result;
}

int getID(std::string str) {
  static std::regex not_digit("[^[:digit:]+]");
  static std::string nothing("");
  return std::stoi(std::regex_replace(str, not_digit, nothing));
}

VSMTypes::GoldSet FileLoader::buildGoldSet(const FileLoader::FileName dir) {
  boost::filesystem::path directory(dir);

  VSMTypes::GoldSet gold;

  using dirItr = boost::filesystem::directory_iterator;
  for (auto file = dirItr(directory); file != dirItr(); ++file) {
    VSMTypes::QueryID id = getID(file->path().filename().string());
    boost::filesystem::ifstream ifs(file->path());
    std::string line;
    VSMTypes::QueryList list;
    while (std::getline(ifs, line)) {
      list.push_back(std::move(line));
    }
    gold.emplace(id, list);
  }
  return gold;
}

VSMTypes::DocumentList
FileLoader::buildDocumentList(const FileLoader::FileName names) {
  std::ifstream nameFile(names);
  VSMTypes::DocumentList list;
  std::string nameLine;
  while (std::getline(nameFile, nameLine)) {
    list.push_back(std::move(nameLine));
  }
  return list;
}
