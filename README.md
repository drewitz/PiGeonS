# PiGeonS

**P**olygons as f**i**nite **geo**desically right-a**n**gled **s**equences

This is an implementation of the algorithm described in [On right-angled polygons in hyperbolic space, E. Dotti, S. Drewitz, Geom Dedicata (2018)](https://doi.org/10.1007/s10711-018-0357-y).

## Installation

So far, it is only tested on Linux.
It uses the [GluCat library](https://github.com/penguian/glucat).
After installing GluCat as described in the [INSTALL](https://github.com/penguian/glucat/blob/master/INSTALL) file, you need to clone and compile the programme:

```bash
$ git clone https://github.com/drewitz/PiGeonS
$ cd PiGeonS
$ make
```

## Running and Examples

The programme `pigeons` takes the parameters `q_1, q_2, ..., q_{p-3}` as input.
The generator `i_k` of the Clifford algebra is written as `{-k}`, so for example, the Clifford vector `a + b i_1 + c i_2` is written as `a+b{-1}+c{-2}`.

Examples for running it are:
```bash
$ ./pigeons 2{-1} 2{-2}
$ ./pigeons -1+{-1} -2+2{-2}
```
The first example yields a degenerate pentagon, the second one a non-degenerate one.

Additional examples are in the file [runtest.sh](runtest.sh).
