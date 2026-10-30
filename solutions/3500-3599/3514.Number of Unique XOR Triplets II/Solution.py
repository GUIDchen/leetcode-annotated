# 题目：3514. 不同 XOR 三元组的数目 II（Number of Unique XOR Triplets II）
# 思路：先用双重循环求出所有二元异或值，再与每个数异或得到三元异或值，最后统计可达个数。
# 时间复杂度：O(n^2 + nV)，V 为值域上界；空间复杂度：O(V)。
class Solution:  # LeetCode 约定的题解类
    def uniqueXorTriplets(self, nums: List[int]) -> int:  # nums：输入的整数数组，返回不同异或三元组的个数
        mx = max(nums) << 1  # mx：异或结果上界，最大值左移一位即可覆盖全部异或结果
        st = [False] * mx  # st[x] 标记二元异或值 x 是否可达
        for a in nums:  # 枚举第一个数 a
            for b in nums:  # 枚举第二个数 b
                st[a ^ b] = True  # 标记二元异或值 a^b 可达
        s = [0] * mx  # s[x] 记录三元异或值 x 是否可达
        for ab in range(mx):  # 遍历所有可能的二元异或值
            if st[ab]:  # 该二元异或值可达时才枚举第三个数
                for c in nums:  # 枚举第三个数 c
                    s[ab ^ c] = 1  # 标记三元异或值 ab^c 可达
        return sum(s)  # 求和得到可达的三元异或值个数
