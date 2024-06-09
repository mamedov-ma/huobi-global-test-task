#include "order_book.hpp"

namespace order_book
{

void OrderBookUnorderedSet::update(std::vector<bid> const& bids, std::vector<ask> const& asks)
{
    for (bid const& level : bids)
    {
        level.price == 0.0 ? deleteLevel(level) : addOrModifyLevel(level);
    }

    for (ask const& level : asks)
    {
        level.price == 0.0 ? deleteLevel(level) : addOrModifyLevel(level);
    }
}

template <ALevel LEVEL>
void OrderBookUnorderedSet::addOrModifyLevel(LEVEL const& level) // maybe look for std::expected, as failure indicator
{
    if constexpr (std::is_same_v<std::remove_cvref_t<LEVEL>, bid>)
    {
        if (auto it = m_bids.find(level); it != m_bids.end())
        {
            deleteLevel(level);
            addOrModifyLevel(level);
        }
        else
        {
            auto [itBid, _] = m_bids.emplace(level);
            if (bestBid.price < level.price) { bestBid = *itBid; }
        }
    }
    else if constexpr (std::is_same_v<std::remove_cvref_t<LEVEL>, ask>)
    {
        if (auto it = m_asks.find(level); it != m_asks.end())
        {
            deleteLevel(level);
            addOrModifyLevel(level);
        }
        else
        {
            auto [itAsk, _] = m_asks.emplace(level);
            if (bestAsk.price > level.price) { bestAsk = *itAsk; }
        }
    }
}

template <ALevel LEVEL>
void OrderBookUnorderedSet::deleteLevel(LEVEL const& level)
{
    if constexpr (std::is_same_v<std::remove_cvref_t<LEVEL>, bid>)
    {
        if (bestBid.price != level.price)
        {
            m_bids.erase(level);
        }
        else
        {
            m_bids.erase(level);

            bestBid = *m_bids.begin();
            for (auto it = m_bids.begin(); it != m_bids.end(); ++it)
            {
                if (bestBid.price < it->price) { bestBid = *it; }
            }
        }
    }
    else if constexpr (std::is_same_v<std::remove_cvref_t<LEVEL>, ask>)
    {
        if (bestAsk.price != level.price)
        {
            m_asks.erase(level);
        }
        else
        {
            m_asks.erase(level);

            bestAsk = *m_asks.begin();
            for (auto it = m_asks.begin(); it != m_asks.end(); ++it)
            {
                if (bestAsk.price > it->price) { bestAsk = *it; }
            }
        }
    }
}

void OrderBookSet::update(std::vector<bid> const& bids, std::vector<ask> const& asks)
{
    for (bid const& level : bids)
    {
        level.price == 0.0 ? deleteLevel(level) : addOrModifyLevel(level);
    }

    for (ask const& level : asks)
    {
        level.price == 0.0 ? deleteLevel(level) : addOrModifyLevel(level);
    }
}

template <ALevel LEVEL>
void OrderBookSet::addOrModifyLevel(LEVEL const& level)
{
    if constexpr (std::is_same_v<std::remove_cvref_t<LEVEL>, bid>)
    {
        if (auto it = m_bids.find(level); it != m_bids.end())
        {
            deleteLevel(level);
            addOrModifyLevel(level);
        }
        else
        {
            m_bids.emplace(level);
        }
    }
    else if constexpr (std::is_same_v<std::remove_cvref_t<LEVEL>, ask>)
    {
        if (auto it = m_asks.find(level); it != m_asks.end())
        {
            deleteLevel(level);
            addOrModifyLevel(level);
        }
        else
        {
            m_asks.emplace(level);
        }
    }
}

template <ALevel LEVEL>
void OrderBookSet::deleteLevel(LEVEL const& level)
{
    if constexpr (std::is_same_v<std::remove_cvref_t<LEVEL>, bid>)
    {
        m_bids.erase(level);
    }
    else if constexpr (std::is_same_v<std::remove_cvref_t<LEVEL>, ask>)
    {
        m_asks.erase(level);
    }
}

} // namespace order_book
