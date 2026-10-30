# 题目：767. 重构字符串（Reorganize String）
# 思路：先判可行（最高频次不超过 (n+1)//2），再按频次降序把字母依次填到 0,2,4,... 再回到 1,3,5,...，保证相邻字符不同。
# 时间复杂度：O(n log 26)，统计与填表为线性，排序仅涉及常数个字母；空间复杂度：O(n)，答案数组与计数器。
class Solution:  # LeetCode 约定的题解类
    def reorganizeString(self, s: str) -> str:  # s：待重构的字符串
        n = len(s)  # 字符串长度
        cnt = Counter(s)  # 统计每个字母出现的次数
        mx = max(cnt.values())  # 出现次数最多的字母的频次
        if mx > (n + 1) // 2:  # 超过向上取整的一半就无法隔开
            return ''  # 无法重构，返回空串
        i = 0  # 当前写入位置，步长为 2
        ans = [None] * n  # 预先按长度开好答案列表
        for k, v in cnt.most_common():  # 按频次从高到低遍历字母
            while v:  # 把当前字母逐个写入
                ans[i] = k  # 写入该字母到位置 i
                v -= 1  # 剩余个数减一
                i += 2  # 隔一个位置写下一个，保证不相邻
                if i >= n:  # 越过末尾
                    i = 1  # 回到下标 1，切换到另一组奇偶位置
        return ''.join(ans)  # 拼接成字符串返回
