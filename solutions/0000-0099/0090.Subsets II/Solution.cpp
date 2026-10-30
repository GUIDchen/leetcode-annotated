// 题目：90. 子集 II（Subsets II）
// 思路：先排序让相同数字相邻，再回溯枚举「选 / 不选」；不选的分支里一次跳过所有相同值，从而去重。
// 时间复杂度：O(n·2^n)，共枚举 2^n 个子集、每个子集复制需 O(n)；空间复杂度：O(n)，递归栈与路径数组 t。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {  // nums 是可能含重复元素的数组，返回所有不重复子集
        ranges::sort(nums);  // C++20 ranges 版排序：把相同的数字聚到一起，去重才有依据
        vector<vector<int>> ans;  // 结果集：收集所有不重复的子集
        vector<int> t;  // 回溯路径：当前正在构造的子集
        int n = nums.size();  // 数组长度，供递归出口判断使用
        auto dfs = [&](this auto&& dfs, int i) {  // 泛型递归 lambda，this auto&& 让 lambda 能调用自身；i 为当前决策到的下标
            if (i >= n) {  // 所有元素都决策完毕，说明 t 已经是一个完整子集
                ans.push_back(t);  // 把当前路径作为答案收集起来
                return;  // 递归出口：回到上一层继续尝试其他分支
            }
            t.push_back(nums[i]);  // 分支一：把 nums[i] 选进当前子集
            dfs(i + 1);  // 选完之后继续决策下一个元素
            t.pop_back();  // 撤销选择、恢复现场，以便尝试「不选」的分支
            while (i + 1 < n && nums[i + 1] == nums[i]) {  // 分支二：不选 nums[i]，并把后面与它相等的值全部跨过
                ++i;  // 跳过重复值，保证同一层不会枚举出内容相同的子集
            }
            dfs(i + 1);  // 从重复段的最后一位之后继续递归
        };  // lambda 定义结束
        dfs(0);  // 从下标 0 开始回溯
        return ans;  // 返回所有不重复的子集
    }
};
