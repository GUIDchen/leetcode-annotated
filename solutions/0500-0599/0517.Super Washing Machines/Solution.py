# 题目：517. 超级洗衣机（Super Washing Machines）
# 思路：先判断能否均分；再从左到右扫描，用前缀和表示穿过当前边界的净流量，答案取「前缀和绝对值」与「单台机器盈余」的最大值。
# 时间复杂度：O(n)，一次求和加一次扫描；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findMinMoves(self, machines: List[int]) -> int:  # 返回使各机器衣服数相等所需的最少轮数
        n = len(machines)  # 机器数量
        k, mod = divmod(sum(machines), n)  # divmod 同时得到平均值 k 和余数 mod
        if mod:  # 余数不为 0，说明总数无法平分
            return -1  # 题目约定不可行时返回 -1
        ans = s = 0  # ans 记录答案，s 是前缀和（累计净流量）
        for x in machines:  # 从左到右扫描每台机器
            x -= k  # 转成盈余（正）或缺口（负）
            s += x  # 更新前缀和：左边穿过当前位置的净流量
            ans = max(ans, abs(s), x)  # 三者取最大：已有答案、前缀净流量绝对值、本机盈余
        return ans  # 返回最少轮数
