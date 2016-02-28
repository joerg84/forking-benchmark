#!/usr/bin/python
import subprocess
import time

numberForks = 1
ResSetMB = 300
CacheLineSize = 64;
PageSize = 4096;

with open('clone_output_forked_line.dat', 'a+') as output_f:
    for percentage in xrange(0,100,10):
        p = subprocess.check_call(['../bin/Clone-Benchmark', str(numberForks), str(ResSetMB), str(percentage), str(CacheLineSize)],
                         stdout=output_f,
                         stderr=output_f)
with open('clone_output_forked_page.dat', 'a+') as output_f:
    for percentage in xrange(0,100,10):
        p = subprocess.check_call(['../bin/Clone-Benchmark', str(numberForks), str(ResSetMB), str(percentage), str(PageSize)],
                         stdout=output_f,
                         stderr=output_f)


numberForks = 0
with open('clone_output_nonforked_line.dat', 'a+') as output_f:
    for percentage in xrange(0,100,10):
        p = subprocess.check_call(['../bin/Clone-Benchmark', str(numberForks), str(ResSetMB), str(percentage), str(CacheLineSize)],
                             stdout=output_f,
                             stderr=output_f)
with open('clone_output_nonforked_page.dat', 'a+') as output_f:
    for percentage in xrange(0,100,10):
        p = subprocess.check_call(['../bin/Clone-Benchmark', str(numberForks), str(ResSetMB), str(percentage), str(PageSize)],
                             stdout=output_f,
                             stderr=output_f)




