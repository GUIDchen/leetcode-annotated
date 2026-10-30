# 题目：2149. 按符号重排数组（Rearrange Array Elements by Sign）
# 思路：新建答案数组，用偶数位指针 i 放正数、奇数位指针 j 放负数，一次遍历即可保持同类元素原来的相对顺序。
# 时间复杂度：O(n)，只需遍历一次；空间复杂度：O(n)，需要长度为 n 的答案数组。
class Solution:  # LeetCode 约定的题解类
    def rearrangeArray(self, nums: List[int]) -> List[int]:  # nums：正负数量相等、待重排的数组
        ans = [0] * len(nums)  # 预先分配与输入等长的答案数组
        i, j = 0, 1  # i：下一个放正数的偶数下标；j：下一个放负数的奇数下标
        for x in nums:  # 按原顺序遍历每个元素
            if x > 0:  # 正数放在偶数位
                ans[i] = x  # 写入当前偶数位
                i += 2  # 偶数位指针后移两位
            else:  # 负数放在奇数位
                ans[j] = x  # 写入当前奇数位
                j += 2  # 奇数位指针后移两位
        return ans  # 返回正负交替排列好的数组
