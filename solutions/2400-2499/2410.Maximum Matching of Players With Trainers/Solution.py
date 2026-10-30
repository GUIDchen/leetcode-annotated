# 题目：2410. 运动员和训练师的最大匹配数（Maximum Matching of Players With Trainers）
# 思路：双方都升序排序后用双指针贪心，给每个运动员分配当前能力够用的最弱训练师。
# 时间复杂度：O(m log m + n log n)（排序主导）；空间复杂度：O(1)（不计排序内部开销）。
class Solution:  # LeetCode 约定的题解类
    def matchPlayersAndTrainers(self, players: List[int], trainers: List[int]) -> int:  # players 是运动员能力，trainers 是训练师能力
        players.sort()  # 运动员能力原地升序排序
        trainers.sort()  # 训练师能力原地升序排序
        j, n = 0, len(trainers)  # j 是训练师指针，n 是训练师人数
        for i, p in enumerate(players):  # 按能力从小到大依次处理每个运动员
            while j < n and trainers[j] < p:  # 训练师能力不足就跳过，找第一个能带 p 的人
                j += 1  # 指针后移到更强的训练师
            if j == n:  # 训练师用完了，剩余运动员都无法匹配
                return i  # 已匹配 i 对，直接返回
            j += 1  # 匹配成功，训练师指针后移，避免重复使用同一个人
        return len(players)  # 所有运动员都匹配成功，返回总人数
