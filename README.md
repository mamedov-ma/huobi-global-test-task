## Requirements
 * g++ 11.4.0 or above
 * [Google Benchmark](https://github.com/google/benchmark) library installed on your machine


## Building on linux ubuntu

```
cd <project-directory>
mkdir build
cd build
cmake ..
make
```

## run main (in build directory), results will be in data/output.txt
```
./main
```

## run benchmarks (in build directory)
```
./bm/bench
```


## Результаты тестирования
Бенчмарк измеряет, за какое время прогонятся все updates из файла huobi_global_depth.log, все данные были распаршены заранее.

Я сделал две реализации стакана:
*  на std::unordered_set, с хранением двух указателей на best_bid и best_ask, и их корректировкой при изменении содержимого стакана.
*  на std:set, в таком случае хранить указатели на лучшие уровни не нужно, поскольку контейнер упорядоченный, и к ним есть доступ за константное время.
*  на std::array, с хранением двух указателей на best_bid и best_ask, так же как в варианте с std::unordered_set

Как видно, вариант с использованием статического массива оказался самым производительным.


```
2024-06-09T18:24:34+03:00
Running ./bm/bench
Run on (8 X 400 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 1280 KiB (x4)
  L3 Unified 8192 KiB (x1)
Load Average: 0.42, 0.58, 0.59
-------------------------------------------------------------------
Benchmark                         Time             CPU   Iterations
-------------------------------------------------------------------
order_book_unordered_set    9476353 ns      9475517 ns           64
order_book_set             17560801 ns     17560338 ns           40
order_book_array            3182234 ns      3182181 ns          219
```

