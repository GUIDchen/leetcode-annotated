# 题目：1442. 形成两个异或相等数组的三元组数目（Count Triplets That Can Form Two Arrays of Equal XOR）
# 思路：a == b 与 arr[i..k] 异或和为 0 等价；枚举 i 并向右累加异或，遇 0 就把 k-i 计入答案。
# 时间复杂度：O(n^2)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def countTriplets(self, arr: List[int]) -> int:  # arr 是输入数组
        ans, n = 0, len(arr)  # ans 统计答案，n 是数组长度
        for i, x in enumerate(arr):  # 枚举左端点 i 及其值 x
            s = x  # 以 i 开头的区间异或和
            for k in range(i + 1, n):  # 枚举右端点 k
                s ^= arr[k]  # 把 arr[k] 并入异或和
                if s == 0:  # 区间异或为 0，说明左右两段异或相等
                    ans += k - i  # 分界点 j 有 k-i 种取法
        return ans  # 返回合法三元组总数
