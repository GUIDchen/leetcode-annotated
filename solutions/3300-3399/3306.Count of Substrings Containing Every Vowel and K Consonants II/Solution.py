# 题目：3306. 元音辅音字符串计数 II（Count of Substrings Containing Every Vowel and K Consonants II）
# 思路：用滑动窗口求 f(k) = 「辅音数至少 k 且五种元音齐全」的子串数，答案 = f(k) - f(k + 1)，用容斥把「至少」变成「恰好」。
# 复杂度：时间 O(n)，左右端点各最多移动 n 次，且 f 只调用两次；空间 O(1)，Counter 中最多只有 5 个元音键。
class Solution:  # LeetCode 约定的题解类
    def countOfSubstrings(self, word: str, k: int) -> int:  # word 为只含小写字母的字符串，k 为要求的辅音个数，返回满足条件的子串数
        def f(k: int) -> int:  # 辅助函数 f(k)：统计「至少 k 个辅音且五种元音齐全」的子串个数
            cnt = Counter()  # 窗口内各元音的计数，len(cnt) 即当前出现的元音种类数
            ans = l = x = 0  # ans：累加答案；l：窗口左端点；x：窗口内辅音个数
            for c in word:  # 枚举右端点，把字符 c 并入窗口
                if c in "aeiou":  # 是元音（用 5 个字符组成的字符串做成员判断）
                    cnt[c] += 1  # 该元音计数加一
                else:  # 否则是辅音
                    x += 1  # 窗口内辅音个数加一
                while x >= k and len(cnt) == 5:  # 窗口满足条件时不断右移左端点收缩，直到不再满足
                    d = word[l]  # 取出窗口最左边的字符
                    if d in "aeiou":  # 移出的是元音
                        cnt[d] -= 1  # 对应元音计数减一
                        if cnt[d] == 0:  # 这种元音在窗口里彻底消失了
                            cnt.pop(d)  # 删除该键，保证 len(cnt) 表示元音种类数
                    else:  # 移出的是辅音
                        x -= 1  # 窗口辅音个数减一
                    l += 1  # 左端点右移一位
                ans += l  # 以当前位置为右端点时，左端点取 0..l-1 共 l 个都满足条件，累加到答案
            return ans  # 返回本轮 f(k) 的统计结果

        return f(k) - f(k + 1)  # 「至少 k 个」减去「至少 k+1 个」，恰好得到「正好 k 个辅音」的子串数
