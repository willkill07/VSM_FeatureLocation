#ifndef _VSM_TYPES_HPP_
#define _VSM_TYPES_HPP_

#include <cstdlib>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct VSMTypes {
  using Term = std::string;
  using Document = std::string;
  using Countable = int;
  using Weight = float;

  template <typename T> using MatrixRow = std::unordered_map<Term, T>;

  using WeightedMatrixRow = MatrixRow<Weight>;
  using CountableMatrixRow = MatrixRow<Countable>;

  template <typename T>
  using Matrix = std::unordered_map<Document, MatrixRow<T>>;

  using TermDocumentMatrix = Matrix<Countable>;
  using NormalizedTermDocumentMatrix = Matrix<Weight>;
  using WeightedMatrix = Matrix<Weight>;

  using DocumentFrequency = std::unordered_map<Term, Countable>;
  using InverseDocumentFrequency = std::unordered_map<Term, Weight>;

  using QueryID = Countable;
  using QueryList = std::vector<Term>;

  using TermList = std::unordered_set<Term>;

  using Query = std::unordered_map<Term, Countable>;
  using QueryItem = std::pair<QueryID, Query>;
  using Queries = std::map<QueryID, Query>;

  using GoldList = std::vector<Document>;
  using GoldSet = std::map<QueryID, GoldList>;

  using RankedItem = std::tuple<Document, Weight>;
  using RankedList = std::vector<RankedItem>;

  using DocumentList = std::vector<Document>;

  using DocumentRank = std::unordered_map<Document, Countable>;
  using EffectivenessAllSet = std::unordered_map<QueryID, DocumentRank>;

  using EffectivenessBestSet = std::unordered_map<QueryID, Countable>;
};

#endif /* _VSM_TYPES_HPP_ */
