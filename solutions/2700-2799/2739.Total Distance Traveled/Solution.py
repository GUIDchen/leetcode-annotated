# 题目：2739. 总行驶距离（Total Distance Traveled）
# 思路：每消耗 1 升油行驶 10 公里；累计消耗满 5 升且备用油未用完时补 1 升回主油箱，循环到主油箱为空为止。
# 时间复杂度：O(mainTank + additionalTank)，每轮消耗 1 升；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def distanceTraveled(self, mainTank: int, additionalTank: int) -> int:  # mainTank 是主油箱升数，additionalTank 是备用油可补充的升数
        ans = cur = 0  # ans 记录总公里数，cur 记录已消耗的升数，两者同时初始化为 0
        while mainTank:  # 主油箱里还有油（非 0 即为真）就继续行驶
            cur += 1  # 又消耗 1 升油
            ans += 10  # 每消耗 1 升可行驶 10 公里
            mainTank -= 1  # 主油箱减少 1 升
            if cur % 5 == 0 and additionalTank:  # 每消耗满 5 升且备用油还有剩余，就补 1 升
                additionalTank -= 1  # 备用油减少 1 升
                mainTank += 1  # 补来的 1 升加回主油箱，使循环继续
        return ans  # 主油箱耗尽，返回总行驶距离
