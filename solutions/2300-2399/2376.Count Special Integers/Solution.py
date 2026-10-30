# 题目：2376. 统计特殊整数（Count Special Integers）
# 思路：数位 DP，mask 记录已出现的数字，lead 标记前导零、limit 标记是否贴上界，用 @cache 记忆化无约束状态。
# 时间复杂度：O(位数 × 2^10 × 10)；空间复杂度：O(位数 × 2^10)，即缓存状态数。
class Solution:  # LeetCode 约定的题解类
    def countSpecialNumbers(self, n: int) -> int:  # n 是上界，统计 [1, n] 内各位数字互不相同的整数个数
        @cache  # 记忆化：相同参数的状态只计算一次
        def dfs(i: int, mask: int, lead: bool, limit: bool) -> int:  # i 当前位；mask 已用数字集合；lead 前导零；limit 是否贴上界
            if i >= len(s):  # 所有位都填完了
                return int(lead ^ 1)  # 全是前导零（数字 0）不算，其余各算一个合法整数
            up = int(s[i]) if limit else 9  # 当前位的取值上限：贴上界时取 s[i]，否则 9
            ans = 0  # 累计当前状态下的方案数
            for j in range(up + 1):  # 枚举当前位填入的数字 j
                if mask >> j & 1:  # j 之前已经用过，违反「互不相同」
                    continue
                if lead and j == 0:  # 仍在前导零阶段且继续填 0，等于没使用任何数字
                    ans += dfs(i + 1, mask, True, limit and j == up)  # mask 不变，仍是前导零状态
                else:  # 正式使用数字 j
                    ans += dfs(i + 1, mask | 1 << j, False, limit and j == up)  # 把 j 加入集合并取消前导零
            return ans  # 返回当前状态的方案数

        s = str(n)  # 转成字符串，便于逐位读取上界数字
        return dfs(0, 0, True, True)  # 从最高位、空集合、前导零、贴住上界开始搜索
