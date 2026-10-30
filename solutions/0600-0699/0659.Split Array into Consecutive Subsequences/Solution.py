# 题目：659. 分割数组为连续子序列（Split Array into Consecutive Subsequences）
# 核心思路：贪心，d[尾部值] 用堆保存各序列长度，每个数优先接到最短的、以 v-1 结尾的序列后。
# 时间复杂度：O(n log n)；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def isPossible(self, nums: List[int]) -> bool:  # nums 已升序，判断能否切成若干长度不少于 3 的连续子序列
        d = defaultdict(list)  # d[尾部值] 是一个小根堆（list），存放以该值结尾的各条序列长度
        for v in nums:  # 按升序依次处理每个数字
            if h := d[v - 1]:  # 海象运算符：取出以 v-1 结尾的长度堆，非空才为真
                heappush(d[v], heappop(h) + 1)  # 弹出最短的序列接上 v，长度加一后放入以 v 结尾的堆
            else:  # 接不上任何已有序列，只能新开一条
                heappush(d[v], 1)  # 新序列长度为 1
        return all(not v or v and v[0] > 2 for v in d.values())  # 空堆视为合格；非空则最短长度必须大于 2
