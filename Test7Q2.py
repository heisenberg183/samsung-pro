MOD = 10**9 + 7

def count_certificates(A_str, target_sum):
    # Convert A to string and determine the number of digits
    N = len(A_str)
    
    # Quick check: if target_sum is more than the maximum possible digit sum,
    # there is no valid certificate.
    if target_sum > 9 * N:
        return 0

    # Using memoization to cache results for state (pos, current_sum, tight)
    from functools import lru_cache
    @lru_cache(maxsize=None)
    def dp(pos, current_sum, tight):
        # Base condition: when we have processed all digits,
        # check if the current sum is equal to the target sum.
        if pos == N:
            return 1 if current_sum == target_sum else 0

        result = 0
        # Determine the limit for current digit based on tight constraint
        limit = int(A_str[pos]) if tight else 9
        for d in range(0, limit + 1):
            new_sum = current_sum + d
            # Skip this branch if new_sum is already above target_sum.
            if new_sum > target_sum:
                continue
            # If tight was True and the digit chosen equals the limit,
            # then the next position remains under tight constraint.
            new_tight = tight and (d == limit)
            result = (result + dp(pos + 1, new_sum, new_tight)) % MOD
        return result

    # The dp function counts numbers including those with leading zeros.
    # Since target_sum >= 1, the number 0 (which is all zeros) is not counted.
    return dp(0, 0, True)

# Example usage:
if __name__ == "__main__":
    # Test examples provided:
    examples = [
        ("101", 3),   # Expected answer: 4
        ("172", 3),   # Expected answer: 7
        ("50", 4),    # Expected answer: 5
        ("999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", 980)  # Expected answer: 0
    ]
    
    for A, S in examples:
        result = count_certificates(A, S)
        print(f"A = {A}, S = {S}, Answer: {result}")
