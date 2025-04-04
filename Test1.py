# NOT OPTIMAL

from collections import defaultdict



def count_points_on_path(n, m, x_points, y_points, path_x, path_y):
    # Hash maps to store horizontal and vertical segments
    # Assume we have read:
    # n: number of points, m: number of turning points
    # points: a list of tuples [(x1, y1), (x2, y2), ..., (xn, yn)]
    # path_points: a list of turning points [(p1_x, p1_y), ..., (pm_x, pm_y)]
    points = [(x_points[i], y_points[i]) for i in range(n)]
    path_points = [(path_x[i], path_y[i]) for i in range(m)] 

    # Dictionaries for segments
    horizontals = {}  # key: y-coordinate, value: list of intervals [ (x_start, x_end) ]
    verticals = {}    # key: x-coordinate, value: list of intervals [ (y_start, y_end) ]

    # Build segments from turning points
    for i in range(m - 1):
        x1, y1 = path_points[i]
        x2, y2 = path_points[i+1]
        if y1 == y2:
            y = y1
            low = min(x1, x2)
            high = max(x1, x2)
            if y not in horizontals:
                horizontals[y] = []
            horizontals[y].append((low, high))
        elif x1 == x2:
            x = x1
            low = min(y1, y2)
            high = max(y1, y2)
            if x not in verticals:
                verticals[x] = []
            verticals[x].append((low, high))

    # Merge overlapping intervals in both horizontals and verticals
    def merge_intervals(intervals):
        intervals.sort(key=lambda x: x[0])
        merged = []
        for interval in intervals:
            if not merged or merged[-1][1] < interval[0]:
                merged.append(interval)
            else:
                merged[-1] = (merged[-1][0], max(merged[-1][1], interval[1]))
        return merged

    for y in horizontals:
        horizontals[y] = merge_intervals(horizontals[y])

    for x in verticals:
        verticals[x] = merge_intervals(verticals[x])
        

    # Count points on the path
    on_path = 0
    for x, y in points:
        found = False
        if y in horizontals:
            for (low, high) in horizontals[y]:
                if low <= x <= high:
                    found = True
                    break
        # Check vertical segments at x if not already found
        if not found and x in verticals:
            for (low, high) in verticals[x]:
                if low <= y <= high:
                    found = True
                    break
        if found:
            on_path += 1

    print(on_path)
    return on_path


# Example Input
n, m = 3, 3
x_points = [1, 2, 3]
y_points = [3, 5, 5]
path_x = [1, 1, 2]
path_y = [1, 5, 5]

# Output the result
result = count_points_on_path(n, m, x_points, y_points, path_x, path_y)
print("Points on path:", result)
