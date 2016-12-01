The Questions have two interpretations based on which 2 versions have been developed.
Interpretations differ based on counting of false positives.

## Interpretation 1

False positive for any input string has only two values based on the following -
1. It is 1 if hash code of any hash table element matches with the input pattern but pattern is not found in the hash table.
2. In rest all cases is it is 0 including the case when pattern is found.

## Interpretation 2

False positive for any input string represents the counts the no of probes in the hash table while searching for an input pattern where hash value matches but not the string.

*For running the particular interpretation please refer there Readme.txt separately.