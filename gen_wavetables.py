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
vmax = 2**16 - 1
vhalf = vmax/2

wavetable_none = [0]*samples
wavetable_sin = [vhalf + vhalf*math.sin(x*2*math.pi/samples) for x in range(samples)]
wavetable_square = [0 if x < samples/2 else vmax for x in range(samples)]
wavetable_tri = [vmax*2*x/samples if x < samples/2 else (vmax - (vmax*2*(x-samples/2))/samples) for x in range(samples)]
wavetable_saw_up = [x*vmax/samples for x in range(samples)]
wavetable_saw_down = [vmax - x*vmax/samples for x in range(samples)]

width = 16
with open('wavetables.h', 'w') as f:
    f.write("uint16_t wavetable_sin[] = {\n    ")
    rows = ["%6d, " * (len(x)) % tuple(x) for x in chunked(wavetable_sin, width)]
    f.write('\n    '.join(rows))
    f.write("\n};\n\n")

    f.write("uint16_t wavetable_square[] = {\n    ")
    rows = ["%6d, " * (len(x)) % tuple(x) for x in chunked(wavetable_square, width)]
    f.write('\n    '.join(rows))
    f.write("\n};\n\n")

    f.write("uint16_t wavetable_tri[] = {\n    ")
    rows = ["%6d, " * (len(x)) % tuple(x) for x in chunked(wavetable_tri, width)]
    f.write('\n    '.join(rows))
    f.write("\n};\n\n")

    f.write("uint16_t wavetable_saw_up[] = {\n    ")
    rows = ["%6d, " * (len(x)) % tuple(x) for x in chunked(wavetable_saw_up, width)]
    f.write('\n    '.join(rows))
    f.write("\n};\n\n")

    f.write("uint16_t wavetable_saw_down[] = {\n    ")
    rows = ["%6d, " * (len(x)) % tuple(x) for x in chunked(wavetable_saw_down, width)]
    f.write('\n    '.join(rows))
    f.write("\n};\n\n")
