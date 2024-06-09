#include "order_book.hpp"
#include "utils.hpp"

int main()
{
    std::ifstream inputFile("../data/huobi_global_depth.log");
    std::ofstream outputFile{"../data/output.txt"};

    order_book::OrderBookUnorderedSet orderBook;
    std::string line;

    while (std::getline(inputFile, line))
    {
        auto updateInfo = utils::parse_update(line);
        orderBook.update(updateInfo.bids, updateInfo.asks);
        auto const& [bestBid, bestAsk] = orderBook.getBestLevels();
        utils::dump_best_orders(bestBid, bestAsk, updateInfo.eventTime, outputFile);
    }

    return 0;
}
