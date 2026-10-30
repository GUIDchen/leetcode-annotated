# 题目：1806. 还原排列的最少操作步数（Minimum Number of Operations to Reinitialize a Permutation）
# 思路：元素 0 与 n-1 始终不动，只需跟踪下标 1 的轨迹，按置换规则反复迭代，回到 1 的步数即答案。
# 时间复杂度：O(n)，循环次数不超过 n；空间复杂度：O(1)，只用常数个整型变量。
class Solution:  # LeetCode 约定的题解类
    def reinitializePermutation(self, n: int) -> int:  # n：排列长度，元素取自 0..n-1，其中 0 与 n-1 始终不动
        ans, i = 0, 1  # ans 记录操作次数，i 是数字 1 当前所在的下标
        while 1:  # 无限循环，直到数字 1 回到下标 1 才退出
            ans += 1  # 又执行了一次置换
            if i < n >> 1:  # 注意运算符优先级：>> 高于 <，这里等价于 i < (n >> 1)
                i <<= 1  # 左半段：新下标 = 2 * i
            else:  # 右半段
                i = (i - (n >> 1)) << 1 | 1  # 新下标 = 2 * (i - n/2) + 1，左移后按位或 1 相当于加 1
            if i == 1:  # 数字 1 回到起点，整个排列随之复原
                return ans  # 返回所需的最少操作步数
