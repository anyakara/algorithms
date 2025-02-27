import math
import counting_sort

def bucket_sort(arr: list[int]):
    minval = min(arr)
    maxval = max(arr)
    diff = (maxval-minval)/len(arr)

    buckets = [[] for _ in range(len(arr)+1)]

    for i in range(len(arr)):
        index = math.floor((arr[i]-minval)/diff)
        buckets[index].append(arr[i])
    for b in buckets:
        b = counting_sort.run_counting_sort(b)

    main_list = []
    for i in range(10):
        main_list.extend(buckets[i])
    return main_list
