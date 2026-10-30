# 题目：1534. 统计好三元组（Count Good Triplets）
# 思路：三重循环按 i<j<k 枚举所有下标组合，只要三对差值分别不超过 a、b、c，就计入答案。
# 时间复杂度：O(n³)，枚举全部三元组；空间复杂度：O(1)，只用了计数器与长度变量。
class Solution:  # LeetCode 约定的题解类
    def countGoodTriplets(self, arr: List[int], a: int, b: int, c: int) -> int:  # arr 是输入数组，a、b、c 是三对差值各自的上限
        ans, n = 0, len(arr)  # ans 统计好三元组个数，n 是数组长度
        for i in range(n):  # 枚举第一个下标 i
            for j in range(i + 1, n):  # 第二个下标从 i+1 起，保证 i<j
                for k in range(j + 1, n):  # 第三个下标从 j+1 起，保证 i<j<k
                    # 三个条件依次是：|arr[i]-arr[j]|<=a、|arr[j]-arr[k]|<=b、|arr[i]-arr[k]|<=c
                    ans += (  # 布尔表达式的值被隐式转成 0/1 累加进答案
                        abs(arr[i] - arr[j]) <= a
                        and abs(arr[j] - arr[k]) <= b
                        and abs(arr[i] - arr[k]) <= c
                    )
        return ans  # 返回好三元组的总数
