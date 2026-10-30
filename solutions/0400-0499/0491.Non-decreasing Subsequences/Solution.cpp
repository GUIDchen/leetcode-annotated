// 题目：491. 非递减子序列（Non-decreasing Subsequences）
// 思路：按下标回溯，每个元素分「选」与「不选」两支；选的前提是它不小于已选序列的最后一个值 last，不选时若它与 last 相同则跳过，以此消除同一层重复元素带来的重复子序列。
// 时间复杂度：O(n·2ⁿ)，每个下标两种决策、每个合法子序列拷贝 O(n)；空间复杂度：O(n)，递归深度与路径数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> findSubsequences(vector<int>& nums) {  // nums：可能含重复元素的数组；返回所有长度 ≥ 2 的非递减子序列
        vector<vector<int>> ans;  // 收集所有合法的非递减子序列
        vector<int> t;  // 回溯过程中的当前子序列（即决策路径）
        dfs(0, -1000, t, nums, ans);  // 从下标 0 开始搜；last 取 -1000 充当 -∞（题目元素值 ≥ -100）
        return ans;  // 返回全部结果
    }  // 方法结束

    void dfs(int u, int last, vector<int>& t, vector<int>& nums, vector<vector<int>>& ans) {  // u：当前处理的下标；last：已选子序列的最后一个值；t：当前路径；ans：结果集
        if (u == nums.size()) {  // 已经走到数组末尾，一条完整的决策链结束
            if (t.size() > 1) ans.push_back(t);  // 长度至少为 2 才符合「子序列」要求，才放进答案
            return;  // 到达出口，返回上一层继续做别的决策
        }  // 出口分支结束
        if (nums[u] >= last) {  // 选 nums[u]：只有它不小于 last，选完才仍是非递减的
            t.push_back(nums[u]);  // 把当前值加入路径
            dfs(u + 1, nums[u], t, nums, ans);  // 带着新的 last 继续处理下一个下标
            t.pop_back();  // 回溯：撤销刚才的选择，恢复路径以便尝试其他分支
        }  // 「选」的分支结束
        if (nums[u] != last) dfs(u + 1, last, t, nums, ans);  // 「不选」的分支：若 nums[u] 与 last 相同，这一支会与上面重复，故直接跳过
    }  // dfs 结束
};  // 类定义结束