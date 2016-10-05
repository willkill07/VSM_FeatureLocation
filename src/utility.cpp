#include <algorithm>
#include <iterator>
#include <set>

#include "utility.hpp"

void sortSetByWeight(VSMTypes::RankedList &list) {
  std::stable_sort(
      std::begin(list), std::end(list),
      [](const VSMTypes::RankedItem &i1, const VSMTypes::RankedItem &i2) {
        return (std::get<1>(i1) > std::get<1>(i2));
      });
}

bool operator==(const VSMTypes::RankedItem &i1,
                const VSMTypes::RankedItem &i2) {
  return (std::get<0>(i1) == std::get<0>(i2));
}

VSMTypes::DocumentRank buildDocumentRank(const VSMTypes::RankedList &list,
                                         const VSMTypes::GoldSet &goldSet,
                                         const VSMTypes::QueryID &q) {
  const VSMTypes::GoldList &gold = goldSet.at(q);
  VSMTypes::DocumentRank ranks;
  size_t index(1);
  for (const auto &g : gold) {
    ranks[g] = -1;
  }
  for (const auto &item : list) {
    const auto &doc = std::get<0>(item);
    if (gold.cend() != std::find(std::begin(gold), std::end(gold), doc)) {
      // no rank change //

      ranks[doc] = index;

      // floor

      // const auto & val = std::get <1> (item);
      // auto i (index);
      // while (i >= 0 && val == std::get <1> (list [i--]));
      // ranks [doc] = i + 1;

      // ceiling

      // const auto & val = std::get <1> (item);
      // auto i (index);
      // while (i < list.size() && val == std::get <1> (list [i++]));
      // ranks [doc] = i - 1;
    }
    ++index;
  }
  return ranks;
}

VSMTypes::Countable getBestRank(const VSMTypes::DocumentRank &ranks) {
  using Countable = VSMTypes::Countable;
  std::vector<Countable> list;
  std::transform(
      std::begin(ranks), std::end(ranks), std::inserter(list, std::begin(list)),
      [](const VSMTypes::DocumentRank::value_type &val) -> Countable {
        return val.second;
      });
  list.erase(std::remove_if(std::begin(list), std::end(list),
                            [](const Countable &num) { return (num < 0); }),
             std::end(list));
  return (list.size() == 0)
             ? -1
             : *std::min_element(std::begin(list), std::end(list));
}
