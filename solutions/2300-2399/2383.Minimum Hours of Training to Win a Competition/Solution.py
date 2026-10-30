# 题目：2383. 赢得比赛需要的最少训练时长（Minimum Hours of Training to Win a Competition）
# 思路：按顺序模拟比赛，精力只减不增、经验只增不减；赛前不满足「严格大于」时补到恰好压线，补足时长累加即为答案。
# 时间复杂度：O(n)，n 为比赛场数；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minNumberOfHours(  # x：初始精力；y：初始经验；energy/experience：每场的消耗与经验要求
        self, x: int, y: int, energy: List[int], experience: List[int]  # 参数列表的第二行，仅为了排版换行
    ) -> int:  # 返回赢得全部比赛所需的最少训练小时数
        ans = 0  # 需要的最少训练小时数
        for dx, dy in zip(energy, experience):  # 同时取出本场消耗的精力与获得的经验
            if x <= dx:  # 精力必须严格大于消耗才能获胜，否则赛前要补到 dx + 1
                ans += dx + 1 - x  # 累加补足的时长
                x = dx + 1  # 补完后精力恰好比消耗多 1，刚好压线能赢
            if y <= dy:  # 经验同理，也必须严格大于本场要求
                ans += dy + 1 - y  # 累加补足的时长
                y = dy + 1  # 补完后经验恰好压线
            x -= dx  # 打完这场，精力被消耗 dx
            y += dy  # 打完这场，经验增加 dy
        return ans  # 赢下所有场次所需的最少训练时长
