from bisect import bisect_right

def find_optimal_D_optimized(a, b):
    # Sort the input arrays to enable binary search.
    a.sort()
    b.sort()
    n, m = len(a), len(b)
    
    # Candidate threshold values: only check values present in a or b.
    candidates = sorted(set(a + b))
    
    best_diff = float('-inf')
    best_D = None

    for D in candidates:
        # Use binary search to count elements <= D.
        count_a = bisect_right(a, D)
        count_b = bisect_right(b, D)
        
        # Compute scores for a and b:
        # For each array, score = (# elements > D)*2 + (# elements <= D)*1.
        # This simplifies to: score = 2*(total elements) - (# elements <= D).
        score_a = 2 * n - count_a
        score_b = 2 * m - count_b
        
        diff = score_a - score_b
        
        if diff > best_diff:
            best_diff = diff
            best_D = D
            
    return best_D, best_diff


a = [90, 3, 78, 23, 66]
b = [19, 839, 21, 81, 34]
optimal_D, max_difference = find_optimal_D_optimized(a, b)
print("Optimal D:", optimal_D)
print("Max Difference (A_score - B_score):", max_difference)
