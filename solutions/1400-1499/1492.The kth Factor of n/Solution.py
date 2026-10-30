# 题目：1492. n 的第 k 个因子（The kth Factor of n）
# 思路：从 1 到 n 升序遍历，遇到因子就把 k 减一，k 归零时返回该因子；遍历完仍未归零则返回 -1。
# 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def kthFactor(self, n: int, k: int) -> int:  # 返回 n 的第 k 个因子，不存在时返回 -1
        for i in range(1, n + 1):  # 升序枚举 1..n，保证因子按从小到大被数到
            if n % i == 0:  # 能整除说明 i 是 n 的一个因子
                k -= 1  # 消耗掉一个因子名额
                if k == 0:  # 名额用完，说明 i 正是第 k 个因子
                    return i  # 返回答案
        return -1  # 因子个数不足 k 个
