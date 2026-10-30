# 题目：1871. 跳跃游戏 VII（Jump Game VII）
# 思路：f[i] 表示能否跳到 i，用前缀和把「区间 [i-maxJump, i-minJump] 内是否存在可达点」的查询压缩到 O(1)。
# 时间复杂度：O(n)，每个位置只被推导一次；空间复杂度：O(n)，需要存 f 数组与前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def canReach(self, s: str, minJump: int, maxJump: int) -> bool:  # s：只含 '0'/'1' 的字符串；minJump/maxJump：每次可跳距离的范围
        n = len(s)  # 字符串长度
        pre = [0] * (n + 1)  # 前缀和数组：pre[k] = f[0..k-1] 中可达位置的数量
        pre[1] = 1  # 起点 0 必然可达，所以前 1 个位置的可达计数为 1
        f = [True] + [False] * (n - 1)  # f[i] 表示能否跳到下标 i，起点为 True、其余初始为 False
        for i in range(1, n):  # 按下标从小到大递推每个位置
            if s[i] == "0":  # 只能落在 '0' 上，'1' 位置直接不可达
                l, r = max(0, i - maxJump), i - minJump  # 可起跳的下标区间 [l, r]
                f[i] = l <= r and pre[r + 1] - pre[l] > 0  # 区间内存在可达点则 i 可达
            pre[i + 1] = pre[i] + f[i]  # 把当前位的可达性并入前缀和（bool 参与运算按 0/1 处理）
        return f[-1]  # 终点是否可达就是答案
