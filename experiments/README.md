# Matrix Multiplication Experiments

This is a directory storing the source code of the experiments of the seminar course Modern Trends in High Performance Computing. The analysis of experiments is conducted in the seminar paper. 

## Author Information

* Name: Jinwen Pan
* E-Mail: [jinwen.pan@tum.de](mailto:jinwen.pan@tum.de)

## Application Information
Matrix multiplication is a fundamental operation in numerical algorithms, and its computational efficiency has garnered considerable attention from the academic community. Some experiments aimed at optimizing the computational efficiency of matrix multiplication are conducted and
analyzed based on four different aspects with particular emphasis placed on precision considerations to
elucidate the potential benefits of employing mixed precision algorithms.

## Testsystem

Host/Clustername: SuperMUC-NG

Cluster Info URL: <https://doku.lrz.de/supermuc-ng-10745965.html>

=====  Processor  =====

Processor name: Intel(R) Xeon(R) Platinum 8174 @ 2.70GHz (Turbo 3.90Ghz) 

Nodes: 6480

Packages(sockets): 2

Cores: 48

Processors(CPUs): 96

Cores per package: 24

Threads per core: 2

=====  Memory  =====

L1 per core: 32KB

L2 per core: 1MB

L3 per socket: 33MB

DRAM per node: 96GB

## Software Environment

=====  Operating System  ===== 

SUSE Linux Enterprise Server 15 SP3

=====  Compilers  =====

intel-oneapi-compilers/2021.4.0

=====  Libraries  =====

papi/6.0.0.1-intel21 (hardware counters for performance monitoring)

=====  Others  =====

intel-oneapi-vtune/2021.7.1 (detailed performance analysis software)


## How to build the program

Clone or download this directory to the system you want to run on and execute the following command in the appropriate folder:  

```
$ module load intel-oneapi-compilers/2021.4.0
$ module load papi/6.0.0.1-intel21
$ module load intel-oneapi-vtune/2021.7.1
$ make
```

**Note:** All tests are built and run on SuperMUC-NG with the software mentioned above. If you couldn't access it, please refer to the official sites of the respective software. Or the similar compilers and libraries on your system would work most of the time. The build-run process and results would be similar. 

**Note:** There are some options available in the makefile we can select:
- `-std=c++11`: Utilizes c++11 standard mainly for the timing function with high resolution
- `-O0, -O1, -O2, -O3`: General compiler optimization levels 
- `-Ofast`: This option will not strictly follow language standards and will specifically optimize for some languages in addition to enabling all `-O3` optimization options
- `-no-vec`: No vectorization is utilized
- `-xSSE4.2`: Enables SSE vectorization 
- `-xCORE-AVX2`: Enables AVX2 vectorization (Intel only)
- `-xCORE-AVX512` and `-qopt-zmm-usage=high`: Forces usage of AVX512 instructions (Intel only)
- `-ipo`: Enables interprocedural optimization
- `-fno-alias`: Not assume memory aliasing

## How to run the program
The program is run by a provided script on the cluster as follows:

```
$ sbatch job.scp
```
But you could also run it on your local system with command line input as follows:
```
$ ./matrixMultiplication n precision [block size]
```
where `n` is the size of matrices (for better quantify the problem size, what we have implemented is actually square multiplication, but you could easily modify the program to multiply matrices with arbitrary size), and `precision` is the data type identifier (1 means float, 2 means double, and 3 means long double). `block size` is only needed in the blocking version of `Cache Optimization`. You could also modify the parameters in the execution script according to this.  

This is a general introduction for all versions in the directory. Some extra remarks will be mentioned in the folders respectively. You are welcome to contact me for any problem regarding the program. 

## Have Fun!
