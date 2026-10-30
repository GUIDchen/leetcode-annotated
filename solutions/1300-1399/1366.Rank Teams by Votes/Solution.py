# 题目：1366. 通过投票对团队排名（Rank Teams by Votes）
# 思路：统计每个队伍在每个名次上的票数，以「票数向量」为主键降序、字母序号为辅键升序排序。
# 时间复杂度：O(V·m + 26·m + 26·m log26)；空间复杂度：O(26·m)，计数表 cnt。
class Solution:  # LeetCode 约定的题解类
    def rankTeams(self, votes: List[str]) -> str:  # votes 是选票列表，返回按规则排好序的队伍字母串
        m = len(votes[0])  # m 是队伍（也是名次）数量
        cnt = defaultdict(lambda: [0] * m)  # cnt[c][k] 表示队伍 c 得到第 k 名的票数，默认全 0
        for vote in votes:  # 逐张选票统计
            for i, c in enumerate(vote):  # 逐个名次统计
                cnt[c][i] += 1  # 该名次上该队伍的票数加一
        return "".join(sorted(cnt, key=lambda c: (cnt[c], -ord(c)), reverse=True))  # 键为「票数向量, -字母序号」并逆序排列：票数多者在前，票数相同则字母小者在前
