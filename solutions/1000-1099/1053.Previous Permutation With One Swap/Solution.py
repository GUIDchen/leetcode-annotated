# 题目：1053. 交换一次的先前排列（Previous Permutation With One Swap）
# 思路：从右往左找第一个 arr[i-1] > arr[i] 的断点，再在断点右侧从右往左找小于断点值的最大元素交换。
# 时间复杂度：O(n)，最多扫描两遍；空间复杂度：O(1)，只在原数组上交换。
class Solution:  # LeetCode 约定的题解类
    def prevPermOpt1(self, arr: List[int]) -> List[int]:  # arr：当前排列，返回交换一次后能得到的最大「先前排列」
        n = len(arr)  # 排列长度
        for i in range(n - 1, 0, -1):  # 从右往左找第一个可以变小的位置：arr[i-1] > arr[i]
            if arr[i - 1] > arr[i]:  # 找到断点，说明把 i-1 处的值换小就能得到更小的排列
                for j in range(n - 1, i - 1, -1):  # 在断点右侧从右往左找合适的元素来交换
                    if arr[j] < arr[i - 1] and arr[j] != arr[j - 1]:  # 取小于断点值中最大的那个；跳过与前一位相等的值以免换错位置
                        arr[i - 1], arr[j] = arr[j], arr[i - 1]  # 交换一次，右侧保持原升序即得最大的先前排列
                        return arr  # 题目只允许交换一次，交换后立即返回
        return arr  # 不存在先前排列（本身已非递减），原样返回
