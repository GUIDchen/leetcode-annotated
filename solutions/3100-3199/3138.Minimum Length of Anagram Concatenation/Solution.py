# 题目：3138. 同位字符串连接的最小长度（Minimum Length of Anagram Concatenation）
# 思路：从小到大枚举块长 k（必须整除 n），检查每个长 k 的块字符频次是否相同；块频次乘以块数应等于整体频次。
# 时间复杂度：O(n*d)，d 为 n 的约数个数（每个约数都要扫全串）；空间复杂度：O(1)，计数表只含 26 个字母。
class Solution:  # LeetCode 约定的题解类
    def minAnagramLength(self, s: str) -> int:  # s 是待拆分的原串，返回最小的块长度
        def check(k: int) -> bool:  # 闭包：判断能否把 s 切成若干长 k 且互为字母异位词的块
            for i in range(0, n, k):  # 按长度 k 从头逐块枚举；n 在闭包被调用时已赋值
                cnt1 = Counter(s[i : i + k])  # 统计当前块的字符频次
                for c, v in cnt.items():  # 逐个字母比较块频次与整体频次
                    if cnt1[c] * (n // k) != v:  # 若所有块同构，则块频次 × 块数必须等于整体频次
                        return False  # 只要有一个字母不满足，该 k 就不可行
            return True  # 每个块都同构，返回可行

        cnt = Counter(s)  # 整体字符频次
        n = len(s)  # 记录原串长度
        for i in range(1, n + 1):  # 从小到大枚举块长度；i=n 时必然成立
            if n % i == 0 and check(i):  # 块长必须整除 n，且切分后每个块都同构
                return i  # 第一个可行的长度就是最小长度
