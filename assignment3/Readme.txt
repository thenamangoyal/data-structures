# Pattern Searcher

A C++ program to search pattern in given input file.

### Multiple search

You can search multiple strings. Provide multiple search strings in P.txt and data in T.txt

We offer you 3 options for the same. Eitehr using linear probing or separate chaining or optimisied linear probing.

There are four hash codes:
1. Integer Casting (Code 0)
2. Component Sum (Code 1)
3. Polynomial Sum (Code 2)
4. Cyclic Sum (Code 3)

And there are three hash values
1. Division (Code 0)
2. MAD (Code 1)
3. Multiplication (Code 2)

*Complie the code using 
make

*Run multiple search using linear probing
./q1

*Run multiple search using separate chaining
./q1-chain

*Run multiple search using optimised linear probing
./q1-optimise

### Single search with optional characters

You can search single string with optioanl characters specified by ?. Provide data in T2.txt
*Example You can type in something like ?orcius and have the program match this patternto the Porcius

We offer you 3 options for the same. Eitehr using linear probing or separate chaining or optimisied linear probing.

There are four hash codes:
1. Integer Casting (Code 0)
2. Component Sum (Code 1)
3. Polynomial Sum (Code 2)
4. Cyclic Sum (Code 3)

And there are three hash values
1. Division (Code 0)
2. MAD (Code 1)
3. Multiplication (Code 2)

*Complie the code using 
make

*Run single search using linear probing
./q2 <search_string> <code_no> <value_no>
value_no and code_no are optioanl and by default 2.

*Run single search using separate chaining
./q2-chain <search_string> <code_no> <value_no>
value_no and code_no are optioanl and by default 2.

*Run single search using optimised linear probing
./q2-optimise <search_string> <code_no> <value_no>
value_no and code_no are optioanl and by default 2.

*You can clean the program using
make clean

Developed by Naman Goyal, 2015CSB1021