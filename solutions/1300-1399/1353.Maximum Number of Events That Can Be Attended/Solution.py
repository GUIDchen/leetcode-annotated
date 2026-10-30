# 题目：1353. 最多可以参加的会议数目（Maximum Number of Events That Can Be Attended）
# 思路：会议按开始日装进字典桶，从最早开始日逐天推进；用小顶堆维护当前可参加会议的结束日，每天贪心参加结束最早的一场，过期会议弹掉。
# 时间复杂度：O(n log n + D log n)，D 为日期跨度、n 为会议数；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def maxEvents(self, events: List[List[int]]) -> int:  # events[i] = [开始日, 结束日]，每天最多参加一场
        g = defaultdict(list)  # 哈希桶：键是开始日，值是该天开始的所有会议的结束日
        l, r = inf, 0  # l 维护最早开始日、r 维护最晚结束日，用于确定扫描区间
        for s, e in events:  # 第一遍遍历：分桶并求出区间端点
            g[s].append(e)  # 把这场会议挂到它的开始日上
            l = min(l, s)  # 维护最早开始日
            r = max(r, e)  # 维护最晚结束日
        pq = []  # 小顶堆（列表即堆结构）：存放可参加会议的结束日
        ans = 0  # 已参加的会议数量
        for s in range(l, r + 1):  # 从最早开始日逐天推进到最晚结束日
            while pq and pq[0] < s:  # 堆顶会议在昨天或更早结束，已彻底过期
                heappop(pq)  # 丢弃这场不可能再参加的会议
            for e in g[s]:  # 把今天新开始的会议放进候选池
                heappush(pq, e)  # 结束日入堆
            if pq:  # 候选池非空，今天可以参加一场
                heappop(pq)  # 贪心：参加结束最早的那一场
                ans += 1  # 参加数加一
        return ans  # 返回最多能参加的会议数目
