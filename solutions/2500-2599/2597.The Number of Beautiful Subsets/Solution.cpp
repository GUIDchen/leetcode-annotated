// 题目：2597. 美丽子集的数目（The Number of Beautiful Subsets）
// 思路：回溯枚举「选 / 不选」每个元素，用值域桶 cnt 记录当前子集里的值，选 nums[i] 前检查 nums[i]±k 是否已出现。
// 时间复杂度：O(2^n)，最坏枚举全部子集；空间复杂度：O(n + V)，递归深度 n、桶数组大小 V（值域上界 1010）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int beautifulSubsets(vector<int>& nums, int k) {  // nums：候选数字；k：允许的最小差值；返回美丽子集（任意两数之差不等于 k）的个数
        int ans = -1;  // 计数从 -1 起，用来抵消递归中把空子集也记上的那一次
        int cnt[1010]{};  // 值域桶：cnt[v] 表示值 v 在当前子集中出现的次数，值为 0 时表示未选
        int n = nums.size();  // 元素个数，作为递归的下标上界

        // 下面这个 lambda 是回溯主体：先用分支一「不选」，再尝试分支二「选」
        auto dfs = [&](this auto&& dfs, int i) {  // C++23 显式对象参数写法，让 lambda 能递归调用自己；i 是当前决策的下标
            if (i >= n) {  // 所有元素都决策完了，说明当前子集合法
                ++ans;  // 子集个数加一（空集也会在这里被计一次，最后由 ans 初值扣掉）
                return;  // 本分支结束，回溯返回上一层
            }  // 越界判断结束
            dfs(i + 1);  // 分支一：不把 nums[i] 放进子集，直接处理下一个元素
            bool ok1 = nums[i] + k >= 1010 || cnt[nums[i] + k] == 0;  // 选 nums[i] 后不能已存在 nums[i]+k；下标越过桶上界视为该值不存在
            bool ok2 = nums[i] - k < 0 || cnt[nums[i] - k] == 0;  // 同理不能已存在 nums[i]-k；负下标不可能被记录，直接视为不存在
            if (ok1 && ok2) {  // 两个方向都不冲突，当前元素才能被选入
                ++cnt[nums[i]];  // 把 nums[i] 计入当前子集（桶计数加一）
                dfs(i + 1);  // 分支二：选了 nums[i] 后继续决策后续元素
                --cnt[nums[i]];  // 回溯：撤销本次选择，保证兄弟分支看到的是干净状态
            }  // 选入分支结束
        };  // lambda 定义结束
        dfs(0);  // 从下标 0 开始搜索
        return ans;  // ans 已扣掉空子集，直接返回美丽子集个数
    }
};
