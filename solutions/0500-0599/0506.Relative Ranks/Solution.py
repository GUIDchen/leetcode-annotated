# 题目：506. 相对名次（Relative Ranks）
# 思路：对下标按得分降序排序，名次 i 对应的运动员下标是 idx[i]；前三名填奖牌名，其余填 i+1。
# 时间复杂度：O(n log n)，排序开销；空间复杂度：O(n)，下标数组、答案数组与奖牌名数组。
class Solution:  # LeetCode 约定的题解类
    def findRelativeRanks(self, score: List[int]) -> List[str]:  # score：各运动员得分；返回与输入同序的名次字符串数组
        n = len(score)  # 运动员人数（即下标个数）
        idx = list(range(n))  # 下标列表 0..n-1
        idx.sort(key=lambda x: -score[x])  # 按得分降序排列下标：key 取负分，负得越多排得越前
        top3 = ["Gold Medal", "Silver Medal", "Bronze Medal"]  # 前三名的固定奖牌名
        ans = [None] * n  # 结果数组，先用 None 占位，按原始下标回填
        for i, j in enumerate(idx):  # i 是名次（从 0 起），j 是该名次对应的原始下标
            ans[j] = top3[i] if i < 3 else str(i + 1)  # 前三名给奖牌名，其余给从 1 开始的名次数字
        return ans  # 返回结果数组
