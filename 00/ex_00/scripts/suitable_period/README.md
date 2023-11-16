
# BENCHMARK

Specify benchmark time in milliseconds to script ./measure.sh





## E.g

    ./measure.sh 1000 

This specifies 1000 milliseconds for the benchmark.


When the benchmark is done running, 2 files are generated. 

    _./archive_st_ and _result_benchmark_st.csv_


## Suitable Period

To execute scripts for the computation of the standard deviation, execute this commands,


   
    module load python
    python ./st_deviation.py XXX

where XXX is the file that contains the result from previous computation.

## E.g 

    python ./st_deviation _result_1500_st.csv_
