# Pattern Searcher

A C++ program to search pattern in given input file.

### Multiple search

You can search multiple strings. Provide multiple search strings in P.txt and data in T.txt

We offer you 2 options for the same. Either using linear probing or separate chaining.

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
./q1 <table-size>
:  table-size is optional and by default calculated based on load factor.

*Run multiple search using separate chaining
./q1-chain <table-size>
:  table-size is optional and by default calculated based on load factor.


****************************************************************************************
****************************************************************************************


### Single search with multiple optional characters

You can search single string with multiple optional characters specified by ?. Provide data in T2.txt
*Example You can type in something like ?orcius and have the program match this pattern to the Porcius

We offer you 2 options for the same. Either using linear probing or separate chaining.

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
./q2 <search-string> <table-size> <code-no> <value-no>
:  table-size is optional and by default calculated based on load factor.
:  code-no and value-no are optional and by default 2.
:  To specify code-no and value-no but skip specifiying table-size type 0 for table-size.

*Run single search using separate chaining
./q2-chain <search-string> <table-size> <code-no> <value-no>
:  table-size is optional and by default calculated based on load factor.
:  code-no and value-no are optional and by default 2.
:  To specify code-no and value-no but skip specifiying table-size type 0 for table-size.


****************************************************************************************
****************************************************************************************


### Multiple search with single optional characters

You can search multiple string with single optional characters specified by ?. Provide multiple search strings in P2.txt and data in T2.txt
*Example You can type in something like ?orcius and have the program match this pattern to the Porcius

We offer you 2 options for the same. Either using linear probing or separate chaining.

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

*Run mutliple search using linear probing
./q2-mult-input <table-size> <code-no> <value-no>
:  table-size is optional and by default calculated based on load factor.
:  code-no and value-no are optional and by default 2.
:  To specify code-no and value-no but skip specifiying table-size type 0 for table-size.

*Run multiple search using separate chaining
./q2-mult-input-chain <table-size> <code-no> <value-no>
:  table-size is optional and by default calculated based on load factor.
:  code-no and value-no are optional and by default 2.
:  To specify code-no and value-no but skip specifiying table-size type 0 for table-size.


*You can clean the program using
make clean

Developed by Naman Goyal, 2015CSB1021
