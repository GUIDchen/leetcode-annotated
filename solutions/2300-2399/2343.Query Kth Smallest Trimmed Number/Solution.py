# 题目：2343. 裁剪数字后查询第 K 小的数字（Query Kth Smallest Trimmed Number）
# 思路：对每个查询用切片 v[-trim:] 取每个数字的末尾 trim 位，构造 (裁剪结果, 原下标) 元组并排序；元组排序先比字符串再比下标，正好满足数值相同时下标小的在前，取第 k-1 个元组的下标即为答案。
# 时间复杂度：O(q · n log n · L)，q 为查询数、L 为字符串长度；空间复杂度：O(n)，每个查询构造一份临时列表。
class Solution:  # LeetCode 约定的题解类
    def smallestTrimmedNumbers(  # 返回每个查询对应的答案：第 k 小裁剪数字的原下标
        self, nums: List[str], queries: List[List[int]]  # nums 是数字字符串数组，queries 是 {k, trim} 列表；分多行书写只为控制行宽
    ) -> List[int]:  # 类型标注：queries 是二维整数列表，返回值是下标列表
        ans = []  # ans 按查询顺序收集答案
        for k, trim in queries:  # 逐个查询独立处理，k 是第几小（1 起），trim 是保留的末尾位数
            t = sorted((v[-trim:], i) for i, v in enumerate(nums))  # 生成器表达式枚举下标与原字符串，切片取末尾 trim 位；元组排序先比字符串、再比下标
            ans.append(t[k - 1][1])  # 第 k 小对应下标 k-1，元组的第 2 个元素就是原下标
        return ans  # 按查询顺序返回全部答案
