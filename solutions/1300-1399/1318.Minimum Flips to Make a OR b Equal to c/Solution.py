# 题目：1318. 或运算的最小翻转次数（Minimum Flips to Make a OR b Equal to c）
# 思路：逐位独立考虑：c 的该位为 0 时 a、b 该位必须全为 0；为 1 时 a、b 至少一个为 1，缺则翻一次。
# 时间复杂度：O(32)，常数位宽；空间复杂度：O(1)，只用若干标量。
class Solution:  # LeetCode 约定的题解类
    def minFlips(self, a: int, b: int, c: int) -> int:  # 统计最少翻转位数，使 a | b == c
        ans = 0  # 记录累计的翻转次数
        for i in range(32):  # 逐位从低到高检查 32 位（int 的位宽）
            x, y, z = a >> i & 1, b >> i & 1, c >> i & 1  # 分别取出 a、b、c 在第 i 位的比特值
            ans += x + y if z == 0 else int(x == 0 and y == 0)  # c 该位为 0：a、b 中为 1 的位都要翻；为 1：a、b 都为 0 时翻一次即可
        return ans  # 返回最少翻转次数
