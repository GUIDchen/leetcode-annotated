# 题目：2121. 相同元素的间隔之和（Intervals Between Identical Elements）
# 核心思路：按值分组记录下标，组内用前缀和递推：中心右移 delta 时左侧各加 delta、右侧各减 delta。
# 时间复杂度：O(n)，每个下标只被访问常数次；空间复杂度：O(n)，分组字典与答案数组。
class Solution:  # LeetCode 约定的题解类
    def getDistances(self, arr: List[int]) -> List[int]:  # arr：输入数组
        d = defaultdict(list)  # 值 → 该值出现的下标列表（按遍历顺序天然升序）
        n = len(arr)  # 数组长度
        for i, v in enumerate(arr):  # 同时取出下标 i 与元素值 v
            d[v].append(i)  # 把下标追加到该值对应的分组里
        ans = [0] * n  # 答案数组，长度与输入相同，先全部置 0
        for v in d.values():  # 逐组处理，v 是某种值的升序下标列表
            m = len(v)  # 该值出现的次数
            val = sum(v) - v[0] * m  # 下标总和减去 m 倍首下标，即以 v[0] 为中心的距离和
            for i, p in enumerate(v):  # 按组内位置递推每个下标的答案
                delta = v[i] - v[i - 1] if i >= 1 else 0  # 与上一个同值下标的间距，i 为 0 时取 0
                val += i * delta - (m - i) * delta  # 中心右移 delta：左侧 i 个各加 delta，右侧 m-i 个各减 delta
                ans[p] = val  # 把结果写回该下标在原数组中的位置
        return ans  # 返回所有位置的间隔之和
