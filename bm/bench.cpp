#include "order_book.hpp"
#include "utils.hpp"

#include <benchmark/benchmark.h>

struct data
{
    std::vector<std::pair<std::vector<order_book::bid>, std::vector<order_book::ask>>> values;

    auto begin() const { return values.begin(); }
    auto end() const { return values.end(); }

    data()
    {
        std::ifstream inputFile("../data/huobi_global_depth.log");
        std::string line;

        while (std::getline(inputFile, line))
        {
            auto updateInfo = utils::parse_update(line);
            values.push_back({updateInfo.bids, updateInfo.asks});
        }
    }
};

data g_data;

void order_book_unordered_set(benchmark::State& state)
{
    order_book::OrderBookUnorderedSet orderBook;

    for (auto _ : state)
    {
        for (auto const& [bids, asks] : g_data)
        {
            orderBook.update(bids, asks);
            orderBook.getBestLevels();
        }
    }
}
BENCHMARK(order_book_unordered_set);

void order_book_set(benchmark::State& state)
{
    order_book::OrderBookSet orderBook;

    for (auto _ : state)
    {
        for (auto const& [bids, asks] : g_data)
        {
            orderBook.update(bids, asks);
            orderBook.getBestLevels();
        }
    }
}
BENCHMARK(order_book_set);

BENCHMARK_MAIN();
