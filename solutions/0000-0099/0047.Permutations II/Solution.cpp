// 题目：47. 全排列 II（Permutations II）
// 核心思路：先排序让相同元素相邻；回溯时若 nums[j] 与前一元素相同且前一元素本轮未被使用，说明会产生重复排列，直接剪枝。
// 时间复杂度：O(n·n!)，最坏仍要遍历排列；空间复杂度：O(n)，vis、t 与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> permuteUnique(vector<int>& nums) {  // nums 可能含重复元素，返回所有不重复的全排列
        ranges::sort(nums);  // 用 C++20 ranges 排序：把相同元素排到一起，便于后面剪枝
        int n = nums.size();  // 元素个数，也就是每个排列的长度
        vector<vector<int>> ans;  // 收集所有不重复的排列
        vector<int> t(n);  // 当前正在构造的排列，长度固定为 n
        vector<bool> vis(n);  // vis[j] 标记 nums[j] 是否已经被放进当前排列
        auto dfs = [&](this auto&& dfs, int i) {  // 显式对象参数让 lambda 能递归调用自身；i 是当前要填的位置
            if (i == n) {  // n 个位置都填好了，得到一个完整的排列
                ans.emplace_back(t);  // 把当前排列拷贝进答案
                return;  // 回溯返回上一层
            }
            for (int j = 0; j < n; ++j) {  // 尝试把每个还没用过的数放到位置 i
                if (vis[j] || (j && nums[j] == nums[j - 1] && !vis[j - 1])) {  // 已用过，或与前一相同数且前一数本轮未使用，就会产生重复排列
                    continue;  // 剪枝跳过这一支，避免同一排列被收集多次
                }
                t[i] = nums[j];  // 把 nums[j] 放到第 i 个位置
                vis[j] = true;  // 标记为已使用，避免同一个排列里重复选它
                dfs(i + 1);  // 递归去填下一个位置
                vis[j] = false;  // 回溯：撤销使用标记，让后面的分支还能选它
            }
        };
        dfs(0);  // 从第 0 个位置开始构造排列
        return ans;  // 返回全部不重复的全排列
    }
};
