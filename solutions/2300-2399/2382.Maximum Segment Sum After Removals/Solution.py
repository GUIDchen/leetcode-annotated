# 题目：2382. 删除操作后的最大子段和（Maximum Segment Sum After Removals）
# 思路：倒着看删除就是逐个「加回」元素，用并查集把相邻的已激活位置合并成连续段，同时维护最大段和。
# 时间复杂度：O(n α(n))，n 为数组长度、并查集每次操作近似 O(1)；空间复杂度：O(n)，父指针与段和数组各占 O(n)。
class Solution:  # LeetCode 约定的题解类
    def maximumSegmentSum(self, nums: List[int], removeQueries: List[int]) -> List[int]:  # nums：原数组；removeQueries：依次删除的下标
        def find(x):  # 并查集查找，带路径压缩
            if p[x] != x:  # 当前节点不是代表元
                p[x] = find(p[x])  # 递归找到代表元并直接挂过去，压缩路径
            return p[x]  # 返回代表元

        def merge(a, b):  # 合并 a、b 所在的两个连续段
            pa, pb = find(a), find(b)  # 先分别取到两段的代表元
            p[pa] = pb  # 把 a 所在段挂到 b 所在段下面
            s[pb] += s[pa]  # 段和累加到新的代表元上

        n = len(nums)  # 数组长度，也是删除操作的次数
        p = list(range(n))  # 父指针数组，初始时每个下标自成一个集合
        s = [0] * n  # 段和数组；0 同时表示该位置还没被加回（用来判断邻居是否已激活）
        ans = [0] * n  # 每次删除后的最大子段和；最后一格留 0，对应删空后的空段
        mx = 0  # 当前所有连续段中的最大段和
        for j in range(n - 1, 0, -1):  # 倒序遍历，第 j 次删除相当于把 removeQueries[j] 加回来
            i = removeQueries[j]  # 本轮要加回的下标
            s[i] = nums[i]  # 激活该位置，先把它看成长度为 1 的独立段
            if i and s[find(i - 1)]:  # 左邻居存在且已激活（段和非 0）
                merge(i, i - 1)  # 和左边的段合并
            if i < n - 1 and s[find(i + 1)]:  # 右邻居存在且已激活
                merge(i, i + 1)  # 和右边的段合并
            mx = max(mx, s[find(i)])  # 用合并后的整段和刷新全局最大值
            ans[j - 1] = mx  # 记录第 j-1 次删除后的答案
        return ans  # 返回每次删除后的最大子段和
