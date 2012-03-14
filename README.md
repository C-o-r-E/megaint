# COMP 345 Assignment 3 -- megaint

Authors: Corey Clayton (9349200) and Tavish Armstrong (9276254)
March, 2012

The `megaint` class can store an arbitrarily large integral number, similarly to the Integer type in haskell. It can do addition, subtraction, multiplication, exponentiation, and can be output to a stream.

## Examples

    megaint a(10);
    megaint b(30);
    megaint c = a * b; // 300
    megaint d = a + b; // 40
    megaint e = a - b; // -20
    megaint f = a^b; // 1000000000000000000000000000000

## Implementation notes

`megaint` is pretty basic. It simply stores a `vector` of type `bool`, where each bool is a bit in the number. That is, `megaint` runs on base 2.

Important: There was no requirement to use base 10 numbers. It was also explicitly stated that we can deal in the realm of positive integers only.

--> if you have difficulty reading the larger binary numbers (313 ^ 313), try doing a mathematical proof.
	example: (313 ^ 313) == (313 ^ 312) * 313


### Corey

	Linux 3.2.9-1
	gcc version 4.6.3
	GNU Emacs 23.4.1

### Tavish

  Linux 3.0.0-16-generic
  gcc version 4.6.1 (Ubuntu/Linaro 4.6.1-9ubuntu3) 
  VIM - Vi IMproved 7.3 (2010 Aug 15, compiled Oct  6 2011 10:34:41)

## Build Instructions

   Simply run "make"