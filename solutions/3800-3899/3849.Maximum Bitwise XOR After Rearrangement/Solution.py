# 3849. 重新排列后的最大按位异或值 / Maximum Bitwise XOR After Rearrangement（中等）
# 核心思路：统计 t 中 0 与 1 的个数，从高位到低位优先用与 s 当前位相反的字符，使每位的异或结果为 1。
# 复杂度：时间 O(|s| + |t|)，空间 O(1)。
class Solution:  # 题解类（LeetCode 约定类名）
    def maximumXor(self, s: str, t: str) -> str:  # 重排 t 后与 s 逐位异或，返回能得到的最大二进制串
        cnt = [0, 0]  # cnt[0]、cnt[1] 分别记录 t 中 0 与 1 的剩余个数
        for c in t:  # 统计 t 中两种字符的数量
            cnt[int(c)] += 1  # 对应字符计数加一
        ans = ['0'] * len(s)  # 结果列表，长度与 s 相同，先全置 0
        for i, c in enumerate(s):  # 从高位到低位依次为 s 的每一位挑选 t 中的字符
            x = int(c)  # s 当前位的比特值
            if cnt[x ^ 1]:  # 若还存在与 x 相反的字符，异或可得 1
                cnt[x ^ 1] -= 1  # 消耗一个相反字符
                ans[i] = '1'  # 该位结果为 1
            else:  # 否则只能用相同字符，异或结果为 0
                cnt[x] -= 1  # 消耗一个相同字符
        return ''.join(ans)  # 拼接并返回最大异或结果串
