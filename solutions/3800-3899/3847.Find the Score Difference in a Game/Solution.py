# 3847. 计算比赛分数差 / Find the Score Difference in a Game（中等）
# 核心思路：维护当前得分归属方，遇到奇数得分或每满 6 轮就换发球，按归属累加得分得到分差。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 题解类（LeetCode 约定类名）
    def scoreDifference(self, nums: List[int]) -> int:  # 返回比赛结束时的分数差（A 的得分减 B 的得分）
        ans, k = 0, 1  # ans 累计分数差；k=1 表示 A 得分，-1 表示 B 得分
        for i, x in enumerate(nums):  # 依次处理每一轮得分
            if x % 2:  # 本轮得分为奇数时立刻换发球权
                k *= -1  # 得分归属切换
            if i % 6 == 5:  # 每满 6 轮（索引 5、11、…）也换发球权
                k *= -1  # 得分归属切换
            ans += k * x  # 把本轮得分按归属累加
        return ans  # 返回最终分数差
