# Test - 1
# You are given a path on an infinite 2d lattice. The path consists of line segments parallel to either the x or y axis.Example : (1, 1) to (1, 3) to (6, 3) to (6, 6). Also there is a set of points given . You have to find how many of the given points lie on the path.
# Input 
# n,m
# There were n numbers that denoted x coordinates of n points
# There were n numbers again which denoted y coordinates of those n points
# Now there are two more arrays of size m , one consisting of x coordinates and other y coordinates correspondingly
# These points are the turning points in a path.
# Examples.
# Say i went from 1, 1 to 1, 5 to 2, 5 so the given arrays will be
# 1, 1, 2
# 1, 5, 5
# In the given path , we have to find how many of the given n points lie.

from collections import defaultdict

def count_points_on_path(n, m, x_points, y_points, path_x, path_y):
    # Hash maps to store horizontal and vertical segments
    horizontal_segments = defaultdict(list)
    vertical_segments = defaultdict(list)
    
    # Build the segments from the path
    for i in range(m - 1):
        x1, y1 = path_x[i], path_y[i]
        x2, y2 = path_x[i + 1], path_y[i + 1]
        
        if y1 == y2:  # Horizontal segment
            min_x, max_x = min(x1, x2), max(x1, x2)
            horizontal_segments[y1].append((min_x, max_x))
        
        if x1 == x2:  # Vertical segment
            min_y, max_y = min(y1, y2), max(y1, y2)
            vertical_segments[x1].append((min_y, max_y))
    
    # Function to check if a value lies in any range
    def is_in_ranges(value, ranges):
        for r_start, r_end in ranges:
            if r_start <= value <= r_end:
                return True
        return False
    
    # Check each point against the path
    count = 0
    for i in range(n):
        px, py = x_points[i], y_points[i]
        
        # Check horizontal segments
        if py in horizontal_segments:
            if is_in_ranges(px, horizontal_segments[py]):
                count += 1
                continue  # No need to check further
        
        # Check vertical segments
        if px in vertical_segments:
            if is_in_ranges(py, vertical_segments[px]):
                count += 1
    
    return count

# Example Input
n, m = 3, 3
x_points = [1, 2, 3]
y_points = [3, 5, 5]
path_x = [1, 1, 2]
path_y = [1, 5, 5]

# Output the result
result = count_points_on_path(n, m, x_points, y_points, path_x, path_y)
print("Points on path:", result)
