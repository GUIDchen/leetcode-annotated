# 题目：2442. 反转之后不同整数的数目（Count Number of Distinct Integers After Reverse Operations）【中等】
# 思路：先把原数组放进集合，再把每个数转成字符串反转后转回整数插入集合，最后集合大小就是不同整数的数目。
# 时间复杂度：O(n·log10M)，每个数要做一次字符串反转，M 为数值大小；空间复杂度：O(n)，集合最多存 2n 个数。
class Solution:  # LeetCode 约定的题解类
    def countDistinctIntegers(self, nums: List[int]) -> int:  # nums 是输入数组
        s = set(nums)  # 先去重收集所有原数，贡献「原数」这一半答案
        for x in nums:  # 逐个处理原数（x 是循环变量，不会改到 nums）
            y = int(str(x)[::-1])  # 转成字符串后用 [::-1] 反转，再转回整数得到反转数（前导零在转 int 时自动丢掉）
            s.add(y)  # 把反转数加进集合，已存在则自动忽略
        return len(s)  # 集合大小就是不同整数的个数
