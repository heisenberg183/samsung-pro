def min_drives(cars, destination):
    p, q = destination
    # Compute Manhattan distances for each car
    distances = [abs(x-p) + abs(y-q) for x, y in cars]
    
    # Check if all distances have the same parity
    parity = [d % 2 for d in distances]
    if len(set(parity)) > 1:
        return -1

    d_max = max(distances)
    print(d_max)
    T = 0
    # Find the smallest T such that:
    # (1) T * (T+1) / 2 >= d_max, and
    # (2) (T * (T+1) / 2 - d_max) is even.
    while True:
        T += 1
        total_moves = T * (T + 1) // 2
        if total_moves >= d_max and (total_moves - d_max) % 2 == 0:
            return T

# Example use:
print(min_drives([(2, 3), (-4, 1)], (1, 1)))  # Output: 5
print(min_drives([(0, 1), (0, 2)], (0, 0)))     # Output: -1
