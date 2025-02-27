
"""
given array: arr
take the min and max of the array
then divide the difference by 10,
that will be the interval used for every bucket,
with starting point as min, and ending point as max of bucket

loop through the array and add each element to the respective bucket;
then linearly call counting sort on every bucket

"""

"""
fractional knapsack: (running through pseudocode)
collecting all price, weight, price/weight - in 3 tuple
sort the tuple by max-least
create a current_weight
create a current_total

start the loop:
for every value in the tuple:
    if current_weight + that_weight <= max_weight:
        current_weight += that_weight
        current_total += that_total
    else:
        remaining_weight = max_weight - current_weight
        total += remaining_weight*price[that_item]

return total_price
"""