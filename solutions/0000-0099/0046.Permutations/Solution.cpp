// 题目：46. 全排列（Permutations）
// 核心思路：回溯。逐位填 t[i]，用 vis 标记已选元素；填满 n 位就收集一个排列，然后撤销标记继续尝试其他分支。
// 时间复杂度：O(n·n!)，共 n! 个排列、每个拷贝 O(n)；空间复杂度：O(n)，vis、t 与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> permute(vector<int>& nums) {  // nums 是互不相同的整数数组，返回它的所有全排列
        int n = nums.size();  // 元素个数，也就是每个排列的长度
        vector<vector<int>> ans;  // 收集所有排列结果
        vector<int> t(n);  // 当前正在构造的排列，长度固定为 n
        vector<bool> vis(n);  // vis[j] 标记 nums[j] 是否已经被放进当前排列
        auto dfs = [&](this auto&& dfs, int i) -> void {  // 显式对象参数让 lambda 能递归调用自身；i 是当前要填的位置
            if (i == n) {  // n 个位置都填好了，得到一个完整的排列
                ans.emplace_back(t);  // 把当前排列拷贝进答案
                return;  // 回溯返回上一层
            }
            for (int j = 0; j < n; ++j) {  // 尝试把每个还没用过的数放到位置 i
                if (!vis[j]) {  // 只有没被用过的元素才可以选
                    vis[j] = true;  // 标记为已使用，避免同一个排列里重复选它
                    t[i] = nums[j];  // 把 nums[j] 放到第 i 个位置
                    dfs(i + 1);  // 递归去填下一个位置
                    vis[j] = false;  // 回溯：撤销使用标记，让后面的分支还能选它
                }
            }
        };
        dfs(0);  // 从第 0 个位置开始构造排列
        return ans;  // 返回全部全排列
    }
};
