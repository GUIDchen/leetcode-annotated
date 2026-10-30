# 题目：3305. 元音辅音字符串计数 I（Count of Substrings Containing Every Vowel and K Consonants I）
# 思路：把「恰好 k 个辅音」转成「至少 k 个」减去「至少 k+1 个」，用滑动窗口分别 O(n) 统计。
# 时间复杂度：O(n)，每个字符至多进出窗口一次；空间复杂度：O(1)，Counter 最多存 5 个元音。
class Solution:  # LeetCode 约定的题解类
    def countOfSubstrings(self, word: str, k: int) -> int:  # word：待统计字符串；k：恰好要包含的辅音个数；返回满足条件的子串个数
        def f(k: int) -> int:  # 闭包 f(k)：统计含全部 5 个元音且辅音数 >= k 的子串个数（至少型）
            cnt = Counter()  # cnt：窗口内各元音出现次数，长度即出现的元音种类数
            ans = l = x = 0  # ans 累加答案；l 是窗口左端点；x 是窗口内辅音个数
            for c in word:  # 右端点逐个扩展窗口
                if c in "aeiou":  # 当前字符是元音
                    cnt[c] += 1  # 累加该元音的计数
                else:  # 否则是辅音
                    x += 1  # 辅音计数 +1
                while x >= k and len(cnt) == 5:  # 满足「辅音足够且 5 种元音齐全」时持续收缩左端点
                    d = word[l]  # 取出左端点字符
                    if d in "aeiou":  # 移出的是元音
                        cnt[d] -= 1  # 该元音计数减一
                        if cnt[d] == 0:  # 计数归零
                            cnt.pop(d)  # 从 Counter 中删除，保证 len(cnt) 表示元音种类数
                    else:  # 移出的是辅音
                        x -= 1  # 辅音计数减一
                    l += 1  # 左端点右移
                ans += l  # 此时左端点 < l 的窗口都合法，共贡献 l 个
            return ans  # 返回至少型计数

        return f(k) - f(k + 1)  # 恰好 k 个 = 「至少 k 个」-「至少 k+1 个」
