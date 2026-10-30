# 题目：2211. 统计道路上的碰撞次数（Count Collisions on a Road）
# 思路：去掉左侧连续的 'L' 与右侧连续的 'R'（它们永远不会相遇），中间剩余的车辆除静止车外都会碰撞一次。
# 时间复杂度：O(n)，一次剥离加一次计数；空间复杂度：O(n)，字符串切片产生了新字符串。
class Solution:  # LeetCode 约定的题解类
    def countCollisions(self, directions: str) -> int:  # directions：每辆车用 'L'/'R' 表示朝向，返回碰撞总次数
        s = directions.lstrip("L").rstrip("R")  # 左侧连续的 'L' 与右侧连续的 'R' 永远不会碰撞，先剥掉它们
        return len(s) - s.count("S")  # 剩余车辆都会碰撞一次，扣除本来就静止的 'S' 数量
