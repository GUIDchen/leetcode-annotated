# 题目：2251. 花期内花的数目（Number of Flowers in Full Bloom）
# 思路：分别取出所有开花时间与凋谢时间并排序；对每个人，正在开花数 = 开花时间 ≤ 当天的个数 − 凋谢时间 < 当天的个数。
# 时间复杂度：O((n + m) log n)，n 为花数、m 为人数；空间复杂度：O(n)，两个排序后的时间数组。
class Solution:  # LeetCode 约定的题解类
    def fullBloomFlowers(  # 求每个人到达时正在开花的数量
        self, flowers: List[List[int]], people: List[int]  # flowers 每项为 [开花时间, 凋谢时间]，people 是到达时间列表
    ) -> List[int]:  # 返回与 people 顺序一致的答案
        start, end = sorted(a for a, _ in flowers), sorted(b for _, b in flowers)  # start：升序的开花时间；end：升序的凋谢时间（同时生成两个列表再一起赋值）
        return [bisect_right(start, p) - bisect_left(end, p) for p in people]  # bisect_right 统计开花时间 ≤ p 的数量，bisect_left 统计凋谢时间 < p 的数量，两者相减即当天仍在开的花数
