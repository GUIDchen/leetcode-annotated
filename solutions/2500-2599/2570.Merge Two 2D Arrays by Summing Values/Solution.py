# 题目：2570. 合并两个二维数组 - 求和法（Merge Two 2D Arrays by Summing Values）
# 思路：用 Counter 按 id 累加两个数组里的 value，再按键（id）升序把 [id, value] 还原成二维数组。
# 时间复杂度：O((n + m) log(n + m))，主要开销是对键排序；空间复杂度：O(n + m)，Counter 存放去重后的 id。
class Solution:  # LeetCode 约定的题解类
    def mergeArrays(  # 两个按 id 升序排列的 [id, value] 数组
        self, nums1: List[List[int]], nums2: List[List[int]]  # 两个待合并的二维数组
    ) -> List[List[int]]:  # 返回按 id 升序、value 已求和的二维数组
        cnt = Counter()  # 计数字典：键是 id，值是所有同 id 项的 value 之和
        for i, v in nums1 + nums2:  # 把两个数组拼起来统一遍历，同时拆出 id 与 value
            cnt[i] += v  # 累加同 id 的 value，自动完成「求和合并」
        return [[i, v] for i, v in sorted(cnt.items())]  # 按 id 升序排序后，把每个键值对还原成 [id, value]
