// 题目：78. 子集（Subsets）
// 思路：回溯 + 每个元素「选或不选」。先递归处理「不选 nums[i]」的分支，再把 nums[i] 加入路径 t 递归处理另一个分支，叶子即一个子集。
// 时间复杂度：O(n * 2^n)，共 2^n 个子集、每个子集拷贝 O(n) 个元素；空间复杂度：O(n)，递归栈与路径数组的深度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> subsets(vector<int>& nums) {  // nums 是不含重复元素的数组，要求返回它的全部子集
        vector<vector<int>> ans;  // 收集所有子集
        vector<int> t;  // 当前正在构造的子集（回溯路径）
        function<void(int)> dfs = [&](int i) -> void {  // 递归 lambda：i 是当前要决定「选不选」的下标，[&] 按引用捕获外部变量
            if (i == nums.size()) {  // 所有元素都决策完毕，当前路径就是一个完整子集
                ans.push_back(t);  // 把这份子集拷贝进答案（必须拷贝，因为 t 之后还会被修改）
                return;  // 到达叶子，回溯返回
            }
            dfs(i + 1);  // 分支一：不选 nums[i]，直接处理下一个下标
            t.push_back(nums[i]);  // 分支二：把 nums[i] 加入当前子集
            dfs(i + 1);  // 带着这个选择递归处理下一个下标
            t.pop_back();  // 撤销选择、恢复现场，保证回到上一层时路径状态正确
        };
        dfs(0);  // 从下标 0 开始做「选或不选」的决策
        return ans;  // 返回收集到的全部子集
    }
};