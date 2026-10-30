# 题目：1055. 形成字符串的最短路径（Shortest Way to Form String）
# 思路：每轮用一整份 source 从下标 0 开始贪心匹配 target；若一整份都没能推进 j，则剩余字符无法匹配，返回 -1。
# 时间复杂度：O(m × n)，最坏每轮扫完 source；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def shortestWay(self, source: str, target: str) -> int:  # source 可重复使用，target 是目标串
        def f(i, j):  # 辅助函数：从 source[i]、target[j] 开始贪心匹配
            while i < m and j < n:  # 两个串都没扫完就继续
                if source[i] == target[j]:  # 当前字符相同，说明 target 的这个字符被满足
                    j += 1  # target 指针后移
                i += 1  # source 指针后移，一个字符只能用一次
            return j  # 返回这一份 source 用完后 target 匹配到的位置

        m, n = len(source), len(target)  # 两个串的长度，供内部函数 f 使用（闭包）
        ans = j = 0  # ans 记份数，j 记 target 当前匹配位置
        while j < n:  # target 还没被完整拼出时循环
            k = f(0, j)  # 用掉一整份新的 source，尝试把 target 往后推进
            if k == j:  # 位置没有前进，说明剩余字符在 source 中不存在
                return -1  # 无解，返回 -1
            j = k  # 更新已匹配位置
            ans += 1  # 消耗的 source 份数加一
        return ans  # 返回最少需要的份数
