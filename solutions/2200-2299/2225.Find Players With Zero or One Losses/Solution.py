# 题目：2225. 找出输掉零场或一场比赛的玩家（Find Players With Zero or One Losses）
# 思路：用 Counter 统计每位玩家输掉的场次，首次作为赢家出现时补记 0 负；最后按输场次 0 或 1 分装两列表并按键排序。
# 时间复杂度：O(m + n log n)，m 为比赛场数、n 为玩家数，耗时在计数与排序；空间复杂度：O(n)，只保存玩家与其输场次。
class Solution:  # LeetCode 约定的题解类
    def findWinners(self, matches: List[List[int]]) -> List[List[int]]:  # matches 中每场比赛为 [赢家, 输家]
        cnt = Counter()  # 计数器：键是玩家编号，值是该玩家输掉的场次
        for winner, loser in matches:  # 逐场比赛解包出赢家与输家
            if winner not in cnt:  # 赢家此前可能从未出现，需要显式建立记录
                cnt[winner] = 0  # 首次出现的赢家输场次记为 0
            cnt[loser] += 1  # 输家输场次加一；Counter 对缺失键按 0 处理，无需预先初始化
        ans = [[], []]  # 结果固定两块：ans[0] 存 0 负玩家，ans[1] 存 1 负玩家
        for x, v in sorted(cnt.items()):  # 按玩家编号升序遍历，x 为编号、v 为输场次
            if v < 2:  # 只保留输 0 场或 1 场的玩家
                ans[v].append(x)  # 以输场次 v 作下标直接归入对应列表
        return ans  # 返回两个升序列表
