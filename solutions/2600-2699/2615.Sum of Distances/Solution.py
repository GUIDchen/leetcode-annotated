# 题目：2615. 等值距离和（Sum of Distances）
# 思路：按值分组记录下标（天然升序），组内用前缀贡献 left 与后缀贡献 right 递推：向右移动一格时，左侧元素贡献增加 gap，右侧元素贡献减少 gap。
# 时间复杂度：O(n)，每个下标只在所属组里被访问两次；空间复杂度：O(n)，字典保存全部分组下标。
class Solution:  # LeetCode 约定的题解类
    def distance(self, nums: List[int]) -> List[int]:  # nums 是输入数组；返回每个下标到同值下标距离之和
        d = defaultdict(list)  # 值 -> 该值出现的下标列表（按遍历顺序天然升序）
        for i, x in enumerate(nums):  # 同时取得下标与元素值
            d[x].append(i)  # 把下标追加到对应值的列表末尾
        ans = [0] * len(nums)  # 答案数组，Python 整数不会溢出让处理更省心
        for idx in d.values():  # 每个值的下标列表独立处理
            left, right = 0, sum(idx) - len(idx) * idx[0]  # left 从 0 开始；right 初值为 sum(idx) - m*idx[0]，即 idx[0] 的右侧距离和
            for i in range(len(idx)):  # 依次求该组每个下标的答案
                ans[idx[i]] = left + right  # 左右贡献相加即为该下标的总距离和
                if i + 1 < len(idx):  # 还有下一个同值下标，需要把贡献迁移过去
                    left += (idx[i + 1] - idx[i]) * (i + 1)  # 左侧 i+1 个元素各被拉远 gap
                    right -= (idx[i + 1] - idx[i]) * (len(idx) - i - 1)  # 右侧剩余元素各被拉近 gap
        return ans  # 结果按原下标存放，直接返回
