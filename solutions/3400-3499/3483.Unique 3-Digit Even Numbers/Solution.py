# 3483. 不同三位偶数的数目 / Unique 3-Digit Even Numbers
# 核心思路：枚举百位、十位、个位三个数字，个位取偶数且百位不为 0，拼成三位数放入集合去重后返回元素个数。
# 复杂度：时间 O(n^3)，空间 O(n^3)（集合最多存 n^3 个数）。
class Solution:  # 定义题解类
    def totalNumbers(self, digits: List[int]) -> int:  # 主函数：返回不同三位偶数的数目
        s = set()  # 集合用于对构造出的三位数按数值去重
        for i, a in enumerate(digits):  # 枚举个位数字 a 及其下标 i
            if a & 1:  # 个位必须为偶数，与 1 相与为 1 说明是奇数
                continue  # 跳过奇数个位
            for j, b in enumerate(digits):  # 枚举十位数字 b 及其下标 j
                if i == j:  # 十位与个位不能使用同一下标
                    continue  # 跳过下标冲突的情况
                for k, c in enumerate(digits):  # 枚举百位数字 c 及其下标 k
                    if c == 0 or k in (i, j):  # 百位不能为 0，也不能与已用的下标重复
                        continue  # 跳过不合法的百位
                    s.add(c * 100 + b * 10 + a)  # 拼成三位数加入集合，重复值自动去重
        return len(s)  # 集合大小即不同三位偶数的个数
