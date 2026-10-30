# 题目：1094. 拼车（Car Pooling）
# 思路：差分数组。对每条行程在起点加上人数、在终点减去人数，再对差分数组求前缀和，得到每个站点车上的实时人数，全部不超过 capacity 才可行。
# 时间复杂度：O(n + M)，n 为行程数、M 为最大终点站；空间复杂度：O(M)，差分数组长度。
class Solution:  # LeetCode 约定的题解类
    def carPooling(self, trips: List[List[int]], capacity: int) -> bool:  # trips 每项是 [人数, 上车点, 下车点]，capacity 为车的容量
        mx = max(e[2] for e in trips)  # 最大的终点站，决定差分数组要开多长
        d = [0] * (mx + 1)  # 差分数组：d[i] 是在站点 i 的净乘车人数变化量
        for x, f, t in trips:  # 逐条行程处理：x 人数，f 上车点，t 下车点
            d[f] += x  # f 站上车，净人数增加 x
            d[t] -= x  # t 站下车，净人数减少 x（注意下车点不再占座）
        return all(s <= capacity for s in accumulate(d))  # accumulate 求前缀和得到每站实时人数，all 要求全程不超过容量
