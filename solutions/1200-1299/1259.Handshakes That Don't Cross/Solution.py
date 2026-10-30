# 题目：1259. 不相交的握手（Handshakes That Don't Cross）
# 思路：记忆化搜索——固定第一个人与 l+2 号位置的人握手，把圆环拆成两段互相独立的子问题，方案数相乘再累加。
# 时间复杂度：O(n²)，共 n 个状态、每个状态枚举约 n/2 个切分点；空间复杂度：O(n)，dfs 的缓存与递归深度。
class Solution:  # LeetCode 约定的题解类
    def numberOfWays(self, numPeople: int) -> int:  # numPeople 是围成一圈的人数（保证为偶数），返回不相交配对方案数
        @cache  # @cache 装饰器把 dfs 的每个参数值对应的结果缓存起来，实现记忆化
        def dfs(i: int) -> int:  # dfs(i) 表示 i 个人时的方案数（把人按圆环顺序看作首尾相邻的一串）
            if i < 2:  # 不足 2 个人时没有可握手对象，只有「不握」一种方案
                return 1  # 返回空方案作为递推边界
            ans = 0  # 累加器，记录当前 i 的方案总数
            for l in range(0, i, 2):  # 枚举第一个人与谁握手：左边隔着 l 个人，l 必须是偶数（否则左右人数为奇数，无法各自配对）
                r = i - l - 2  # 右边剩下的人数 = 总数 - 左边 l 人 - 握手的这 2 人
                ans += dfs(l) * dfs(r)  # 左右两段互相独立，方案数相乘后累加
                ans %= mod  # 边累加边取模，避免大整数不断膨胀
            return ans  # 返回当前 i 的方案数，@cache 会自动把它存下来

        mod = 10**9 + 7  # mod 在 dfs 定义之后赋值，但 Python 闭包在调用时才解析变量，此处赋值对 dfs 有效
        return dfs(numPeople)  # 从总人数开始求解
