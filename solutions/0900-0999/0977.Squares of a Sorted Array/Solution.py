# 题目：977. 有序数组的平方（Squares of a Sorted Array）
# 思路：双指针从两端向中间取绝对值较大者，其平方最大，降序追加到列表末尾后翻转，即得非递减结果。
# 时间复杂度：O(n)，每个元素只处理一次；空间复杂度：O(n)，答案列表。
class Solution:  # LeetCode 约定的题解类
    def sortedSquares(self, nums: List[int]) -> List[int]:  # nums：已按非递减排序的数组，返回每个元素平方后仍按非递减排序的结果
        ans = []  # ans 从最大端开始追加：每次取两端中较大的平方值，最后再翻转
        i, j = 0, len(nums) - 1  # i 指向左端，j 指向右端
        while i <= j:  # 两端向中间收缩，直到 i 超过 j
            a = nums[i] * nums[i]  # 左端元素的平方
            b = nums[j] * nums[j]  # 右端元素的平方
            if a > b:  # 平方较大的那个一定是当前剩余元素中最大的
                ans.append(a)  # 把较大值追加到列表尾部（它最大，翻转后应在最后）
                i += 1  # 左端已用掉，左指针右移
            else:  # 否则右端的平方更大
                ans.append(b)  # 把右端的平方追加到列表尾部
                j -= 1  # 右端已用掉，右指针左移
        return ans[::-1]  # 结果是降序追加的，翻转后即为非递减排序
