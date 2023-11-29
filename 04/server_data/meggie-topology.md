Cache Topology Extraction

|   | Commands | Description |
| ------------- | ------------- | ------------- |
| 1 | ./bin/benchmark_loop 32 | For L1 32 kB |
| 2 | ./bin/benchmark_loop 256 | For L2 256 kB |
| 3 | ./bin/benchmark_loop 25600 | For L3 25 MB |
| 4 | ./bin/benchmark_loop 25600 | For L3 25 MB |




|    | Cache Size | Jacobi Grid Size | Vector Length
|----------|----------|----------|----------|
| L1 | 32 kB| 43 x 43 | 8192|
| L2| 256 kB | 126 x 126 | 65536  |
| L3 | 25 MB | 25600 x 25600 | 6553600 |




