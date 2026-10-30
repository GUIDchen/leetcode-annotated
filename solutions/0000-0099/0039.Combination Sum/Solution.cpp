// 题目：39. 组合总和（Combination Sum）
// 思路：先排序，再回溯枚举：每层从下标 i 开始选数（保证组合不重复、且允许重复选同一数），剩余和减到 0 就收集答案，剩余和小于当前最小值就剪枝。
// 时间复杂度：O(n · 2^t) 量级（与解的个数相关，t 为目标值与最小值之比）；空间复杂度：O(t)，递归深度与路径长度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {  // candidates 是可重复选取的正整数数组，target 是目标和；返回所有和为 target 的组合
        sort(candidates.begin(), candidates.end());  // 排序是为了让数组递增，后面才能用 s < candidates[i] 做剪枝
        vector<vector<int>> ans;  // ans 收集所有合法组合
        vector<int> t;  // t 是当前搜索路径上的组合，做选择/撤销选择时反复增删
        function<void(int, int)> dfs = [&](int i, int s) {  // 回溯函数：i 是本次可选的最小下标，s 是还差多少和；用 std::function 包起来才能自我递归
            if (s == 0) {  // 剩余和为 0，说明当前路径正好凑成 target
                ans.emplace_back(t);  // 把当前路径的拷贝存进答案（必须拷贝，因为 t 后面还会被修改）
                return;  // 这条分支结束，返回上一层
            }  // if (s == 0) 结束
            if (s < candidates[i]) {  // 剩余和比当前能选的最小数还小，后面再选任何数都只会更小
                return;  // 直接剪枝返回，避免无意义的深搜
            }  // if 剪枝结束
            for (int j = i; j < candidates.size(); ++j) {  // 从 i 开始枚举本层可选的数，i 保证了组合按非递减顺序生成、不会重复
                t.push_back(candidates[j]);  // 做选择：把当前数加入路径
                dfs(j, s - candidates[j]);  // 递归时仍传 j（而不是 j+1），表示同一个数可以被重复选取
                t.pop_back();  // 撤销选择，把路径恢复原状，供下一个分支使用
            }  // for 结束
        };  // lambda 定义结束
        dfs(0, target);  // 从下标 0、剩余和 target 开始搜索
        return ans;  // 返回所有收集到的组合
    }  // 方法结束
};  // 类定义结束
