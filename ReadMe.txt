														Programming Assignment 1
	   												     Devansh Bansal, Diksha Jena
														   B20CS094, B20CS013

How To Run:
	--> gcc -o FSM FSM.cpp -lstdc++
	--> ./FSM input.in (input.in is the file provided to us for the input)

What it Generates as Output:
	--> It generates pa_1.out file containing pair of token_ID and value of that token in each line, as a token is encountered.
	--> It also generates symbol_table_1.out file, which contains keywords and identifiers encountered in the input file, with 0 in-front of keywords, and 1 in-front of identifiers (as mentioned in the Programming Assignment)

How it generates these files:
	--> We read the content of input file in a string buffer, and then tokenize the string buffer, generally based on space as the delimeter.
	--> In some special cases, space was not serving a proper role of delimeter, so we had to match the token with various different known tokens, and we found the longest matching token.
	--> For each of the different kind of tokens, viz. Relational Operators, Assignment Operators, Arithmetic Operators, Signed and Unsigned Integer Constants, Signed and Unsigned Floating-Point Constants, Special Symbols, Keywords; we wrote a function to identify that given string is of which type of token.

Assumptions:
	--> There were no assumptions made as such, we just created the FSM, which takes input from a file, and generates symbol table, as well as a file corresponding to tokens in that file.

															THANK YOU

