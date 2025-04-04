import sys
from collections import deque

sys.setrecursionlimit(10000)
INF = 10**9

def bfs(start, grid, h, w):
    dist = [[INF] * w for _ in range(h)]
    sr, sc = start
    dq = deque()
    dq.append((sr, sc))
    dist[sr][sc] = 0
    while dq:
        r, c = dq.popleft()
        for dr, dc in ((0, 1), (0, -1), (1, 0), (-1, 0)):
            nr, nc = r + dr, c + dc
            if 0 <= nr < h and 0 <= nc < w:
                if grid[nr][nc] == 1: # Skip if cell is a tree.
                    continue
            if dist[nr][nc] > dist[r][c] + 1:
                dist[nr][nc] = dist[r][c] + 1
                dq.append((nr, nc))
    return dist

def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return

    t = int(data)
    index = 1
    results = []

    for _ in range(t):
        # Read the grid dimensions and cost limit.
        h = int(data[index])
        w = int(data[index + 1])
        C = int(data[index + 2])
        index += 3

        grid = []
        garage = None
        warehouses = []  # List to hold the coordinates (r, c) of each warehouse (cell value 3).
        airports = []    # List to hold the coordinates (r, c) of each airport (cell value 4).

        # Read each cell in the grid.
        for r in range(h):
            row = []
            for c in range(w):
                val = int(data[index])
                index += 1
                row.append(val)
                if val == 2:
                    garage = (r, c)
                elif val == 3:
                    warehouses.append((r, c))
                elif val == 4:
                    airports.append((r, c))
            grid.append(row)

        # Precompute BFS distances from the garage.
        dist_from_garage = bfs(garage, grid, h, w)
        # Compute the shortest distance from the garage to any airport.
        garage_to_airport = INF
        for (r, c) in airports:
            garage_to_airport = min(garage_to_airport, dist_from_garage[r][c])

        n = len(warehouses)
        # dgw[i]: Distance from garage to warehouse i.
        dgw = [INF] * n
        for i, (r, c) in enumerate(warehouses):
            dgw[i] = dist_from_garage[r][c]

        # Precompute BFS distances for each warehouse.
        airport_from_wh = [INF] * n  # Minimum distance from each warehouse to an airport.
        dwh = [[INF] * n for _ in range(n)]  # Pairwise distances between warehouses.
        bfs_wh = []  # Store BFS distances from each warehouse.

        for i, (r, c) in enumerate(warehouses):
            dist_from_wh = bfs((r, c), grid, h, w)
            bfs_wh.append(dist_from_wh)
            # Calculate minimum distance from warehouse i to any airport.
            for (ar, ac) in airports:
                airport_from_wh[i] = min(airport_from_wh[i], dist_from_wh[ar][ac])

        # Compute distances between each pair of warehouses.
        for i in range(n):
            for j in range(n):
                if i == j:
                    continue
                rj, cj = warehouses[j]
                dwh[i][j] = bfs_wh[i][rj][cj]

        # dp[mask][j]: Minimum cost to visit the warehouses in 'mask'
        # and end at warehouse j. 'mask' is a bitmask of visited warehouses.
        dp = [[INF] * n for _ in range(1 << n)]

        # Initialize dp: Moving from garage to warehouse.
        for i in range(n):
            if dgw[i] < INF:  # Check reachability.
                # Truck is empty, so cost per block is 1.
                dp[1 << i][i] = dgw[i]

        best = 0  # Maximum number of goods delivered.

        # Explore every possible subset of warehouses.
        for mask in range(1, 1 << n):
            # Count number of warehouses (goods) delivered so far.
            goods = mask.bit_count()  # For Python 3.10+ use bit_count()
            for j in range(n):
                if (mask & (1 << j)) == 0:
                    continue
                current_cost = dp[mask][j]
                if current_cost >= INF:
                    continue
                # Try finishing the route by going from warehouse j to an airport.
                # Cost of final leg is: distance * (goods + 1) (due to loaded goods).
                final_cost = current_cost + airport_from_wh[j] * (goods + 1)
                if final_cost <= C:
                    best = max(best, goods)
                # Try extending the route by visiting another warehouse k.
                for k in range(n):
                    if mask & (1 << k):
                        continue
                    d = dwh[j][k]
                    if d >= INF:  # Unreachable.
                        continue
                    next_cost = current_cost + d * (goods + 1)
                    new_mask = mask | (1 << k)
                    if next_cost < dp[new_mask][k]:
                        dp[new_mask][k] = next_cost

        # Consider the scenario when the truck goes directly from the garage to the airport.
        if garage_to_airport < INF and garage_to_airport <= C:
            best = max(best, 0)

        results.append(str(best))

    sys.stdout.write("\n".join(results))