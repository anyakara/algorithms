import random

def collect_weights_per_val(n, prices, weights) -> list:
    return [(prices[i], weights[i], prices[i]/weights[i]) for i in range(n)]


def fractional_knapsack(n: int, m: int, weights: list[int], prices: list[int]):
    r = collect_weights_per_val(n, prices, weights)# compute ratios
    r.sort(key=lambda x: x[2], reverse=True)

    total_price = 0
    current_weight = 0

    for i in r:
        price = i[0]
        weight = i[1]
        if current_weight + weight <= m:
            current_weight += weight
            total_price += price
        else:
            remaining_weight = m - current_weight
            total_price += remaining_weight * price
    return total_price
