# 题目：39. 组合总和（Combination Sum）
# 思路：先排序，再回溯枚举：每层从下标 i 开始选数（保证组合不重复且同一个数可重复使用），剩余和减到 0 就收集答案，剩余和小于最小值就剪枝。
# 时间复杂度：与解的个数相关，约 O(n · 2^t)（t 为目标值与最小值之比）；空间复杂度：O(t)，递归深度即路径长度。
class Solution:  # LeetCode 约定的题解类
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:  # candidates 是可重复选取的正整数数组，target 是目标和；返回所有和为 target 的组合
        def dfs(i: int, s: int):  # 内部回溯函数：i 是本次可选的最小下标，s 是还差多少和
            if s == 0:  # 剩余和为 0，说明当前路径正好凑成 target
                ans.append(t[:])  # 用 t[:] 存入拷贝，否则后续增删 t 会把已保存的答案一起改掉
                return  # 这条分支结束，返回上一层
            if s < candidates[i]:  # 剩余和比当前能选的最小数还小，再选任何数只会更小
                return  # 直接剪枝返回
            for j in range(i, len(candidates)):  # 从 i 开始枚举，保证组合按非递减顺序生成，从而不产生重复组合
                t.append(candidates[j])  # 做选择：把当前数加入路径
                dfs(j, s - candidates[j])  # 递归时仍传 j（不是 j+1），表示同一个数可以重复使用
                t.pop()  # 撤销选择，恢复路径供下一个分支使用

        candidates.sort()  # 排序后数组递增，dfs 里的 s < candidates[i] 剪枝才成立
        t = []  # t 是当前路径（可变的临时组合）
        ans = []  # ans 收集所有合法组合
        dfs(0, target)  # 从下标 0、剩余和 target 开始搜索
        return ans  # 返回结果
