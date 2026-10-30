# 题目：3889. 镜像频次距离（Mirror Frequency Distance）
# 思路：先统计每个字符的出现次数，再对每个字符算出它的镜像字符，用集合保证每一对镜像字符只统计一次，累加 |freq(c) - freq(m)|。
# 时间复杂度：O(n + |Σ|)，n 为字符串长度、|Σ| 为字符集大小；空间复杂度：O(|Σ|)，存放频次表与去重集合。
class Solution:  # LeetCode 约定的题解类
    def mirrorFrequency(self, s: str) -> int:  # s：只由小写字母和数字组成的字符串
        freq = Counter(s)  # Counter 统计每个字符的出现次数
        ans = 0  # 答案：所有镜像字符对的频次绝对差之和
        vis = set()  # 去重集合：记录已经统计过的字符
        for c, v in freq.items():  # 遍历每个字符及其频次
            m = (  # 计算镜像字符 m（多行表达式的开头）
                chr(ord("a") + 25 - (ord(c) - ord("a")))  # 字母的镜像按字母表逆序：a↔z、b↔y
                if c.isalpha()  # 先判断是否为字母
                else str(9 - int(c))  # 数字的镜像：0↔9、1↔8
            )  # 结束多行表达式
            if m in vis:  # 镜像字符已经处理过，说明这一对已统计
                continue  # 直接跳过，避免重复计数
            vis.add(c)  # 标记当前字符已处理
            ans += abs(v - freq[m])  # 累加绝对差；freq[m] 不存在时为 0
        return ans  # 返回镜像频次距离
