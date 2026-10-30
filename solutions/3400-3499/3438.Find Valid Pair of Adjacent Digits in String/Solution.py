# 3438. 找到字符串中合法的相邻数字 / Find Valid Pair of Adjacent Digits in String
# 核心思路：先统计每个数字出现次数，再用 pairwise 顺序检查相邻数字，要求两数字不同且各自频次恰等于自身数值。
# 复杂度：时间 O(n)，空间 O(1)（固定 10 个计数桶）。
class Solution:  # 定义题解类
    def findValidPair(self, s: str) -> str:  # 返回第一个合法相邻数字对，不存在时返回空串
        cnt = [0] * 10  # cnt[d] 记录数字 d 的出现次数
        for x in map(int, s):  # 把字符逐个转成数字
            cnt[x] += 1  # 对应数字计数加一
        for x, y in pairwise(map(int, s)):  # 顺序枚举相邻数字对 (x, y)
            if x != y and cnt[x] == x and cnt[y] == y:  # 两数字不同，且各自频次都等于自身数值
                return f"{x}{y}"  # 返回该相邻数字对
        return ""  # 没有合法数字对
