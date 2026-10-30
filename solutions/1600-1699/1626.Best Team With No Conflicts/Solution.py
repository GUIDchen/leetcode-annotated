# 题目：1626. 无矛盾的最佳球队（Best Team With No Conflicts）
# 思路：把「分数, 年龄」按分数升序排序，问题化为在年龄非降的前提下选子序列使分数和最大，用 O(n²) 的 DP 求解。
# 时间复杂度：O(n²)，排序 O(n log n) 之外还有两层循环；空间复杂度：O(n)，存放二元组与 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def bestTeamScore(self, scores: List[int], ages: List[int]) -> int:  # scores 为球员分数，ages 为球员年龄，返回无矛盾球队的最大总分
        arr = sorted(zip(scores, ages))  # 把「分数, 年龄」配对后按分数升序排序（分数相同再按年龄升序）
        n = len(arr)  # 球员人数
        f = [0] * n  # f[i]：以第 i 个球员作为球队最后一名时能取得的最大总分
        for i, (score, age) in enumerate(arr):  # 依次取出下标与「分数, 年龄」，把当前球员当作队尾
            for j in range(i):  # 枚举它可以接在前面的哪个球员 j 之后
                if age >= arr[j][1]:  # 年龄不小于前一名球员时，两人之间才不会产生矛盾
                    f[i] = max(f[i], f[j])  # 从更优的前驱状态转移过来
            f[i] += score  # 把当前球员的分数加入以他结尾的球队总分
        return max(f)  # 所有可能的队尾里取最大值即为答案
