# 题目：2182. 构造限制重复的字符串（Construct String With Repeat Limit）
# 思路：统计各字母出现次数，从大到小枚举字母；每轮先连续放最多 repeatLimit 个当前最大字母，若仍有剩余，就插入一个更小的字母隔开。
# 时间复杂度：O(n + 26 * n)，每个字母最多被输出 n 次；空间复杂度：O(26 + n)，计数数组与答案列表。
class Solution:  # LeetCode 约定的题解类
    def repeatLimitedString(self, s: str, repeatLimit: int) -> str:  # s：可用字符；repeatLimit：同一字母最多连续出现次数
        cnt = [0] * 26  # 计数数组，cnt[x] 表示字母 chr(ord("a")+x) 的剩余个数
        for c in s:  # 遍历原字符串统计每种字母出现次数
            cnt[ord(c) - ord("a")] += 1  # 对应字母计数加一
        ans = []  # 结果片段列表，最后再拼接
        j = 24  # 备选「隔开字母」的下标，初始为 'y'（比 'z' 小一位）
        for i in range(25, -1, -1):  # i 从最大字母 'z'(25) 向下枚举到 'a'(0)
            j = min(i - 1, j)  # 隔开字母必须比 i 小，且随 i 缩小而同步缩小
            while 1:  # 反复输出字母 i，直到把它用完或没有更小字母可隔开
                x = min(repeatLimit, cnt[i])  # 本轮最多能连续写出的字母 i 的个数
                cnt[i] -= x  # 相应扣减剩余个数
                ans.append(ascii_lowercase[i] * x)  # 一次性把 x 个字母 i 追加到结果中
                if cnt[i] == 0:  # 字母 i 已经用完，不必再插入隔开字符
                    break  # 跳出本轮
                while j >= 0 and cnt[j] == 0:  # 从大到小找下一个还有剩余的更小字母
                    j -= 1  # 该字母用完，继续往下找
                if j < 0:  # 没有更小字母可用来隔开
                    break  # 剩下的字母 i 只能丢弃，结束
                cnt[j] -= 1  # 消耗一个更小字母作为隔开字符
                ans.append(ascii_lowercase[j])  # 把这个隔开字母加入结果
        return "".join(ans)  # 拼接并返回长度最长的合法字符串
