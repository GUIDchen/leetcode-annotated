# 3476. Maximize Profit from Task Assignment / 3476. 最大化任务分配的利润
# 核心思路：按技能分组用有序列表存利润，每个工人取本技能最高利润任务，最后再补一个剩余任务中的最大利润。
# 复杂度：时间 O((n + m) log m)，空间 O(m)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def maxProfit(self, workers: List[int], tasks: List[List[int]]) -> int:  # 返回最多能获得的利润总和
        d = defaultdict(SortedList)  # 每个技能对应一个有序利润列表
        for skill, profit in tasks:  # 遍历所有任务
            d[skill].add(profit)  # 按技能把利润加入有序列表
        ans = 0  # 累计利润
        for skill in workers:  # 依次为每个工人分配任务
            if not d[skill]:  # 该工人技能没有可分配的任务
                continue  # 跳过该工人
            ans += d[skill].pop()  # 弹出并累加本技能的最高利润
        mx = 0  # 记录剩余任务中的最大利润
        for ls in d.values():  # 遍历所有技能的有序列表
            if ls:  # 列表非空才可能取到利润
                mx = max(mx, ls[-1])  # ls[-1] 即该技能剩余任务的最大利润
        ans += mx  # 最多再额外完成一个剩余任务
        return ans  # 返回最大利润总和
