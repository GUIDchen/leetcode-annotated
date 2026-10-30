# 题目：2190. 数组中紧跟 key 之后出现最频繁的数字（Most Frequent Number Following Key In an Array）
# 思路：用 pairwise 遍历相邻元素对 (a, b)，当 a 等于 key 时给 b 计数加一，并随时维护出现次数最多的数字。
# 时间复杂度：O(n)；空间复杂度：O(n)，Counter 最多记录 n 个不同数字。
class Solution:  # LeetCode 约定的题解类
    def mostFrequent(self, nums: List[int], key: int) -> int:  # nums：输入数组；key：需要关注的数字
        cnt = Counter()  # 计数器：统计「紧跟 key 之后出现的数字」各自出现多少次
        ans = mx = 0  # ans：当前最频繁的数字；mx：对应的次数
        for a, b in pairwise(nums):  # pairwise 给出相邻的 (a, b)，省去手动处理下标越界
            if a == key:  # a 是 key，那么 b 就是紧跟其后的数字
                cnt[b] += 1  # 该数字的计数加一
                if mx < cnt[b]:  # 出现次数超过了当前最大值
                    mx = cnt[b]  # 刷新最大值
                    ans = b  # 记录这个新的最频繁数字
        return ans  # 返回答案（题目保证存在）
