#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <thread>

#include "csv.hpp"
#include "file_loader.hpp"
#include "options.hpp"
#include "utility.hpp"
#include "vsm.hpp"

int main(int argc, char *argv[]) {
  ProgramOptions options;
  options.buildOptions();
  if (options.parseOptions(argc, argv, std::cout)) {
    std::cerr << "Import Data!\n";
    FileLoader reader(options.getParams());
    VSMTypes::TermDocumentMatrix matrix = reader.matrix();
    VSMTypes::Queries queries = reader.queries();
    VSMTypes::GoldSet goldSet = reader.goldSet();
    VSMTypes::DocumentList docs = reader.documentList();

    std::cerr << "Construct VSM!\n";
    VSM vsm(matrix);

    VSMTypes::EffectivenessAllSet allRanks;
    VSMTypes::EffectivenessBestSet bestRanks;

    std::cerr << "Begin Query Similarity!\n";

    // detect number of HW threads
    unsigned totalThreads = std::thread::hardware_concurrency();

    // if we could not detect, default to dual-core
    if (totalThreads == 0) {
      totalThreads = 2;
    }
    std::cerr << "  Note: using " << totalThreads << " HW Threads\n";

    // define task to run
    auto task = [&](unsigned threadID) {
      auto index(0);
      for (const auto &q : queries) {
        // it was easier to do a simple check instead of chunking
        // (non-deterministic size)
        if (index % totalThreads == threadID) {
          const auto &query = q.first;
          auto sim = vsm.similarity(q);
          sortSetByWeight(sim);
          auto ranks = buildDocumentRank(sim, goldSet, query);
          bestRanks.emplace(query, getBestRank(ranks));
          allRanks.emplace(query, std::move(ranks));
        }
        ++index;
      }
    };

    // run in parallel
    std::vector<std::thread> tasks;
    for (unsigned i = 0; i < totalThreads; ++i)
      tasks.emplace_back(task, i);

    // wait for execution to complete
    for (auto &task : tasks)
      task.join();

    std::cerr << "Generating Output File!\n";
    CSVFile outputFile(options.getParams(), docs, goldSet, allRanks, bestRanks);

    std::cerr << "Writing Output File!\n";
    outputFile.write();

    std::cerr << "Done!" << std::endl;
  }
  return EXIT_SUCCESS;
}
