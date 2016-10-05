The Questions have two interpretations based on which 2 versions have been developed.
Interpretations differ based on counting of false positives.

## Interpretation 1

False positive for any input string has only two values based on the following -
1. It is 1 if hash code of any hash table element matches with the input pattern but pattern is not found in the hash table.
2. n rest all cases is it is 0 including when pattern is found.

## Interpretation 1

False positive for any input string represents the counts when the input string is probed in the hash table in matches where hash value matches but not the string.

* For running the particular interpretation please refer there Readme.txt separately.