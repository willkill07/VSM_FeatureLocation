#!/bin/bash

./main \
-M data/jEdit4.3/CorpusMethods-jEdit4.3-AfterSplitStopStem.txt \
-P data/jEdit4.3/CorpusMethods-jEdit4.3.mapping \
-F data/jEdit4.3/CorpusQueries-jEdit4.3-AfterSplitStopStem.txt \
-G data/jEdit4.3/jEdit4.3GoldSets/ \
-Q data/jEdit4.3/jEdit4.3ListOfFeatureIDs.txt
