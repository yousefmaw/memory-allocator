# memory-allocator
- Inputs:
1. User inputs holes sizes and starting addresses.
2. User inputs number of processes.
3. User inputs processes’ size (Ex: p0 size =100, p1 size = 50… etc).
4. User inputs the method of allocation (first fit or best fit).
- Scenario to be done:
1. Allocate all processes using allocation methodology.
2. De-Allocate a process ( The user choose a process to de-allocate, you should consider its
space as a hole to be used later and add to it any neighboring holes)
- Output:
Your output is the list of holes and allocated memory blocks (starting addresses and sizes) at
each allocation step (Ex: initial state , after P0 allocation, after P1 allocation, after P2 swapped
out P1 and is allocated instead of P1, … etc.)