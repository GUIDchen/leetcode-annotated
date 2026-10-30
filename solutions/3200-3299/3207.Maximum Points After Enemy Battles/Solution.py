# 题目：3207. 与敌人战斗后的最大分数（Maximum Points After Enemy Battles）
# 思路：总是用最小的敌人能量反复刷分（每击败一次得 1 分），能量不足时再按能量从大到小击败敌人把能量补回来，继续刷分。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(1)，只用了常数个额外变量（原地排序）。
class Solution:  # LeetCode 题解类，固定入口名
    def maximumPoints(self, enemyEnergies: List[int], currentEnergy: int) -> int:  # 返回能获得的最大分数；enemyEnergies 为敌人能量数组，currentEnergy 为初始能量
        enemyEnergies.sort()  # 升序排序，把最小能量放在最前面，作为反复刷分的固定目标
        if currentEnergy < enemyEnergies[0]:  # 如果初始能量连最弱的敌人都打不过
            return 0  # 一分也拿不到，直接返回 0
        ans = 0  # ans 累计总分数
        for i in range(len(enemyEnergies) - 1, -1, -1):  # 从能量最大的敌人开始倒序遍历，每个敌人只被击败一次
            ans += currentEnergy // enemyEnergies[0]  # 每击败一次最弱敌人得 1 分，先把当前能量尽可能多地换成分数
            currentEnergy %= enemyEnergies[0]  # 刷分后剩下的能量已不足以再击败最弱敌人
            currentEnergy += enemyEnergies[i]  # 击败当前这个较强的敌人，把它的能量加回来，供下一轮继续刷分
        return ans  # 返回累计分数
