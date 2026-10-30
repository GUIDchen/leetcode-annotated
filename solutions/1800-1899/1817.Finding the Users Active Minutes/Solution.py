# 题目：1817. 查找用户活跃分钟数（Finding the Users Active Minutes）
# 思路：用字典把每个用户的活跃分钟收集成集合，集合大小就是该用户的 UAM，再按 UAM 统计人数。
# 时间复杂度：O(n)，每条日志只插入一次；空间复杂度：O(n)，保存所有 (用户, 分钟) 的去重结果。
class Solution:  # LeetCode 约定的题解类
    def findingUsersActiveMinutes(self, logs: List[List[int]], k: int) -> List[int]:  # logs：{用户ID, 分钟} 列表；k：UAM 上限
        d = defaultdict(set)  # 默认字典：键是用户 ID，值是该用户活跃分钟的集合（自动去重）
        for i, t in logs:  # 逐条解包日志：i 是用户 ID，t 是活跃分钟
            d[i].add(t)  # 把分钟加入该用户的集合，重复的自动忽略
        ans = [0] * k  # 答案数组，ans[j] 表示 UAM 恰好为 j+1 的用户数
        for ts in d.values():  # 遍历每个用户的分钟集合
            ans[len(ts) - 1] += 1  # 集合大小即 UAM，UAM 为 L 的用户计入下标 L-1
        return ans  # 返回按 UAM 分组的人数
