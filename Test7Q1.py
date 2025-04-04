def min_cleaning_cost(garbage, m):
    n = len(garbage)
    memo = {}
    
    def dp(i, d):
        # Base case: no garbage left.
        if i == n:
            return 0
        if (i, d) in memo:
            return memo[(i, d)]
        # Option 1: Continue with the current robot.
        cost_continue = d * garbage[i] + dp(i + 1, d + 1)
        # Option 2: Deploy a new robot at index i.
        cost_new = m + dp(i + 1, 1)
        memo[(i, d)] = min(cost_continue, cost_new)
        return memo[(i, d)]
    
    # At index 0, we must deploy a robot so cleaning starts with delay 0.
    # Since the deployed robot cleans index 0 immediately (cost 0) and then delay becomes 1,
    # the total cost becomes m (deployment cost) plus the cost from index 1.
    return m + dp(1, 1)

# Example usage:
garbage = [3, 2, 5, 1]  # garbage values at each index
m = 4                  # cost to deploy a robot
print("Minimum cost to clean all garbage:", min_cleaning_cost(garbage, m))
