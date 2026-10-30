# 题目：2177. 找到和为给定整数的三个连续整数（Find Three Consecutive Integers That Sum to a Given Number）
# 思路：divmod(num, 3) 同时得到中间那个数与余数；余数为 0 时答案为 (x-1, x, x+1)，否则无解。
# 时间复杂度：O(1)；空间复杂度：O(1)，返回长度最多为 3 的列表。
class Solution:  # LeetCode 约定的题解类
    def sumOfThree(self, num: int) -> List[int]:  # num 是目标和；返回三个连续整数组成的列表，不存在则返回空列表
        x, mod = divmod(num, 3)  # divmod 一次求出商 x = num // 3 与余数 mod，省去两次运算
        return [] if mod else [x - 1, x, x + 1]  # 余数为 0 时 x 是中间数，返回 (x-1, x, x+1)；否则返回空列表表示无解
