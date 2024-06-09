#pragma once

#include <concepts>
#include <cstdint>
#include <functional>
#include <limits>
#include <set>
#include <unordered_set>
#include <vector>

namespace order_book
{

struct level
{
    using amount_t = double; // arbitrary chosen type
    using price_t = double; // arbitrary chosen type

    level(price_t price, amount_t amount) noexcept
        : price{price}
        , amount{amount}
    {}

    level() = default;

    price_t price{};
    amount_t amount{};
};

struct bid : public level
{
    using level::level;
};

struct ask : public level
{
    using level::level;
};

template <class T>
concept ALevel = std::is_base_of_v<level, T> && std::copyable<T> && std::movable<T>;

struct hash
{
    template <ALevel LEVEL>
    std::size_t operator()(LEVEL const& level) const { return std::hash<level::price_t>{}(level.price); }
};

struct equal_to
{
    template <ALevel LEVEL>
    bool operator()(LEVEL const& lhs, LEVEL const& rhs) const { return std::equal_to<level::price_t>{}(lhs.price, rhs.price); }
};

struct level_comp
{
    template <ALevel LEVEL>
    bool operator()(LEVEL const& lhs, LEVEL const& rhs) const { return std::less<level::price_t>{}(lhs.price, rhs.price); }
};

struct update_info
{
    std::vector<bid> bids;
    std::vector<ask> asks;
    std::size_t eventTime;
};

class OrderBookUnorderedSet
{
public:
    OrderBookUnorderedSet() { bestAsk.price = std::numeric_limits<level::price_t>::max(); }

    void update(std::vector<bid> const& bids, std::vector<ask> const& asks);

    std::pair<bid const&, ask const&> getBestLevels() const noexcept { return {bestBid, bestAsk}; }

private:
    template <ALevel LEVEL>
    void addOrModifyLevel(LEVEL const& level);

    template <ALevel LEVEL>
    void deleteLevel(LEVEL const& level);

    std::unordered_set<bid, hash, equal_to> m_bids;
    std::unordered_set<ask, hash, equal_to> m_asks;
    bid bestBid;
    ask bestAsk;
};

class OrderBookSet
{
public:
    OrderBookSet() {}

    void update(std::vector<bid> const& bids, std::vector<ask> const& asks);

    std::pair<bid const&, ask const&> getBestLevels() const noexcept { return {*m_bids.rbegin(), *m_asks.begin()}; }

private:
    template <ALevel LEVEL>
    void addOrModifyLevel(LEVEL const& level);

    template <ALevel LEVEL>
    void deleteLevel(LEVEL const& level);

    std::set<bid, level_comp> m_bids;
    std::set<ask, level_comp> m_asks;
};

} // namespace order_book
