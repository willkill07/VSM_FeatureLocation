#include <algorithm>
#include <cmath>

#include "vsm.hpp"

VSM::VSM(const VSMTypes::TermDocumentMatrix &matrix) {
  auto tf = normalize(matrix);
  auto df = computeDocumentFrequency(matrix);
  auto n = getDocumentCount(matrix);
  auto idf = computeInverseDocumentFrequency(df, n);
  weightedMatrix = constructWeighted(tf, idf);
}

VSMTypes::RankedList
VSM::similarity(const std::pair<VSMTypes::QueryID, VSMTypes::Query> &q) {
  VSMTypes::Query query = q.second;
  VSMTypes::RankedList list;
  for (const auto &row : weightedMatrix) {
    auto docName = row.first;
    auto docTerms = row.second;
    auto cosineSim = cosineSimilarity(query, docTerms);
    list.emplace_back(docName, cosineSim);
  }
  return list;
}

VSMTypes::Weight VSM::cosineSimilarity(VSMTypes::Query query,
                                       VSMTypes::WeightedMatrixRow document) {
  VSMTypes::Weight qSum(0.0);
  VSMTypes::Weight dSum(0.0);
  VSMTypes::Weight dqSum(0.0);

  VSMTypes::TermList list;

  for (const auto &i : query) {
    qSum += i.second * i.second;
    list.insert(i.first);
  }
  qSum = sqrt(qSum);

  for (const auto &i : document) {
    dSum += i.second * i.second;
    list.insert(i.first);
  }
  dSum = sqrt(dSum);

  for (const auto &i : list) {
    dqSum += query[i] * document[i];
  }
  return dqSum / (dSum * qSum);
}

VSMTypes::NormalizedTermDocumentMatrix
VSM::normalize(const VSMTypes::TermDocumentMatrix &matrix) {
  VSMTypes::NormalizedTermDocumentMatrix newMatrix;
  for (auto &itr : matrix) {
    VSMTypes::MatrixRow<VSMTypes::Weight> newRow;
    VSMTypes::Countable sum(0);
    for (auto &i : itr.second) {
      sum += i.second;
    }
    for (auto &i : itr.second) {
      newRow[i.first] = static_cast<VSMTypes::Weight>(i.second) / sum;
    }
    newMatrix[itr.first] = newRow;
  }
  return newMatrix;
}

VSMTypes::DocumentFrequency
VSM::computeDocumentFrequency(const VSMTypes::TermDocumentMatrix &matrix) {
  VSMTypes::DocumentFrequency df;
  for (auto &i : matrix) {
    for (auto &j : i.second) {
      ++df[j.first];
    }
  }
  return df;
}

VSMTypes::InverseDocumentFrequency
VSM::computeInverseDocumentFrequency(const VSMTypes::DocumentFrequency &df,
                                     VSMTypes::Countable n) {
  VSMTypes::Weight N(n);
  VSMTypes::InverseDocumentFrequency idf;
  for (const auto &i : df) {
    idf[i.first] = log(N / i.second);
  }
  return idf;
}

VSMTypes::Countable
VSM::getDocumentCount(const VSMTypes::TermDocumentMatrix &m) {
  return m.size();
}

VSMTypes::WeightedMatrix
VSM::constructWeighted(const VSMTypes::NormalizedTermDocumentMatrix &tf,
                       const VSMTypes::InverseDocumentFrequency &idf) {
  VSMTypes::WeightedMatrix wm;
  for (auto i : tf) {
    auto doc = i.first;
    VSMTypes::WeightedMatrixRow newRow;
    for (auto j : i.second) {
      auto t = j.first;
      auto w = j.second;
      newRow[t] = w * idf.at(t);
    }
    wm[doc] = newRow;
  }
  return wm;
}
