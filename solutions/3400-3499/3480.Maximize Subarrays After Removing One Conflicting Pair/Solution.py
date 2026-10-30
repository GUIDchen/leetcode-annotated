# 3480. 删除一个冲突对后最大子数组数目（Maximize Subarrays After Removing One Conflicting Pair）
# 核心思路：从右往左枚举左端点 a，维护最小的两个冲突右端点 b1、b2，每个 a 贡献 b1 - a 个合法子数组；删除能解开 b1 那个冲突对可额外获得 b2 - b1 个，取最大增量加到答案上。
# 复杂度：时间 O(n + m)，空间 O(n)
class Solution:  # 解题类
    def maxSubarrays(self, n: int, conflictingPairs: List[List[int]]) -> int:  # 返回删除至多一个冲突对后合法子数组的最大数目
        g = [[] for _ in range(n + 1)]  # g[a] 存放所有左端点为 a 的冲突对的右端点
        for a, b in conflictingPairs:  # 把每个冲突对按左端点归类
            if a > b:  # 保证 a 是较小的端点
                a, b = b, a  # 交换成 a < b
            g[a].append(b)  # 记录到左端点 a 的列表中
        cnt = [0] * (n + 2)  # cnt[b1] 记录删掉造成界 b1 的冲突对时能新增的子数组数
        ans = add = 0  # ans 为不删除时的子数组数，add 为删除一个冲突对的最大增量
        b1 = b2 = n + 1  # b1、b2 分别为当前最小的两个冲突右端点
        for a in range(n, 0, -1):  # 从右往左枚举左端点 a
            for b in g[a]:  # 遍历所有以 a 为左端点的冲突右端点
                if b < b1:  # 出现了更小的冲突右端点
                    b2, b1 = b1, b  # 原来的最小变成第二小，同时更新最小
                elif b < b2:  # 否则若介于最小与第二小之间
                    b2 = b  # 更新第二小右端点
            ans += b1 - a  # 左端点 a 处的合法子数组数为 b1 - a
            cnt[b1] += b2 - b1  # 若删掉造成 b1 的那个冲突对，可额外获得 b2 - b1 个
            add = max(add, cnt[b1])  # 维护所有可删除冲突对带来的最大增量
        ans += add  # 把最优的那次删除带来的增量加到答案上
        return ans  # 返回最大子数组数目
