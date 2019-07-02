# QM
This project aims to use quine mccluskey algorithm to read a text file and produce the prime
implicates, and essential prime implicates based on the minterms and don’t care terms. The
general procedure is:
1) Reading the text file to get the number of variables, the minterm terms, and the don’t
care terms.
2) Produce the prime implicates of the received Boolean function.
3) Produce the essential prime implicants based on chart table.
We basically decided on implementing two different data structure (1)vectors (2)map data structure which could
be possible to be used in the quine mucklasky algorithm and try to find the most efficient one in
terms of time complexity. We succeeded to get the results from both the code but in different
execution time showing which of them is faster and better according to time complexity.
