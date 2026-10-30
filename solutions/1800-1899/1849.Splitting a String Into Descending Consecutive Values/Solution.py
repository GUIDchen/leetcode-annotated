# 题目：1849. 将字符串拆分为递减的连续值（Splitting a String Into Descending Consecutive Values）
# 思路：DFS 枚举切点，首段不限取值，其后每段必须恰好比上一段小 1，且首段不能独占整个串。
# 时间复杂度：O(n^2)，首段 O(n) 种切法、其后切点基本唯一；空间复杂度：O(n)，递归栈深度不超过段数。
class Solution:  # LeetCode 约定的题解类
    def splitString(self, s: str) -> bool:  # s：待拆分的数字字符串
        def dfs(i: int, x: int) -> bool:  # 内部递归函数：i 是当前切分起点，x 是上一段的值（-1 表示还没切过）
            if i >= len(s):  # 已经切到串尾，说明所有字符都被覆盖
                return True  # 找到一种合法拆分
            y = 0  # 当前这一段累加出的数值
            r = len(s) - 1 if x < 0 else len(s)  # 首段要给后面留数字，所以枚举上界减一
            for j in range(i, r):  # 逐位扩展当前这一段的数值
                y = y * 10 + int(s[j])  # 十进制左移一位再加新数字
                if (x < 0 or x - y == 1) and dfs(j + 1, y):  # 首段无约束；否则要求上一段比当前段大 1，并递归处理剩余部分
                    return True  # 剩余部分也能成功，整体即成功
            return False  # 当前起点没有任何可行切法

        return dfs(0, -1)  # 从下标 0 开始切，此时还没有上一段
