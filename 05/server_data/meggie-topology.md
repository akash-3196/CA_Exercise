• Note down the cache sizes (in kB) for each level
• What maximum grid width dx (in cells) can utilize cache blocking according to the
layer condition
• What maximum jacobi grid size (in cells) can utilize cache effects of each leve

Fill the following table

**L1: 32 kiB **>**(**3**⋅**d**x**+**1**)⋅**8** + C

**L2: 256 kiB **>**(**3**⋅**d**x**+**1**)⋅**8** + C

**L3: 25 MiB **>**(**3**⋅**d**x**+**1**)⋅**8** + C


|    | Cache Size | dx      | Max Jacobi Grid size |
| -- | ---------- | ------- | -------------------- |
| L1 | 32 kiB     | 1365    | 1365 x dy            |
| L2 | 256 kiB    | 10922   | 10922 x dy           |
| L3 | 25 MiB     | 1092266 | 1092266 x dy         |
