# 题目：249. 移位字符串分组（Group Shifted Strings）
# 思路：把每个字符减去首字符相对 'a' 的偏移，得到归一化基准串；用 defaultdict 按基准串分组。
# 时间复杂度：O(L)，L 为所有字符串总长度；空间复杂度：O(L)，分组表保存全部字符。
class Solution:  # LeetCode 约定的题解类
    def groupStrings(self, strings: List[str]) -> List[List[str]]:  # strings：待分组的字符串列表，返回按移位关系分好的各组
        g = defaultdict(list)  # 分组表：键是基准串，值是该组的原始字符串列表（缺键时自动创建空 list）
        for s in strings:  # 逐个字符串求它的基准串
            diff = ord(s[0]) - ord("a")  # 首字母相对 'a' 的偏移量
            t = []  # 存放基准串字符的列表
            for c in s:  # 逐字符做平移
                c = ord(c) - diff  # 减去首字母偏移，把字符平移到以 'a' 为起点
                if c < ord("a"):  # 平移后低于 'a'，说明发生了下溢
                    c += 26  # 加 26 做环绕
                t.append(chr(c))  # 把数值还原成字符并追加
            g["".join(t)].append(s)  # 拼接成基准串，把原串加入对应分组
        return list(g.values())  # 返回所有分组（只关心分组内容，不关心键）
