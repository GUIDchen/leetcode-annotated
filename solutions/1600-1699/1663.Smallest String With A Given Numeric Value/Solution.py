# 题目：1663. 具有给定数值的最小字符串（Smallest String With A Given Numeric Value）
# 思路：所有位置先取 'a'（字典序最小），再从末尾开始尽量改成 'z'，把剩余差值补在最后一个未满的位置。
# 时间复杂度：O(n)，每个位置最多处理一次；空间复杂度：O(n)，用列表存放结果字符。
class Solution:  # LeetCode 约定的题解类
    def getSmallestString(self, n: int, k: int) -> str:  # n 是字符串长度，k 是字符数值（a=1..z=26）之和
        ans = ['a'] * n  # 用列表存 n 个 'a'，后面按下标就地修改
        i, d = n - 1, k - n  # i 从末尾开始倒序填；d = k - n 是还需要补的数值
        while d > 25:  # 只要剩余差值超过 25，当前位就能直接拉满成 'z'
            ans[i] = 'z'  # 把当前位改成 'z'（比 'a' 多 25）
            d -= 25  # 剩余差值减去 25
            i -= 1  # 指针左移，继续处理前一位
        ans[i] = chr(ord(ans[i]) + d)  # 把不足 25 的差值加到当前字符上（ord/chr 做数值与字符的转换）
        return ''.join(ans)  # 拼回字符串返回，保证长度 n、数值和 k、字典序最小
