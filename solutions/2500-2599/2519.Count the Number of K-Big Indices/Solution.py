# 题目：2519. 统计 K-Big 索引的数量（Count the Number of K-Big Indices）
# 核心思路：两棵树状数组分别维护「左侧已出现」与「右侧剩余」的元素计数；扫描到 i 时先把它从右侧删掉，再判断两侧严格小于 nums[i] 的个数是否都不少于 k。
# 时间复杂度：O(n log n)，每次更新与查询都是 O(log n)；空间复杂度：O(n)，两棵树状数组各占 O(n)。
class BinaryIndexedTree:  # 手写树状数组，支持单点加与前缀和查询
    def __init__(self, n):  # n 是值域上界（本题取数组长度，配合值域 1..n）
        self.n = n  # 记录上界，供 update 与 query 使用
        self.c = [0] * (n + 1)  # c 从下标 1 开始用，所以长度开 n + 1

    def update(self, x, delta):  # update：把下标 x 处的计数增加 delta
        while x <= self.n:  # 沿 lowbit 向上更新所有覆盖 x 的节点
            self.c[x] += delta  # 当前节点的计数累加 delta
            x += x & -x  # x += x & -x，跳到下一个受影响的节点

    def query(self, x):  # query：返回前缀 [1, x] 的元素个数
        s = 0  # s 累积前缀和
        while x:  # 沿 lowbit 向下回退，直到 x 归零
            s += self.c[x]  # 累加当前节点保存的区间和
            x -= x & -x  # x -= x & -x，跳到前一个前缀块
        return s  # 返回前缀和，即不大于 x 的元素个数


class Solution:  # LeetCode 约定的题解类
    def kBigIndices(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：两侧都要求的严格小于的元素个数
        n = len(nums)  # 数组长度，同时作为树状数组的值域上界
        tree1 = BinaryIndexedTree(n)  # tree1 维护左侧已出现元素的计数
        tree2 = BinaryIndexedTree(n)  # tree2 维护右侧尚未处理元素的计数
        for v in nums:  # 初始时把所有元素都计入右侧
            tree2.update(v, 1)  # 每个值出现一次，计数加一
        ans = 0  # ans 记录满足条件的下标个数
        for v in nums:  # 从左到右依次处理每个元素
            tree2.update(v, -1)  # 当前元素即将被判定，先从右侧集合里移除它
            ans += tree1.query(v - 1) >= k and tree2.query(v - 1) >= k  # 两侧严格小于它的元素都不少于 k 时条件成立，布尔值累加即为计数
            tree1.update(v, 1)  # 判定完成后加入左侧集合，供后面的下标使用
        return ans  # 返回 K-Big 索引的总数
