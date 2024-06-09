## Prerequisites
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
*  на unordered_set, с запоминанием best_bid и best_ask через указатели, и их корректировкой при изменении содержимого стакана.
*  на обычном set, в таком случае хранить указатели на лучшие уровни не нужно, поскольку контейнер упорядоченный, и к ним есть доступ за константное время.

Как видно, первый вариант оказался где-то в 2 раза производительнее. Так же немного поигрался с std::pmr, выделял сразу на стеке чанк размера 20 * 2 * sizeof(level), но существенной разницы я не заметил, поэтому в конечном варианте убрал.


```
2024-06-09T14:51:50+03:00
Running ./bm/bench
Run on (8 X 603.524 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 1280 KiB (x4)
  L3 Unified 8192 KiB (x1)
Load Average: 0.60, 0.49, 0.31
-------------------------------------------------------------------
Benchmark                         Time             CPU   Iterations
-------------------------------------------------------------------
order_book_unordered_set    9497726 ns      9497304 ns           65
order_book_set             18383649 ns     18382885 ns           39
```

