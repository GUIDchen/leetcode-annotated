// 题目：40. 组合总和 II（Combination Sum II）
// 思路：排序后回溯：每个数只能用一次（递归传 j+1），同层相邻的重复值只取第一个，从而既保证不重复、又允许不同层使用相同的值。
// 时间复杂度：与解的个数相关，最坏 O(2^n)；空间复杂度：O(n)，递归深度与路径长度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {  // candidates 中可能含重复值且每个数只能用一次，target 是目标和；返回所有不重复的组合
        sort(candidates.begin(), candidates.end());  // 排序让相同数值相邻，既方便跳重，也让 s < candidates[i] 剪枝成立
        vector<vector<int>> ans;  // 收集所有合法组合
        vector<int> t;  // 当前搜索路径
        function<void(int, int)> dfs = [&](int i, int s) {  // 回溯函数：i 是本次可选的最小下标，s 是剩余和；std::function 支持自我递归
            if (s == 0) {  // 剩余和凑到 0，说明当前路径是一个解
                ans.emplace_back(t);  // 把路径拷贝存入答案（t 之后还会被修改）
                return;  // 返回上一层继续搜索
            }  // if (s == 0) 结束
            if (i >= candidates.size() || s < candidates[i]) {  // 下标越界或剩余和已小于最小值，都无法再凑出 target
                return;  // 剪枝返回
            }  // if 剪枝结束
            for (int j = i; j < candidates.size(); ++j) {  // 从 i 开始枚举本层可选的位置
                if (j > i && candidates[j] == candidates[j - 1]) {  // 同一层里若出现与前一个数相同的值，只保留第一个分支
                    continue;  // 直接跳过，避免生成重复组合
                }  // if 跳重结束
                t.emplace_back(candidates[j]);  // 做选择：把当前数加入路径
                dfs(j + 1, s - candidates[j]);  // 递归传 j+1，因为每个数只能用一次，下一层从它的下一个位置开始
                t.pop_back();  // 撤销选择，恢复路径
            }  // for 结束
        };  // lambda 定义结束
        dfs(0, target);  // 从下标 0、剩余和 target 开始搜索
        return ans;  // 返回所有组合
    }  // 方法结束
};  // 类定义结束
