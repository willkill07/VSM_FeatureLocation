#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include "vsm_types.hpp"

void sortSetByWeight(VSMTypes::RankedList &);

bool operator==(const VSMTypes::RankedItem &, const VSMTypes::RankedItem &);

VSMTypes::DocumentRank buildDocumentRank(const VSMTypes::RankedList &,
                                         const VSMTypes::GoldSet &,
                                         const VSMTypes::QueryID &);

VSMTypes::Countable getBestRank(const VSMTypes::DocumentRank &);

#endif /* _UTILITY_HPP_ */
