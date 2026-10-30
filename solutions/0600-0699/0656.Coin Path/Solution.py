# 题目：656. 成本最小路径（Coin Path）
# 核心思路：从后往前 DP，f[i] = min(f[j] + coins[i])，再正向按 f 值还原字典序最小的路径。
# 时间复杂度：O(n * maxJump)；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def cheapestJump(self, coins: List[int], maxJump: int) -> List[int]:  # coins 是各位置花费（-1 表示不能落脚），maxJump 是单步最大跨度
        if coins[-1] == -1:  # 终点不可落脚时永远到不了
            return []  # 无解返回空路径
        n = len(coins)  # n 是路径上的位置数
        f = [inf] * n  # f[i]：从 i 跳到终点的最小花费（包含 coins[i]），inf 表示不可达
        f[-1] = coins[-1]  # 终点只能落在自己身上，花费就是它的硬币值
        for i in range(n - 2, -1, -1):  # 从倒数第二个位置往前递推
            if coins[i] != -1:  # 只有 i 本身可以落脚时才可能转移
                for j in range(i + 1, min(n, i + maxJump + 1)):  # 枚举落点 j：最多跳 maxJump 格，且不越过末尾
                    if f[i] > f[j] + coins[i]:  # 用「j 之后的后续花费 + coins[i]」能否更优来判断
                        f[i] = f[j] + coins[i]  # 更优就更新 f[i]
        if f[0] == inf:  # 起点 0 无法到达终点
            return []  # 无解返回空路径
        ans = []  # ans 存放最终路径（1 基下标）
        s = f[0]  # s 表示当前还需要的剩余花费
        for i in range(n):  # 正向扫描以便得到字典序最小的路径
            if f[i] == s:  # f[i] == s 说明 i 在最优路径上
                s -= coins[i]  # 扣掉当前硬币花费，剩余目标变成下一跳的 f 值
                ans.append(i + 1)  # 记录 1 基下标
        return ans  # 返回最优路径
