# 题目：3032. 统计各位数字都不同的数字个数 II（Count Numbers With Unique Digits II）
# 思路：数位 DP。dfs(pos, mask, limit) 统计填到第 pos 位、已用数字集合为 mask、是否贴着上界的方案数；分别算 [0, a-1] 与 [0, b] 再相减。
# 时间复杂度：O(位数 × 2^10 × 10)，状态数为 pos × mask；空间复杂度：O(位数 × 2^10)，记忆化缓存。
class Solution:  # LeetCode 约定的题解类
    def numberCount(self, a: int, b: int) -> int:  # a、b：闭区间 [a, b] 的左右端点
        @cache  # 记忆化装饰器：同一个状态只计算一次
        def dfs(pos: int, mask: int, limit: bool) -> int:  # 数位 DP：pos 当前位，mask 已用数字集合，limit 是否贴上限
            if pos >= len(num):  # 所有数位都填完了
                return 1 if mask else 0  # mask 非 0 表示填出的是正数，合法；全前导零的 0 不计入
            up = int(num[pos]) if limit else 9  # 当前位可填的最大值：贴上限时受上界该位限制
            ans = 0  # ans：当前状态下的合法方案数
            for i in range(up + 1):  # 枚举当前位可以填的数字
                if mask >> i & 1:  # 该数字此前已经用过
                    continue  # 会造成重复数字，跳过
                nxt = 0 if mask == 0 and i == 0 else mask | 1 << i  # 仍是前导零就不记录 0，否则把 i 并入集合
                ans += dfs(pos + 1, nxt, limit and i == up)  # 递归下一位；贴上限且取到上界时下一位仍受限
            return ans  # 返回当前状态的方案数

        num = str(a - 1)  # 上界先取 a-1，用于统计前缀
        x = dfs(0, 0, True)  # x：[0, a-1] 内各位数字互不相同的数字个数
        dfs.cache_clear()  # 上界变了，清空缓存避免脏数据
        num = str(b)  # 上界换成 b
        y = dfs(0, 0, True)  # y：[0, b] 内各位数字互不相同的数字个数
        return y - x  # 两个前缀结果相减，得到 [a, b] 的答案
