# 题目：2288. 价格减免（Apply Discount to Prices）
# 核心思路：用 split() 按空格切词，逐个判断是否为「$ 开头且后面全是数字」的合法价格；是就用浮点乘折扣并格式化两位小数，非价格单词原样保留，最后用空格拼回。
# 时间复杂度：O(L)，L 为句子长度，每个字符只处理常数次；空间复杂度：O(L)，结果单词列表与最终字符串。
class Solution:  # LeetCode 约定的题解类
    def discountPrices(self, sentence: str, discount: int) -> str:  # sentence：原句；discount：折扣百分比；返回替换价格后的句子
        ans = []  # 用列表收集处理后的单词，最后统一拼接
        for w in sentence.split():  # 按空格切分句子，逐个处理单词
            if w[0] == '$' and w[1:].isdigit():  # 以 $ 开头且后面全是数字，才认定为合法价格
                w = f'${int(w[1:]) * (1 - discount / 100):.2f}'  # 去掉 $ 转成整数，按折扣比例计算并保留两位小数，再拼回 $
            ans.append(w)  # 把（可能已打折的）单词放入结果列表
        return ' '.join(ans)  # 用单个空格重新拼成句子并返回
