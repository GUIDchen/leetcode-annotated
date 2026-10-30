# 题目：2047. 句子中的有效单词数（Number of Valid Words in a Sentence）
# 思路：按空白切分句子，逐个 token 校验：不能含数字；标点只能在末尾；连字符最多一个且两侧都是字母。合法就计入答案。
# 时间复杂度：O(L)，L 为句子总长度；空间复杂度：O(L)，切分出的 token 列表。
class Solution:  # LeetCode 约定的题解类
    def countValidWords(self, sentence: str) -> int:  # sentence 是输入句子，返回其中有效单词的个数
        def check(s: str) -> bool:  # 内部函数：判断单个 token 是否为有效单词
            st = False  # st 标记本单词是否已经用过连字符
            for i, c in enumerate(s):  # 同时取得字符下标 i 和字符 c
                if c.isdigit() or (c in "!.," and i < len(s) - 1):  # 出现数字，或标点没有出现在单词末尾，都算无效
                    return False  # 判为无效
                if c == "-":  # 遇到连字符，单独校验
                    if (  # 连字符的非法的三种情况：
                        st  # 已经出现过一次连字符
                        or i in (0, len(s) - 1)  # 连字符位于单词的开头或结尾
                        or not s[i - 1].isalpha()  # 连字符左边不是字母
                        or not s[i + 1].isalpha()  # 连字符右边不是字母
                    ):  # 以上任一情况成立就无效
                        return False  # 判为无效
                    st = True  # 标记本单词的连字符已经用过
            return True  # 所有检查通过，这个 token 是有效单词

        return sum(check(s) for s in sentence.split())  # 按空白切分句子，统计其中有效单词的个数
