# 题目：2042. 检查句子中的数字是否递增（Check if Numbers Are Ascending in a Sentence）
# 思路：split 按空格切词，首字符是数字的词转成整数，逐个判断是否严格递增。
# 时间复杂度：O(n)，每个字符只被切分一次；空间复杂度：O(n)，切分结果与临时单词占用线性空间。
class Solution:  # LeetCode 约定的题解类
    def areNumbersAscending(self, s: str) -> bool:  # s：只含小写字母、空格和数字的句子
        pre = 0  # pre：上一个数字，初始为 0 保证第一个数字一定更大
        for t in s.split():  # 按空格切分，逐个单词处理
            if t[0].isdigit():  # 首字符是数字，说明这个单词就是一个数字
                if (cur := int(t)) <= pre:  # 海象运算符：先把当前数字算到 cur，再与 pre 比较
                    return False  # 不满足严格递增，判定失败
                pre = cur  # 更新比较基准
        return True  # 全部数字严格递增，返回 True
