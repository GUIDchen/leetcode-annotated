# 题目：2126. 摧毁小行星（Destroying Asteroids）
# 核心思路：贪心——先对小行星按质量升序排序，能吞就吞；当前最小的都吞不下时必然失败。
# 时间复杂度：O(n log n)，排序占主导；空间复杂度：O(n)，Python 的 sort 需要额外空间。
class Solution:  # LeetCode 约定的题解类
    def asteroidsDestroyed(self, mass: int, asteroids: List[int]) -> bool:  # mass：初始质量；asteroids：小行星质量列表；返回能否全部摧毁
        asteroids.sort()  # 原地升序排序：只有先吞小的，质量增长才最快
        for x in asteroids:  # 从小到大依次尝试吞掉每颗小行星
            if mass < x:  # 当前质量不足以吞下这颗小行星
                return False  # 最小的都吞不下，后面更大的更不可能，直接返回 False
            mass += x  # 吞下成功，质量增加这颗小行星的质量
        return True  # 所有小行星都被吞掉，返回 True
