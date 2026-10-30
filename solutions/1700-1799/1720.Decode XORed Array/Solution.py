# 题目：1720. 解码异或后的数组（Decode XORed Array）难度：简单
# 思路：已知 encoded[i] = arr[i] ^ arr[i+1] 且 arr[0] = first，利用异或的自反性（a ^ b ^ b = a），
# 从前往后逐个推出 arr[i+1] = arr[i] ^ encoded[i]，把结果依次追加到答案数组即可。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，答案数组本身（不计返回值则为 O(1)）。
class Solution:  # LeetCode 约定的题解类
    def decode(self, encoded: List[int], first: int) -> List[int]:  # encoded：相邻元素异或值；first：arr[0]
        ans = [first]  # 答案数组以已知的 arr[0] = first 起始
        for x in encoded:  # 按顺序取出每个异或值
            ans.append(ans[-1] ^ x)  # 由 a ^ b = c 推出 arr[i+1] = arr[i] ^ encoded[i]
        return ans  # 返回完整的解码数组
