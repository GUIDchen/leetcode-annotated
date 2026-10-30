# 题目：2014. 重复 K 次的最长子序列（Longest Subsequence Repeated k Times）
# 思路：先统计字符频率，只保留出现次数 ≥ k 的字符；再用 BFS 按长度递增枚举由这些字符构成的串，用子序列匹配检查它重复 k 次是否仍是 s 的子序列，最后一个通过的串即最长且字典序最大。
# 时间复杂度：O(|Σ|^L · |s|)，L 为答案长度（受频率上限约束）；空间复杂度：O(|Σ|^L)，队列最多存放这么多候选串。
class Solution:  # LeetCode 约定的题解类
    def longestSubsequenceRepeatedK(self, s: str, k: int) -> str:  # s：原字符串；k：重复次数；返回重复 k 次后仍为 s 子序列的最长字符串
        def check(t: str, k: int) -> bool:  # 内层函数：判断 t 连续重复 k 次后是否仍是 s 的子序列
            i = 0  # i 指向 t 中当前等待匹配的字符位置
            for c in s:  # 顺序扫描 s，贪心地匹配 t 的字符
                if c == t[i]:  # s 的当前字符与 t 的待匹配字符相同
                    i += 1  # 该字符匹配成功，t 前进一位
                    if i == len(t):  # t 已经完整匹配了一遍
                        k -= 1  # 剩余重复次数减一
                        if k == 0:  # 减到 0 说明已重复 k 遍
                            return True  # 校验成功
                        i = 0  # 重置下标，从头开始匹配下一遍
            return False  # s 扫完仍未凑满 k 遍，说明 t 不合法

        cnt = Counter(s)  # 统计 s 中每个字符的出现次数
        cs = [c for c in ascii_lowercase if cnt[c] >= k]  # 只保留出现次数 ≥ k 的字符，并保持字典序升序
        q = deque([""])  # BFS 队列，从空串开始按长度递增枚举
        ans = ""  # 记录最后一个通过校验（即最长且字典序最大）的候选串
        while q:  # 队列非空就继续扩展
            cur = q.popleft()  # 取出队首候选串
            for c in cs:  # 尝试在末尾追加每个可用字符
                nxt = cur + c  # 拼出更长一层的候选串
                if check(nxt, k):  # 校验 nxt 重复 k 次后是否仍为 s 的子序列
                    ans = nxt  # 通过校验就更新答案；BFS 顺序保证后更新的串更长或字典序更大
                    q.append(nxt)  # 继续以它为基础扩展更长的串
        return ans  # 返回最长且字典序最大的合法子序列
