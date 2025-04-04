class Tile:
    def __init__(self, width, height):
        self.width = width
        self.height = height

def feasible(D, tiles, K):
    for i in range(len(tiles)):
        count = 0
        baseW = tiles[i].width
        baseH = tiles[i].height
        for j in range(len(tiles)):
            if (tiles[j].width >= baseW and tiles[j].width <= baseW + D and
                tiles[j].height >= baseH and tiles[j].height <= baseH + D):
                count += 1
        if count >= K:
            return True
    return False

def find_minimum_diff(tiles, K):
    min_width = min(tile.width for tile in tiles)
    max_width = max(tile.width for tile in tiles)
    min_height = min(tile.height for tile in tiles)
    max_height = max(tile.height for tile in tiles)

    low = 0
    high = max(max_width - min_width, max_height - min_height)

    while low < high:
        mid = (low + high) // 2
        if feasible(mid, tiles, K):
            high = mid
        else:
            low = mid + 1

    return low

# Test cases for the tile selection problem
def test_tile_selection():
    # Test case 1: Simple case
    tiles = [Tile(1, 1), Tile(2, 2), Tile(3, 3), Tile(4, 4)]
    K = 2
    result = find_minimum_diff(tiles, K)
    print("Test Case 1 Result:", result)

    # Test case 2: Larger range
    tiles = [Tile(1, 1), Tile(10, 10), Tile(20, 20), Tile(30, 30), Tile(40, 40)]
    K = 3
    result = find_minimum_diff(tiles, K)
    print("Test Case 2 Result:", result)

    # Test case 3: All tiles in a small area
    tiles = [Tile(1, 1), Tile(2, 2), Tile(1, 2), Tile(2, 1)]
    K = 4
    result = find_minimum_diff(tiles, K)
    print("Test Case 3 Result:", result)

    # Test case 4: Single tile selection
    tiles = [Tile(5, 5), Tile(10, 10), Tile(15, 15)]
    K = 1
    result = find_minimum_diff(tiles, K)
    print("Test Case 4 Result:", result)

if __name__ == "__main__":
    test_tile_selection()
