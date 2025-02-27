def run_counting_sort(arr):
    min_val = min(arr)
    max_val = max(arr)

    arr_range = max_val - min_val + 1
    occ = [0] * arr_range

    for val in arr:
        occ[val-min_val] += 1
    
    new_list = list()
    for i in range(arr_range):
        new_list.extend([min_val+i] * occ[i])

    return new_list

defa = [1, 4, 2, 3, 5, 6, 2]
print(run_counting_sort(defa))