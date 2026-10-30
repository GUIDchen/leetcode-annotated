# 题目：2365. 任务调度器 II（Task Scheduler II）
# 思路：贪心按给定顺序安排任务，用哈希表记下每个任务下次最早可执行的天数；天数不够就空转到那一天。
# 时间复杂度：O(n)，每个任务只做一次哈希查询；空间复杂度：O(k)，k 为不同任务种类数。
class Solution:  # LeetCode 约定的题解类
    def taskSchedulerII(self, tasks: List[int], space: int) -> int:  # tasks 是任务序列，space 是同类任务之间的最小间隔
        day = defaultdict(int)  # 哈希表：键是任务类型，值是它下次最早可以执行的天数，缺失时默认为 0
        ans = 0  # 当前已推进到的天数
        for task in tasks:  # 必须按给定顺序处理每个任务
            ans += 1  # 先假设今天就能执行，把天数往后推一天
            ans = max(ans, day[task])  # 若同类任务间隔未满，就空转到允许的最早一天
            day[task] = ans + space + 1  # 记录该任务下次最早可执行的天数：本次执行日 + space + 1
        return ans  # 返回完成所有任务所需的总天数
