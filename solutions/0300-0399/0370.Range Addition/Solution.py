# 题目：370. 区间加法（Range Addition）
# 思路：差分数组。区间加 c 等价于 d[l] += c 且 d[r+1] -= c，最后对差分数组做前缀和（accumulate）就得到每个位置的最终值。
# 时间复杂度：O(n + m)，m 为更新次数；空间复杂度：O(n)，差分数组也可复用为结果。
class Solution:  # LeetCode 约定的题解类
    def getModifiedArray(self, length: int, updates: List[List[int]]) -> List[int]:  # length 是数组长度，updates 每项为 [左端点, 右端点, 增量]
        d = [0] * length  # 差分数组，初始全 0，最后经前缀和变成结果
        for l, r, c in updates:  # 逐条处理区间更新，就地解包三个分量
            d[l] += c  # 区间起点加 c，使 l 及其后所有位置都受影响
            if r + 1 < length:  # 只有右端点后面还有元素才需要抵消，避免越界
                d[r + 1] -= c  # 终点之后减 c，把影响范围截断在 r
        return list(accumulate(d))  # accumulate 返回惰性迭代器，list 把它具体化成结果数组
