# ECF with MPI

ECF is a C++ framework intended for application of any type of evolutionary computation. *The Symbolic Regression program has been specifically modified to run with MPI so that it can perform efficiently in supercomputers. 

Info about the original library is available at: http://ecf.zemris.fer.hr/

## Documentation

Documentation of the original library is available at https://ecf.readthedocs.io/

## Installation

Detailed instructions on how to build ECF on Windows or Unix/Linux are covered at https://ecf.readthedocs.io/install.html or on project web page. The provided 'INSTALL' file deals only with generic installation issues with  GNU automake tools.

## Running Symbolic Regression with MPI

1. Install and build ECF as instructed in their documentation.
2. Navigate to the Symoblic Regression program directory, located in ```ECF/examples/GPSymbReg```
3. Edit the flags of the provided ```Makefile```.

   - If an installation folder was specified, edit the ```-I``` and ```-L``` flags accordingly (consult the documentation for details).
   - If libary was compiled in the default folder (```/usr/local/lib```), remove the ```-I``` and ```-L``` flags.
5. Compile with the ```Makefile```
6. Run with the command: ```mpirun -n {number of nodes} ./symbreg parameters.txt```

If the linker cannot find the library, you will have to add the installation library directory to LD_LIBRARY_PATH, e.g. ```export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH```
