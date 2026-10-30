# 题目：1823. 找出游戏的获胜者（Find the Winner of the Circular Game）
# 核心思路：约瑟夫环递推，n 人时的获胜者位置等于「n-1 人时的位置 + k」对 n 取模，递归到只剩 1 人，再处理 0-based 编号为 0 时对应编号 n。
# 时间复杂度：O(n)，递归 n 层；空间复杂度：O(n)，递归栈开销。
class Solution:  # LeetCode 约定的题解类
    def findTheWinner(self, n: int, k: int) -> int:  # 返回约瑟夫环中最后剩下的编号（1-based）
        if n == 1:  # 递归终止条件：只剩一个人
            return 1  # 剩下的人就是获胜者，编号为 1
        ans = (k + self.findTheWinner(n - 1, k)) % n  # 先求 n-1 人的答案，加 k 后对 n 取模得到 0-based 位置
        return n if ans == 0 else ans  # 位置为 0 时真实编号是 n，否则位置本身即为编号
