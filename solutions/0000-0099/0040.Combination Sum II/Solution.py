# 题目：40. 组合总和 II（Combination Sum II）
# 思路：排序后回溯：每个数只能用一次（递归传 j+1），同一层相邻的重复值只取第一个，既避免重复组合又允许不同层使用相同值。
# 时间复杂度：与解的个数相关，最坏 O(2^n)；空间复杂度：O(n)，递归深度即路径长度。
class Solution:  # LeetCode 约定的题解类
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:  # candidates 可能含重复值且每个数只能用一次，target 是目标和；返回所有不重复的组合
        def dfs(i: int, s: int):  # 内部回溯函数：i 是本次可选的最小下标，s 是剩余和
            if s == 0:  # 剩余和凑到 0，说明当前路径是一个解
                ans.append(t[:])  # t[:] 存入拷贝，防止后续增删 t 破坏已保存的答案
                return  # 返回上一层继续搜索
            if i >= len(candidates) or s < candidates[i]:  # 下标越界或剩余和小于最小值，都无法再凑出 target
                return  # 剪枝返回
            for j in range(i, len(candidates)):  # 从 i 开始枚举本层可选位置
                if j > i and candidates[j] == candidates[j - 1]:  # 同一层出现与前一个数相同的值时，只保留第一个分支
                    continue  # 跳过其余重复分支，避免产生重复组合
                t.append(candidates[j])  # 做选择：把当前数加入路径
                dfs(j + 1, s - candidates[j])  # 递归传 j+1，因为每个数只能用一次，下一层从它的下一个位置开始
                t.pop()  # 撤销选择，恢复路径

        candidates.sort()  # 排序让相同数值相邻（跳重的前提），也让剪枝条件成立
        ans = []  # 收集所有合法组合
        t = []  # 当前搜索路径
        dfs(0, target)  # 从下标 0、剩余和 target 开始搜索
        return ans  # 返回结果
