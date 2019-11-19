#!/usr/bin/env python

import math

def chunked(iterator, chunksize):
    """
    Yields items from 'iterator' in chunks of size 'chunksize'.

    >>> list(chunked([1, 2, 3, 4, 5], chunksize=2))
    [(1, 2), (3, 4), (5,)]
    """
    chunk = []
    for idx, item in enumerate(iterator, 1):
        chunk.append(item)
        if idx % chunksize == 0:
            yield chunk
            chunk = []
    if chunk:
        yield chunk

bits = 16
samples = 1024
vmax = 2**16
vhalf = vmax/2

wavetable_sin = [vhalf + vhalf*math.sin(x*2*math.pi/samples) for x in range(samples)]

width = 8
with open('wavetables.h', 'w') as f:
    f.write("int wavetable_sin[] = {\n    ")
    rows = [("%6d, " * (len(x)-1) + "%6d") % tuple(x) for x in chunked(wavetable_sin, width)]
    f.write(',\n    '.join(rows))
    f.write("\n};\n\n")