# 题目：2178. 拆分成最多数目的正偶数之和（Maximum Split of Positive Even Integers）
# 思路：贪心地从 2 开始依次取 2、4、6…；剩余值不足下一个偶数时并入最后一个，个数即为最多。
# 时间复杂度：O(√n)，最多累加约 √n 个偶数；空间复杂度：O(√n)，答案列表的长度。
class Solution:  # LeetCode 约定的题解类
    def maximumEvenSplit(self, finalSum: int) -> List[int]:  # finalSum：需要拆分的正偶数之和
        if finalSum & 1:  # 最低位为 1 说明是奇数，奇数不可能拆成若干偶数之和
            return []  # 无解时返回空列表
        ans = []  # 存放拆分出的各个偶数（从 2 开始依次递增）
        i = 2  # 下一个候选偶数，从最小的 2 开始
        while i <= finalSum:  # 剩余值还够加入当前偶数时继续
            finalSum -= i  # 剩余待分配的和减少 i
            ans.append(i)  # 把当前偶数加入方案
            i += 2  # 候选偶数递增到下一个偶数
        ans[-1] += finalSum  # 余量并入最后一个偶数，总和不变且各数仍互不相同
        return ans  # 返回数目最多的拆分方案
