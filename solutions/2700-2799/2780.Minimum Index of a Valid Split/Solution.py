# 题目：2780. 合法分割的最小下标（Minimum Index of a Valid Split）
# 思路：若某个分割合法，两段的主导元素必然相同，所以它只能是全局出现次数最多的元素 x；先用 Counter 求出 x 及其总频次，再从前往后枚举分割点，检查两段中 x 是否都严格过半。
# 时间复杂度：O(n)，统计频次加一次线性扫描；空间复杂度：O(n)，Counter 最坏保存 n 个不同元素。
class Solution:  # LeetCode 约定的题解类
    def minimumIndex(self, nums: List[int]) -> int:  # nums 是输入数组
        x, cnt = Counter(nums).most_common(1)[0]  # 取出现次数最多的元素 x 及其总出现次数 cnt
        cur = 0  # 前缀（左段）中主导元素 x 已经出现的次数
        for i, v in enumerate(nums, 1):  # 用 1 起编号的 i 表示左段长度，v 是当前元素
            if v == x:  # 当前元素属于主导元素，左段计数才需要增加
                cur += 1  # 左段中 x 的出现次数加一
                if cur * 2 > i and (cnt - cur) * 2 > len(nums) - i:  # 左段 x 严格过半，且右段剩余的 x 也严格过半
                    return i - 1  # 找到最靠左的合法分割下标，直接返回
        return -1  # 所有分割都不合法，按题意返回 -1
