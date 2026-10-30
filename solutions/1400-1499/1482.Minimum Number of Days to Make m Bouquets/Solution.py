# 题目：1482. 制作 m 束花所需的最少天数（Minimum Number of Days to Make m Bouquets）
# 核心思路：可行性关于天数单调，因此对 [0, max(bloomDay)+1] 二分，用贪心统计能扎成多少束相邻的 k 朵花。
# 时间复杂度：O(n log max(bloomDay))；空间复杂度：O(1)，只用到常数额外变量。
class Solution:  # LeetCode 约定的题解类
    def minDays(self, bloomDay: List[int], m: int, k: int) -> int:  # bloomDay 为各花开花日，m 为所需束数，k 为每束所需相邻花朵数
        def check(days: int) -> int:  # 内层判定函数：等到第 days 天能否凑出 m 束
            cnt = cur = 0  # cnt 为已扎花束数，cur 为当前连续开花朵数
            for x in bloomDay:  # 顺序扫描每朵花的开花时间
                cur = cur + 1 if x <= days else 0  # 盛开则连续长度 +1，未开则连续段清零
                if cur == k:  # 连续 k 朵刚好扎成一束
                    cnt += 1  # 花束数加一
                    cur = 0  # 这 k 朵已用掉，连续计数归零
            return cnt >= m  # 能凑够 m 束即说明 days 天可行
        # 天数越大越容易成功，故布尔序列单调，可以对答案二分
        mx = max(bloomDay)  # 最晚开花日，决定二分上界
        l = bisect_left(range(mx + 2), True, key=check)  # 在单调布尔序列上二分，返回第一个 check 为真的天数
        return -1 if l > mx else l  # 落到 mx+1 表示无解，返回 -1
