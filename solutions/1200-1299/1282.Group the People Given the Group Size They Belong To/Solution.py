# 题目：1282. 用户分组（Group the People Given the Group Size They Belong To）
# 思路：按「组大小」把下标分桶，再用列表推导式按桶大小把每个桶切成若干组，正好满足每组人数等于组大小。
# 时间复杂度：O(n)，每个下标只入桶、出桶各一次；空间复杂度：O(n)，桶与答案合计保存 n 个下标。
class Solution:  # LeetCode 约定的题解类
    def groupThePeople(self, groupSizes: List[int]) -> List[List[int]]:  # groupSizes[i] 是第 i 个人希望所在组的人数
        g = defaultdict(list)  # 默认字典：键是组大小，值是想进入该大小组的人的下标列表
        for i, v in enumerate(groupSizes):  # 遍历每个人，i 是下标，v 是期望的组大小
            g[v].append(i)  # 按下标 i 的期望组大小投进对应桶
        return [v[j : j + i] for i, v in g.items() for j in range(0, len(v), i)]  # 每个桶按大小 i 切片成组；桶为空时 range 为空
