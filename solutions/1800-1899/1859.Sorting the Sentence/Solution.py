# 题目：1859. 将句子排序（Sorting the Sentence）
# 思路：按空格切分出单词，每个单词末位是它的位次号，直接以「编号 - 1」为下标把去掉编号的单词放进结果列表，最后用空格拼接，省去排序。
# 时间复杂度：O(L)，L 为句子长度；空间复杂度：O(L)，存放单词与结果。
class Solution:  # LeetCode 约定的题解类
    def sortSentence(self, s: str) -> str:  # s：每个单词末尾带 1..9 位次号的乱序句子
        ws = s.split()  # 按空白切分出所有单词
        ans = [None] * len(ws)  # 按位次号直接定位置，省掉排序
        for w in ws:  # 遍历每个带编号的单词
            ans[int(w[-1]) - 1] = w[:-1]  # 末位是编号，减一得到 0 基下标；w[:-1] 是去掉编号的单词
        return " ".join(ans)  # 用空格拼回句子并返回
