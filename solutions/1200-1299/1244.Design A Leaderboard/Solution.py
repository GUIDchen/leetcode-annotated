# 题目：1244. 力扣排行榜（Design A Leaderboard）
# 思路：字典存玩家总分，SortedList 存所有分数，加分时先删旧分再插新分，top 直接取有序表末尾 K 个求和。
# 时间复杂度：addScore O(log n)、reset O(log n)、top O(K)；空间复杂度：O(n)，n 为玩家数。
class Leaderboard:  # 排行榜类，支持加分、查询前 K 名总分、重置三种操作
    def __init__(self):  # 构造函数
        self.d = defaultdict(int)  # 玩家编号 → 当前总分，缺省值为 0
        self.rank = SortedList()  # 有序表保存所有玩家分数，便于按排名取前 K 个

    def addScore(self, playerId: int, score: int) -> None:  # 给玩家加分
        if playerId not in self.d:  # 该玩家第一次出现
            self.d[playerId] = score  # 记录他的总分
            self.rank.add(score)  # 同时把分数插入有序表
        else:  # 老玩家：需要把旧分数换掉
            self.rank.remove(self.d[playerId])  # 先从有序表删除旧总分
            self.d[playerId] += score  # 再在字典上累加新分数
            self.rank.add(self.d[playerId])  # 把新总分写回有序表

    def top(self, K: int) -> int:  # 前 K 名玩家的总分之和
        return sum(self.rank[-K:])  # 有序表升序，取末尾 K 个就是最大的 K 个分数

    def reset(self, playerId: int) -> None:  # 重置某个玩家的分数
        self.rank.remove(self.d.pop(playerId))  # pop 取走并删除字典项，同时把该分数从有序表删掉


# Your Leaderboard object will be instantiated and called as such:
# obj = Leaderboard()
# obj.addScore(playerId,score)
# param_2 = obj.top(K)
# obj.reset(playerId)
