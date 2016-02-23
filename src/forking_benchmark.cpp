#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <sys/resource.h>
#include <unistd.h>
#include <memory>

using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

  // Check and read parameters.
  if (argc < 5) {
    cerr << "Usage: " << argv[0] << " numberForks memSizeMB overwritePercentage stride" << std::endl;
    return EXIT_FAILURE;
  }

  int numberForks = atoi(argv[1]);
  int memSize =  atoi(argv[2]) * 1024 * 1024;
  double percentageWritten = atoi(argv[3])/100.0;
  int stride = atoi(argv[4]);

  if (percentageWritten > 1.0) {
    cerr << "OverwritePercentage should be less than 100;"<< std::endl;
    return EXIT_FAILURE;
  }

  // Create pipes;
  //TODO enable more pipes to children
  int pipefd[2];
  if (pipe(pipefd) == -1) {
        cerr << "Creating Pipes failed."<< std::endl;
        return EXIT_FAILURE;
  }

  // Generate memory set
  std::unique_ptr<char[]> mem {new char[memSize]};
  memset(mem.get(), 'a', memSize);

  // Get minor pagefaults initialization.
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  long min_pagefaults = usage.ru_minflt;
  //std::cout << "Initial Minor Pagefaults: " << min_pagefaults << std::endl;


  clock_t d1 = clock();

  for (int i = 0; i < numberForks; ++i) {
    pid_t pid = fork();


    if (pid < 0) {
      cerr << "Fork failed."<< std::endl;
      return EXIT_FAILURE;
    }
    // Child process
    if (pid == 0) {
      // Goal: wait for parent signal end then quit.

      // close other pipe
      close(pipefd[1]);

      // Block until parent is done.
      char buf;
      read(pipefd[0], &buf, 1);
      close(pipefd[0]);
      return EXIT_SUCCESS;
    }
    // Parent process
    else {
      // Goal we are touching percentenageWritten memory and then signal child.

      // close other pipe
      close(pipefd[0]);

      int overwriteMem = memSize * percentageWritten;
      assert (overwriteMem <= memSize);

      // Write one page per cache line.
      unsigned totalNumberCacheLines = overwriteMem / stride;
      for (unsigned cacheLine = 0; cacheLine < totalNumberCacheLines; ++cacheLine) {
        unsigned position = cacheLine * stride;
        mem[position] ='b';
      }

      // Signal child process to quit.
      char message {'a'};
      write(pipefd[1], &message, 1);
    }

  }

  // Baseline with no forks.
  if (numberForks == 0) {
    int overwriteMem = memSize * percentageWritten;
    assert (overwriteMem <= memSize);

    unsigned totalNumberCacheLines = overwriteMem / stride;
    for (unsigned cacheLine = 0; cacheLine < totalNumberCacheLines; ++cacheLine) {
        unsigned position = cacheLine * stride;
        mem[position] ='b';
      }
  }

  d1 = clock() - d1;
  double t1 = ((double) d1) / CLOCKS_PER_SEC;

  // Get min_pagefaults after execution.
  getrusage(RUSAGE_SELF, &usage);
  min_pagefaults = usage.ru_minflt - min_pagefaults;
  //std::cout << "Major-pagefaults: " << usage.ru_majflt << " Minor Pagefaults: " << usage.ru_minflt << std::endl;

  // Output in format processable by gnuplot.
  std::cout << std::setprecision(15) << numberForks << " "<< atoi(argv[2]) << " " << percentageWritten << " "
            << t1 << " " << min_pagefaults << " " << stride << " " << mem[0] << " " << mem[memSize-1] << std::endl;

  return EXIT_SUCCESS;
}
