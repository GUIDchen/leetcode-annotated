# 题目：3720. 大于目标字符串的最小字典序排列（Lexicographically Smallest Permutation Greater Than Target）
# 思路：先尽量拉长与 target 的公共前缀；再从最长前缀位置向左回退，在该位换成一个可用且更大的最小字母，剩余字母按升序拼接即得最小后缀。
# 时间复杂度：O(26n)，空间复杂度：O(n)，用于保存答案前缀与字母计数。
class Solution:  # LeetCode 约定的题解类
    def lexGreaterPermutation(self, s: str, target: str) -> str:  # s：可重排的字符来源；target：目标串；返回大于 target 的最小字典序排列
        cnt = Counter(s)  # 统计 s 中各字母的可用次数
        n = len(target)  # 目标串长度
        ans = []  # 与 target 逐位相等的前缀
        for c in target:  # 先尽量把公共前缀拉长
            if cnt[c] == 0:  # 该字母已用尽，公共前缀到此为止
                break  # 提前结束前缀匹配
            cnt[c] -= 1  # 消耗一个该字母
            ans.append(c)  # 该位与 target 相同
        for i in range(len(ans), -1, -1):  # 从最长的公共前缀位置开始向左回退，寻找可以变大的位置
            if i < n:  # 该位置在 target 内才需要比较
                for c in ascii_lowercase:  # 按字典序从小到大尝试更大的字母
                    if c > target[i] and cnt[c] > 0:  # 找到可用且比 target[i] 大的最小字母
                        cnt[c] -= 1  # 消耗一个该字母
                        rest = ''.join(x * cnt[x] for x in ascii_lowercase)  # 剩余字母按升序拼接即为字典序最小的后缀
                        return ''.join(ans[:i]) + c + rest  # 前缀 + 变大的字母 + 最小后缀
            if i > 0:  # 回退前把 ans[i-1] 还回计数池
                cnt[ans[i - 1]] += 1  # 释放前缀末位的字母，供更靠前的位置使用
        return ''  # 不存在更大的排列，返回空串
