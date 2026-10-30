# 题目：1533. 找到最大整数的索引（Find the Index of the Large Integer）
# 思路：其余元素都相等，只有最大值不同；把区间三分后比较前两段之和，就能判断最大值在哪一段，不断缩小区间。
# 时间复杂度：O(log n)，每轮区间缩小到约 1/3；空间复杂度：O(1)，只用常数个下标变量。
# """  # 下面几行是题面给出的 ArrayReader 接口说明，判题器提供，无需自己实现
# This is ArrayReader's API interface.
# You should not implement it, or speculate about its implementation
# """
# class ArrayReader(object):
# 	 # Compares the sum of arr[l..r] with the sum of arr[x..y]
# 	 # return 1 if sum(arr[l..r]) > sum(arr[x..y])
# 	 # return 0 if sum(arr[l..r]) == sum(arr[x..y])
# 	 # return -1 if sum(arr[l..r]) < sum(arr[x..y])
#    def compareSub(self, l: int, r: int, x: int, y: int) -> int:
#
# 	 # Returns the length of the array
#    def length(self) -> int:
#


class Solution:  # LeetCode 约定的题解类
    def getIndex(self, reader: 'ArrayReader') -> int:  # reader 是题目给的接口对象，只能用它比较区间和、取长度
        left, right = 0, reader.length() - 1  # 答案一定落在当前区间 [left, right] 中，初始为整个数组
        while left < right:  # 区间不止一个数时继续三分查找
            t1, t2, t3 = (  # 把区间均分为 A=[t1,t2]、B=[t2+1,t3] 两段，剩下部分留作 C 段
                left,
                left + (right - left) // 3,
                left + ((right - left) // 3) * 2 + 1,
            )
            cmp = reader.compareSub(t1, t2, t2 + 1, t3)  # 比较 A、B 两段的和（接口返回 1/0/-1）
            if cmp == 0:  # 两段和相等：最大值既不在 A 也不在 B，只能在剩余的 C 段
                left = t3 + 1  # 把查找区间收缩到 C 段
            elif cmp == 1:  # A 段和更大：最大值在 A 段
                right = t2  # 右边界收到 A 段末尾
            else:  # 否则是 B 段和更大：最大值在 B 段
                left, right = t2 + 1, t3  # 把区间收缩到 B 段
        return left  # 区间只剩一个下标，它就是最大整数的位置
