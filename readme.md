This is my attempt at a simple multithreaded matrix multiplication program in C++. 
The program will generate two matrices of the given sizes (matrices are filled with random doubles in range [-100, 100]) and multiply them twice: once sequentially, and one in parallel, and compare the times.

USAGE: ./matmult \<nrows1\> \<ncols1\> \<nrows2\> \<ncols2\> \<nthreads\>
Where nrows1 is the number of rows of the first matrix, etc.
Note: ncols1 and nrows2 must be the same for multiplication to work!

I want to avoid using any generative AI, so every instance I use it will be documented below:
2-28: Used Gemini to debug this compile error: error: attempt to use a deleted function. 
The problem was that I was passing non-copiable arguments into my threads, which doesn't work, as threads need to copy data into local thread storage. The solution was to wrap my non-copiable arguments in std::ref() and std::cref() to enable passing by reference.