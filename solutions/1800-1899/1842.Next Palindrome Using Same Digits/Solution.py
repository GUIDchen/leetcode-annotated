# 题目：1842. 下个由相同数字构成的回文串（Next Palindrome Using Same Digits）🔒
# 思路：回文串由前半段唯一决定，先对前半段求"下一个排列"（找下降点 → 交换 → 翻转后缀），再把前半段镜像到后半段；前半段已是最大排列则返回空串。
# 时间复杂度：O(n)，只做几趟线性扫描；空间复杂度：O(n)，把字符串转成字符列表以便原地交换。
class Solution:  # LeetCode 约定的题解类
    def nextPalindrome(self, num: str) -> str:  # num：输入的回文数字串，返回下一个更大的回文串
        def next_permutation(nums: List[str]) -> bool:  # 内部函数：把 nums 的前半段改成下一个排列，成功返回 True
            n = len(nums) // 2  # 只有前半段参与排列，所以有效长度取总长的一半
            i = n - 2  # 从倒数第二个位置开始找"下降点"
            while i >= 0 and nums[i] >= nums[i + 1]:  # 从右往左找第一个严格小于右邻的位置
                i -= 1  # 不满足条件就继续左移
            if i < 0:  # 整个前半段非递增，说明它已经是最大排列
                return False  # 没有下一个排列
            j = n - 1  # 从最右端开始找比 nums[i] 大的最小字符
            while j >= 0 and nums[j] <= nums[i]:  # 跳过所有不大于 nums[i] 的字符
                j -= 1  # 继续左移
            nums[i], nums[j] = nums[j], nums[i]  # 交换，使前缀字典序刚好变大
            nums[i + 1 : n] = nums[i + 1 : n][::-1]  # 后缀原来是降序，翻转成升序让整体增量最小
            return True  # 修改成功

        nums = list(num)  # 转成字符列表，便于按下标原地交换
        if not next_permutation(nums):  # 前半段不存在下一个排列
            return ""  # 返回空串表示无解
        n = len(nums)  # 这里的 n 是整串长度（注意与内层 n 含义不同）
        for i in range(n // 2):  # 遍历前半段的每个位置
            nums[n - i - 1] = nums[i]  # 把后半段对应位置写成左半段的镜像
        return "".join(nums)  # 拼接成字符串返回
