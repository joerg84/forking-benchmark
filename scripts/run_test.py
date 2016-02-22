#!/usr/bin/python
import subprocess
import time

numberForks = 1
ResSetMB = 300
percentageWritten = 100

with open('output_forked.dat', 'a+') as output_f:
    for percentage in xrange(0,100,10):
        p = subprocess.check_call(['../bin/Forking-Benchmark', str(numberForks), str(ResSetMB), str(percentage)],
                         stdout=output_f,
                         stderr=output_f)

numberForks = 0
with open('output_nonforked.dat', 'a+') as output_f:
    for percentage in xrange(0,100,10):
        p = subprocess.check_call(['../bin/Forking-Benchmark', str(numberForks), str(ResSetMB), str(percentage)],
                             stdout=output_f,
                             stderr=output_f)





