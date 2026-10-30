# 题目：2963. 统计好分割方案的数目（Count the Number of Good Partitions）
# 思路：字典记录每个数字最后出现的下标，再按「段尾最远可达位置」切出 k 个极大段，答案就是 2^(k-1) % (10^9+7)。
# 时间复杂度：O(n)，一次推导式加一次扫描，pow 的模幂是 O(log k)；空间复杂度：O(n)，字典存每个数字的最后下标。
class Solution:  # LeetCode 约定的题解类
    def numberOfGoodPartitions(self, nums: List[int]) -> int:  # nums 是输入数组，返回好分割方案的数目
        last = {x: i for i, x in enumerate(nums)}  # 字典推导式：一边遍历一边记录每个数字最后出现的下标
        mod = 10**9 + 7  # 模数 10^9+7
        j, k = -1, 0  # j 是当前段必须延伸到的最右下标（-1 表示还没开始）；k 是极大段的个数
        for i, x in enumerate(nums):  # 同时拿到下标 i 和数字 x，扫描出极大段
            j = max(j, last[x])  # 段尾要覆盖 x 的最后出现位置，与历史最远位置取较大值
            k += i == j  # 布尔值参与加法：i 等于段尾说明一个极大段结束，k 加一
        return pow(2, k - 1, mod)  # 内置 pow 支持模运算：k 个极大段之间可切可不切，答案是 2^(k-1) % mod
