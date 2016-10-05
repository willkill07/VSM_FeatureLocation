#!/bin/bash

echo ""
echo "Timing"
echo "===================="

time \
./main \
-M data/jEdit4.3/CorpusMethods-jEdit4.3-AfterSplitStopStem.txt \
-P data/jEdit4.3/CorpusMethods-jEdit4.3.mapping \
-F data/jEdit4.3/CorpusQueries-jEdit4.3-AfterSplitStopStem.txt \
-G data/jEdit4.3/jEdit4.3GoldSets/ \
-Q data/jEdit4.3/jEdit4.3ListOfFeatureIDs.txt \
2>&1 > time.log

echo ""
echo "Callgrind"
echo "===================="

valgrind \
--tool=callgrind \
--callgrind-out-file=callgrind.out \
./main \
-M data/jEdit4.3/CorpusMethods-jEdit4.3-AfterSplitStopStem.txt \
-P data/jEdit4.3/CorpusMethods-jEdit4.3.mapping \
-F data/jEdit4.3/CorpusQueries-jEdit4.3-AfterSplitStopStem.txt \
-G data/jEdit4.3/jEdit4.3GoldSets/ \
-Q data/jEdit4.3/jEdit4.3ListOfFeatureIDs.txt \
2>&1 > callgrind.log
callgrind_annotate --inclusive=yes --tree=caller callgrind.out >> callgrind.log
rm callgrind.out

echo ""
echo "Cachegrind"
echo "===================="

valgrind \
--tool=cachegrind \
--cachegrind-out-file=cachegrind.out \
--branch-sim=yes \
--cache-sim=yes \
./main \
-M data/jEdit4.3/CorpusMethods-jEdit4.3-AfterSplitStopStem.txt \
-P data/jEdit4.3/CorpusMethods-jEdit4.3.mapping \
-F data/jEdit4.3/CorpusQueries-jEdit4.3-AfterSplitStopStem.txt \
-G data/jEdit4.3/jEdit4.3GoldSets/ \
-Q data/jEdit4.3/jEdit4.3ListOfFeatureIDs.txt \
2>&1 > cachegrind.log
cg_annotate cachegrind.out >> cachegrind.log
rm cachegrind.out

echo ""
echo "Memcheck"
echo "===================="

valgrind \
./main \
-M data/jEdit4.3/CorpusMethods-jEdit4.3-AfterSplitStopStem.txt \
-P data/jEdit4.3/CorpusMethods-jEdit4.3.mapping \
-F data/jEdit4.3/CorpusQueries-jEdit4.3-AfterSplitStopStem.txt \
-G data/jEdit4.3/jEdit4.3GoldSets/ \
-Q data/jEdit4.3/jEdit4.3ListOfFeatureIDs.txt \
2>&1 > memcheck.log
