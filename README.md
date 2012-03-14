# COMP 345 Assignment 3 -- megaint

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
