# 题目：2136. 全部开花的最早一天（Earliest Possible Day of Full Bloom）
# 思路：播种必须串行，总播种时间固定；把生长期长的种子尽量往前排（按 growTime 降序），用贪心交换论证可证最优，逐颗累加播种时间并取 t + gt 的最大值。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n)，排序产生的配对序列。
class Solution:  # LeetCode 约定的题解类
    def earliestFullBloom(self, plantTime: List[int], growTime: List[int]) -> int:  # plantTime：各种子的播种耗时；growTime：各种子的生长期
        ans = t = 0  # ans：全部开花的最早一天；t：当前已累计的播种时间
        for pt, gt in sorted(zip(plantTime, growTime), key=lambda x: -x[1]):  # 按生长期从大到小排序：生长期长的种子先播种
            t += pt  # 累计播种耗时，该种子在时刻 t 播完
            ans = max(ans, t + gt)  # 该种子在 t + gt 开花，用最大值更新答案
        return ans  # 返回全部开花的最早一天
