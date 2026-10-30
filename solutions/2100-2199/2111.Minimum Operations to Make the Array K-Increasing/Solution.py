# 题目：2111. 使数组 K 递增的最少操作次数（Minimum Operations to Make the Array K-Increasing）
# 思路：下标模 k 相同的元素互不影响，各自成一条子链；每条子链保留「最长非降子序列」不动，其余改成合适值即可。
# 时间复杂度：O(n log n)，每条子链二分维护 LIS；空间复杂度：O(n)，贪心数组 t 存候选结尾。
class Solution:# LeetCode 约定的题解类
    def kIncreasing(self, arr: List[int], k: int) -> int:# arr：原数组；k：步长；返回最少操作次数
        def lis(arr):# 内部函数：求最长非降子序列长度，并换算成需要修改的元素个数
            t = []# t 是贪心数组，t[len-1] 表示长度为 len 的非降子序列的最小结尾
            for x in arr:# 依次把每个元素 x 作为新的候选结尾
                idx = bisect_right(t, x)# 二分找第一个大于 x 的位置（right 允许相等，对应「非降」）
                if idx == len(t):# 没有更大的结尾，x 可以直接延长子序列
                    t.append(x)# 追加到尾部，LIS 长度加一
                else:# 否则可以把该位置的结尾改小
                    t[idx] = x# 用更小的 x 替换，给后续元素留出更大空间
            return len(arr) - len(t)# 子链长度减去 LIS 长度，就是最少修改次数

        return sum(lis(arr[i::k]) for i in range(k))# 把数组按步长 k 切成 k 条子链，各自求最少修改次数后求和
