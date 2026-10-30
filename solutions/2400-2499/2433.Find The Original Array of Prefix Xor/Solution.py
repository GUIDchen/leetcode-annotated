# 题目：2433. 找出前缀异或的原始数组（Find The Original Array of Prefix Xor）
# 思路：由 pref[i] = pref[i-1] ^ arr[i] 两边同异或 pref[i-1]，得 arr[i] = pref[i-1] ^ pref[i]；在头部补 0 后就是相邻两项异或。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(n)，列表推导新建了与输入等长的结果列表。
class Solution:  # LeetCode 约定的题解类
    def findArray(self, pref: List[int]) -> List[int]:  # pref：题目给出的前缀异或数组
        return [a ^ b for a, b in pairwise([0] + pref)]  # 头部补 0（相当于 pref[-1] = 0），再对相邻两项做异或得到 arr
