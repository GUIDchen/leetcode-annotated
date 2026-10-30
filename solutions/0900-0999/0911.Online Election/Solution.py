# 题目：911. 在线选举（Online Election）
# 核心思路：初始化时顺序扫描投票记录，用计数器维护票王（平票取最近得票者），并记录每个时刻结束后的票王；查询时二分定位最后一个 <= t 的时刻。
# 时间复杂度：构造 O(n)、单次查询 O(log n)；空间复杂度：O(n)，需要保存时间数组与每个时刻的票王。
class TopVotedCandidate:  # 题解类：初始化时预处理，q(t) 负责查询

    def __init__(self, persons: List[int], times: List[int]):  # persons[i] 是在 times[i] 时刻投票的人；times 严格递增
        cnt = Counter()  # 计数器：统计每个候选人当前的票数
        self.times = times  # 保存时间数组，查询时二分用
        self.wins = []  # 按时间顺序记录每个时刻结束后的票王
        cur = 0  # 当前票王
        for p in persons:  # 按时间顺序处理每一张选票
            cnt[p] += 1  # 候选人 p 票数加一
            if cnt[cur] <= cnt[p]:  # 用 <= 让平票时也换人，符合「最近获得选票者当选」的规则
                cur = p  # 更新票王
            self.wins.append(cur)  # 把这一时刻之后的票王追加到快照里

    def q(self, t: int) -> int:  # 查询 t 时刻（含之前所有投票）的票王
        i = bisect_right(self.times, t) - 1  # 找第一个大于 t 的位置，减一即最后一个 <= t 的时刻
        return self.wins[i]  # 返回该时刻的票王


# Your TopVotedCandidate object will be instantiated and called as such:
# obj = TopVotedCandidate(persons, times)
# param_1 = obj.q(t)
