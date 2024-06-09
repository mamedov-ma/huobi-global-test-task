#pragma once

#include "json.h"
#include "order_book.hpp"

#include <fstream>

namespace utils
{

order_book::update_info parse_update(std::string line)
{
    using json = nlohmann::json;

    json jsonInfo = json::parse(line.substr(62));

    order_book::update_info updateInfo;
    updateInfo.eventTime = jsonInfo["event_time"];

    for (auto it = jsonInfo["asks"].begin(); it != jsonInfo["asks"].end(); ++it)
    {
        updateInfo.asks.push_back({it->begin()->template get<order_book::level::price_t>(), (it->begin() + 1)->template get<order_book::level::amount_t>()});
    }

    for (auto it = jsonInfo["bids"].begin(); it != jsonInfo["bids"].end(); ++it)
    {
        updateInfo.bids.push_back({it->begin()->template get<order_book::level::price_t>(), (it->begin() + 1)->template get<order_book::level::amount_t>()});
    }

    return updateInfo;
}

void dump_best_orders(order_book::bid const& bestBid, order_book::ask const& bestAsk, std::size_t eventTime, std::ofstream& outputFile)
{
    outputFile.precision(16);
    outputFile << "{" << eventTime << "} {" << bestBid.price << "} {" << bestBid.amount << "} {" << bestAsk.price << "} {" << bestAsk.amount << "}\n";
}

} // namespace utils
