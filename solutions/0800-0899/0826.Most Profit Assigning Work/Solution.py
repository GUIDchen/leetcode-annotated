# 题目：826. 安排工作以达到最大收益（Most Profit Assigning Work）
# 思路：贪心。工人与工作分别按能力、难度升序排序，用一个不回退的指针把「难度不高于当前工人」的工作依次纳入，并维护其中最大收益，每个工人直接领取这个最大值。
# 时间复杂度：O(n log n + m log m)，来自两次排序；空间复杂度：O(n)，保存打包后的 jobs 列表。
class Solution:  # LeetCode 约定的题解类
    def maxProfitAssignment(  # 方法签名较长，拆成多行书写
        self, difficulty: List[int], profit: List[int], worker: List[int]  # self 之外：difficulty 与 profit 是每项工作的难度与收益，worker 是工人能力
    ) -> int:  # 返回这些工人能获得的最大总收益
        worker.sort()  # 工人按能力升序，后处理的工人能力不小于前面的
        jobs = sorted(zip(difficulty, profit))  # zip 把难度与收益配对，sorted 按难度升序排序
        ans = mx = i = 0  # ans：总收益；mx：当前能拿到的最大单项收益；i：jobs 上的指针
        for w in worker:  # 按能力从小到大处理每个工人
            while i < len(jobs) and jobs[i][0] <= w:  # 把难度不超过当前工人能力的工作全部纳入候选，指针 i 只增不减，所以整体是线性的
                mx = max(mx, jobs[i][1])  # 取候选工作里的最大收益
                i += 1  # 指针后移，下一轮只考察更难的工作
            ans += mx  # 当前工人拿 mx（若无任何可做的工作，mx 为 0，加 0 无害）
        return ans  # 返回总收益
