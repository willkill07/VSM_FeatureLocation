#ifndef _VSM_HPP_
#define _VSM_HPP_

#include "vsm_types.hpp"

class VSM {

public:
  VSM(const VSMTypes::TermDocumentMatrix &);

  VSMTypes::RankedList
  similarity(const std::pair<VSMTypes::QueryID, VSMTypes::Query> &);

private:
  VSMTypes::WeightedMatrix weightedMatrix;

  VSMTypes::NormalizedTermDocumentMatrix
  normalize(const VSMTypes::TermDocumentMatrix &);

  VSMTypes::DocumentFrequency
  computeDocumentFrequency(const VSMTypes::TermDocumentMatrix &);

  VSMTypes::InverseDocumentFrequency
  computeInverseDocumentFrequency(const VSMTypes::DocumentFrequency &df,
                                  VSMTypes::Countable N);

  VSMTypes::Countable getDocumentCount(const VSMTypes::TermDocumentMatrix &);

  VSMTypes::WeightedMatrix
  constructWeighted(const VSMTypes::NormalizedTermDocumentMatrix &,
                    const VSMTypes::InverseDocumentFrequency &);

  VSMTypes::Weight cosineSimilarity(VSMTypes::Query,
                                    VSMTypes::WeightedMatrixRow);
};

#endif /* _VSM_HPP_ */
