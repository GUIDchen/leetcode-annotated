# 题目：2844. 生成特殊数字的最少操作（Minimum Operations to Make a Special Number）
# 思路：记忆化 DFS，状态为 (下标 i, 已保留数字模 25 的余数 k)；每位数字可删除或保留，末尾余数为 0 时删除次数最少。
# 时间复杂度：O(n * 25)，共 n*25 个状态；空间复杂度：O(n * 25)，用于缓存递归结果。
class Solution:  # LeetCode 约定的题解类
    def minimumOperations(self, num: str) -> int:  # num：只含数字的字符串，可以删除其中任意一位
        @cache  # 记忆化装饰器：同一个 (i, k) 状态只计算一次
        def dfs(i: int, k: int) -> int:  # dfs 返回「处理到下标 i、当前余数为 k」时的最少删除次数
            if i == n:  # 递归边界：所有数位都处理完了
                return 0 if k == 0 else n  # 余数为 0 说明保留下来的数字是 25 的倍数；否则只能全部删除，代价为 n
            ans = dfs(i + 1, k) + 1  # 方案一：删除第 i 位，删除次数 +1
            ans = min(ans, dfs(i + 1, (k * 10 + int(num[i])) % 25))  # 方案二：保留第 i 位，十进制余数推进后对 25 取模，取两种方案中较小者
            return ans  # 返回当前状态的最优值

        n = len(num)  # 字符串长度（闭包引用，必须在调用 dfs 之前赋值）
        return dfs(0, 0)  # 从下标 0、余数 0 开始搜索
