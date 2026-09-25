# Arbitrary Precision Arithmetic
In computer science, arbitrary-precision arithmetic, also called bignum arithmetic, multiple-precision arithmetic, or sometimes infinite-precision arithmetic, indicates that calculations are performed on numbers whose digits of precision are potentially limited only by the available memory of the host system. This contrasts with the faster fixed-precision arithmetic found in most arithmetic logic unit (ALU) hardware, which typically offers between 8 and 64 bits of precision.

Several modern programming languages have built-in support for bignums, and others have libraries available for arbitrary-precision integer and floating-point math. Rather than storing values as a fixed number of bits related to the size of the processor register, these implementations typically use variable-length arrays of digits.

Arbitrary precision is used in applications where the speed of arithmetic is not a limiting factor, or where precise results with very large numbers are required. It should not be confused with the symbolic computation provided by many computer algebra systems, which represent numbers by expressions such as π·sin(2), and can thus represent any computable number with infinite precision.

Applications
A common application is public-key cryptography, whose algorithms commonly employ arithmetic with integers having hundreds of digits. Another is in situations where artificial limits and overflows would be inappropriate. It is also useful for checking the results of fixed-precision calculations, and for determining optimal or near-optimal values for coefficients needed in formula

read: https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic
