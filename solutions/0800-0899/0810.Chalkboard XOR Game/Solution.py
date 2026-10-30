# 题目：810. 黑板异或游戏（Chalkboard XOR Game）
# 思路：长度偶数必胜；长度奇数时，只有全部数字异或和为 0 才必胜。
# 时间复杂度：O(n)，归约求异或和；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def xorGame(self, nums: List[int]) -> bool:  # nums 为黑板上的数字，返回先手是否必胜
        return len(nums) % 2 == 0 or reduce(xor, nums) == 0  # 长度为偶数或整体异或和为 0，先手必胜
