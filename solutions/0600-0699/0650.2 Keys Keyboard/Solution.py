# 题目：650. 两个键的键盘（2 Keys Keyboard）
# 思路：自顶向下记忆化搜索。n 若可分解成 i × (n//i)，先造出 n//i 个 A，再做一次 Copy All 与 i-1 次粘贴，代价为 dfs(n//i) + i，对所有因子取最小。
# 时间复杂度：O(n√n)，每个状态枚举到 √n 个候选因子；空间复杂度：O(n)，缓存中最多保存 n 个状态。
class Solution:  # LeetCode 约定的题解类
    def minSteps(self, n: int) -> int:  # n 是目标 A 的个数，返回所需的最少按键次数
        @cache  # 记忆化装饰器：同一参数只真正计算一次
        def dfs(n):  # 返回打印出 n 个 A 所需的最少按键次数
            if n == 1:  # 只有一个 A 时不需要任何操作，这是递归边界
                return 0  # 边界返回 0 次按键
            i, ans = 2, n  # i 从最小因子 2 开始试；ans 以最坏情况「Copy All + 粘贴 n-1 次」为基线
            while i * i <= n:  # 只枚举到 √n，因子成对出现，另一半会由递归覆盖
                if n % i == 0:  # i 是 n 的因子，可把 n 拆成 i 组、每组 n//i 个
                    ans = min(ans, dfs(n // i) + i)  # 先造 n//i 个，再 Copy All 并粘贴 i-1 次
                i += 1  # 继续试下一个候选因子
            return ans  # 返回该状态的最优按键数

        return dfs(n)  # 从目标 n 出发递推得到答案
