# 题目：2554. 从一个范围内选择最多整数 I（Maximum Number of Integers to Choose From a Range I）
# 思路：禁用值转成集合，从 1 到 n 顺序贪心选取（小的数更省总和），一旦加上当前数就超过 maxSum 便停止。
# 时间复杂度：O(bannedSize + n)，建集合加一次线性枚举，成员查询 O(1)；空间复杂度：O(bannedSize)，集合存放禁用值。
class Solution:  # LeetCode 约定的题解类
    def maxCount(self, banned: List[int], n: int, maxSum: int) -> int:  # banned 是禁用数字，n 是范围上界，maxSum 是所选数字之和的上限
        ans = s = 0  # ans 是已选个数，s 是已选数字的总和
        ban = set(banned)  # 转成集合，去重并支持 O(1) 的成员查询
        for i in range(1, n + 1):  # 从小到大枚举每个可选的整数
            if s + i > maxSum:  # 加上 i 就会超过总和上限
                break  # 因为 i 递增，后面的只会更大，直接结束
            if i not in ban:  # 当前数字没有被禁用
                ans += 1  # 选取个数加一
                s += i  # 累加到已选总和
        return ans  # 返回最多能选的整数个数
