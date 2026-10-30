# 题目：413. 等差数列划分（Arithmetic Slices）
# 思路：成对遍历相邻元素，公差不变则等差段延长并累加当前长度，公差变化就重置计数。
# 时间复杂度：O(n)，只扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfArithmeticSlices(self, nums: List[int]) -> int:  # nums 是整数数组，返回等差连续子数组（长度 ≥ 3）的个数
        ans = cnt = 0  # ans 累计答案，cnt 为以当前相邻对结尾的等差段长度
        d = 3000  # 当前公差，用题面范围外的 3000 当哨兵
        for a, b in pairwise(nums):  # 成对遍历相邻元素（pairwise 由判题环境提供，无需 import）
            if b - a == d:  # 公差未变，等差段继续延长
                cnt += 1  # 段长计数加一
            else:  # 公差变化，等差段断开
                d = b - a  # 更新当前公差
                cnt = 0  # 重新开始计数
            ans += cnt  # 以该位置结尾的新增等差子数组正好 cnt 个
        return ans  # 返回等差子数组总数
