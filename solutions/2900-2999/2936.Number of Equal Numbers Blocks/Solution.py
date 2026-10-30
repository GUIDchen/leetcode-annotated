# 题目：2936. 包含相等值数字块的数量（Number of Equal Numbers Blocks）
# 思路：从左到右扫描，先看下一项是否与当前值相同；相同就用 bisect_left 二分出该块的末端，块数加一后直接跳到块尾。
# 时间复杂度：O(b log n)，b 为块的个数、n 为数组长度；空间复杂度：O(1)，只用常数个变量。
# Definition for BigArray.
# class BigArray:
#     def at(self, index: long) -> int:
#         pass
#     def size(self) -> long:
#         pass
class Solution(object):  # LeetCode 约定的题解类（题目模板显式继承 object）
    def countBlocks(self, nums: Optional["BigArray"]) -> int:  # nums：只能通过 at/size 随机访问的大数组
        i, n = 0, nums.size()  # i：当前扫描位置；n：数组长度
        ans = 0  # 累计相等值块的个数
        while i < n:  # 只要还没扫到末尾
            ans += 1  # 当前位置必然开启一个新的值块
            x = nums.at(i)  # 读出当前块的值
            if i + 1 < n and nums.at(i + 1) != x:  # 块长只有 1：下一项存在且值与当前不同
                i += 1  # 直接跳到下一块
            else:  # 否则块内还有相同元素，需要用二分定位块尾
                i += bisect_left(range(i, n), True, key=lambda j: nums.at(j) != x)  # bisect_left 返回第一个「值不等于 x」的下标偏移，加上后正好跳到下一块起点
        return ans  # 返回块的总数
