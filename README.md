# Whetstone benchmarking for Multicore CPU

**Whetstone benchmark** is a **synthetic benchmark** for evaluating the performance of computers. It was originally written in Algol 60 in 1972 by Curnow, H.J. and Wichman, B.A (**see paper in docs directory**). Performance is measured in Millions of Whetstone Instructions Per Second (**MWIPS**). It primarily measures the floating-point arithmetic performance.

**Text from wikipedia article on Whetstone (benchmark)** "The workload on the machine was represented as a set of frequencies of execution of the 124 instructions of the Whetstone Code, a set of 42 simple ALGOL 60 statements, which in a suitable combination matched the execution statistics."

**Link to the original paper can be found in the wikipedia article on "Whetstone (benchmark)"**

## System Requirements

The program compiles and runs on both **Windows and Linux OS**.

**Make** tool is required for compilation.

### For Windows OS
1.  **cl compiler** (download the Build Tools for Visual Studio)
2.  **gnuplot**

### For Linux OS
1.  **gcc compiler**
2.  **gnuplot**

## Compiling

1. Open terminal/command prompt (in top level directory) and enter
	> make clean
	
	> make
	
	make will identify the OS and use the right compiler.

## Running

1. Open terminal/command prompt (in top level directory) and enter

	**For Windows OS**
	> bin\benchmark.exe
	
	**For Linux OS**
	> ./bin/benchmark
	
2. See results in results directory.

	**whetstone.jpeg**
	A Graph plotted based on the csv data generated. Higher the MWIPS, the more is the performance.

	**whetstone.csv**
	No. of threads versus MWIPS (benchmark score)

## Results

The original Whetstone benchmark is for single cpu system. By running this benchmark on many threads simultaneously, we can analyse the overall score based on the overall time taken by all threads.

Some Whetstone Benchmark **Detailed Results** are available in **http://www.roylongbottom.org.uk/whetstone%20results.htm**. This can be used for comparision between CPUs.

Some sample results of old CPUs taken from www.roylongbottom.org.uk.

| CPU  |  MWIPS
|---------------------------------|-------------------|
| Athlon XP 2.3 GHz | 1890 |
| Core 2 Duo 1 CP 2.4 GHz | 2151 |
| Phenom II 3 GHz | 2227 |
| Core i7 930 | 2618 |

### Results generated by the program on my PC

![Results](sample/whetstone.jpeg)
