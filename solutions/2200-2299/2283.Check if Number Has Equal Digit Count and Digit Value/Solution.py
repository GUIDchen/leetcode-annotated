# 题目：2283. 判断一个数的数字计数是否等于数位的值（Check if Number Has Equal Digit Count and Digit Value）
# 核心思路：用 Counter 统计每个数字字符出现的次数，再用 all 逐位检查「第 i 位字符表示的数字」是否等于「数字 i 的出现次数」。
# 时间复杂度：O(n)，统计与校验各遍历一次；空间复杂度：O(1)，最多 10 个不同数字。
class Solution:  # LeetCode 约定的题解类
    def digitCount(self, num: str) -> bool:  # num：只含数字字符的字符串
        cnt = Counter(int(x) for x in num)  # 生成器表达式把每个字符转成整数后计数，未出现的数字计数默认为 0
        return all(cnt[i] == int(x) for i, x in enumerate(num))  # 逐位比较：数字 i 的计数是否等于第 i 位字符所表示的数字
