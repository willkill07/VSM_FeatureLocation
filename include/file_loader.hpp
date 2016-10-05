#ifndef _FILE_LOADER_HPP_
#define _FILE_LOADER_HPP_

#include "file_list.hpp"
#include "vsm_types.hpp"

class FileLoader {
public:
  using FileName = std::string;
  using Line = std::string;
  using Token = std::string;

  FileLoader(FileList list);

  VSMTypes::Queries queries();

  VSMTypes::TermDocumentMatrix matrix();

  VSMTypes::GoldSet goldSet();

  VSMTypes::DocumentList documentList();

private:
  VSMTypes::Queries buildQueries(const FileName, const FileName);

  VSMTypes::TermDocumentMatrix buildMatrix(const FileName, const FileName);

  VSMTypes::GoldSet buildGoldSet(const FileName);

  VSMTypes::DocumentList buildDocumentList(const FileName);

  std::vector<Line> splitLine(const Line);

  VSMTypes::Queries _queries;
  VSMTypes::TermDocumentMatrix _matrix;
  VSMTypes::GoldSet _goldSet;
  VSMTypes::DocumentList _documentList;
};

#endif /* _FILE_LOADER_HPP_ */
