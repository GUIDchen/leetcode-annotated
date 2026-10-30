# 题目：3344. 最大尺寸数组（Maximum Sized Array）
# 思路：模块级预处理长度对应的最小总代价基数 f[i]，再在 [1, mx] 上二分最大可行长度。
# 时间复杂度：O(mx^2) 预处理 + O(log mx) 查找；空间复杂度：O(mx)。
mx = 1330  # 预处理上界，与 C++ 版本保持一致
f = [0] * mx  # f[i]：规模 i 对应的代价基数，先用 0 填满
for i in range(1, mx):  # 从小到大递推每个规模
    f[i] = f[i - 1] + i  # 先累加新下标自身带来的贡献 i
    for j in range(i):  # 枚举所有比 i 小的下标
        f[i] += 2 * (i | j)  # 配对产生的按位或贡献对称出现两次，故乘 2


class Solution:  # LeetCode 约定的题解类
    def maxSizedArray(self, s: int) -> int:  # s：允许的最大总代价
        l, r = 1, mx  # 二分区间：答案至少为 1，右界取预处理上界
        while l < r:  # 二分找满足条件的最大长度
            m = (l + r + 1) >> 1  # 上取整的中点（右移一位等价于整除 2）
            if f[m - 1] * (m - 1) * m // 2 <= s:  # 长度 m 所需的最小代价不超过 s 即可行
                l = m  # 可行就把左界抬到 m
            else:  # 代价超出预算
                r = m - 1  # 右界缩到 m-1
        return l  # 循环结束时 l 就是最大可行长度
