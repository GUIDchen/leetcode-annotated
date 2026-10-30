# 题目：1563. 石子游戏 V（Stone Game V）
# 思路：区间 DP + 记忆化。枚举分割点，两段和不等时 Bob 丢掉较大的一段，只能在小的一段继续递归；相等时两种选择都尝试。前缀和 O(1) 求段和，上界剪枝减少枚举。
# 时间复杂度：O(n^3)，区间 O(n^2) × 分割点 O(n)，剪枝后更快；空间复杂度：O(n^2)，缓存与前缀和。
def max(a: int, b: int) -> int:  # 自己实现的 max：本题源码没有引入内置 max，这里显式定义同名版本
    return a if a > b else b  # 返回较大的那个参数


class Solution:  # LeetCode 约定的题解类
    def stoneGameV(self, stoneValue: List[int]) -> int:  # stoneValue：每堆石子的价值
        @cache  # 记忆化装饰器：同一个区间只计算一次
        def dfs(i: int, j: int) -> int:  # 返回区间 [i, j] 能取得的最大分数
            if i >= j:  # 只剩一段或空区间，无法继续分割
                return 0  # 得分为 0
            ans = l = 0  # ans 当前最优；l 左段和
            r = s[j + 1] - s[i]  # r 右段和，初始为整段之和
            for k in range(i, j):  # 枚举分割点 k：左段 [i, k]，右段 [k+1, j]
                l += stoneValue[k]  # 左段和加入 stoneValue[k]
                r -= stoneValue[k]  # 右段和减去 stoneValue[k]
                if l < r:  # 左段更小，Bob 丢掉右段，只能在左段继续游戏
                    if ans >= l * 2:  # 剪枝：左段贡献上限是 l + l，已不可能超过 ans
                        continue  # 跳过这个分割点
                    ans = max(ans, l + dfs(i, k))  # 取左段和加上左段内部最优
                elif l > r:  # 右段更小，只能在右段继续游戏
                    if ans >= r * 2:  # 剪枝：右段贡献上限是 r + r
                        break  # 之后 r 只会更小，直接跳出循环
                    ans = max(ans, r + dfs(k + 1, j))  # 取右段和加上右段内部最优
                else:  # 两段和相等，Bob 可以任选一段
                    ans = max(ans, max(l + dfs(i, k), r + dfs(k + 1, j)))  # 两种选法都尝试，取较大者
            return ans  # 返回区间最优值

        s = list(accumulate(stoneValue, initial=0))  # 前缀和：s[i] 表示前 i 堆石子之和
        return dfs(0, len(stoneValue) - 1)  # 从整个区间开始求解
