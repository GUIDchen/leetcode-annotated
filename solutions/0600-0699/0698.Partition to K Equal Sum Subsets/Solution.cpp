// 题目：698. 划分为k个相等的子集（Partition to K Equal Sum Subsets）
// 思路：先算出目标和 sum/k，再把元素从大到小依次放进 k 个桶里做回溯；跳过与上一个桶剩余值相同的桶来剪枝，任一方案装满所有桶即成功。
// 时间复杂度：O(k^n) 量级（回溯最坏情况，实际被排序与同值剪枝大幅削减）；空间复杂度：O(n + k)，递归栈与桶数组的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canPartitionKSubsets(vector<int>& nums, int k) {  // nums 是候选数字，k 是子集个数
        int s = accumulate(nums.begin(), nums.end(), 0);  // 先求出全部元素的总和
        if (s % k) {  // 总和不能被 k 整除时，不可能均分成 k 份
            return false;  // 直接返回不可能
        }
        s /= k;  // 每个子集的目标和
        int n = nums.size();  // 元素个数，供递归终止判断使用
        vector<int> cur(k);  // cur[j] 表示第 j 个桶当前已装的元素之和
        function<bool(int)> dfs = [&](int i) {  // 递归函数：尝试把第 i 个元素放进某个桶
            if (i == n) {  // 所有元素都成功放置
                return true;  // 找到一种合法划分
            }
            for (int j = 0; j < k; ++j) {  // 依次尝试放进每一个桶
                if (j && cur[j] == cur[j - 1]) {  // 若与上一个桶当前和相同，放哪个都一样，跳过以剪枝
                    continue;  // 跳过重复状态的桶
                }
                cur[j] += nums[i];  // 先把当前元素放进第 j 个桶
                if (cur[j] <= s && dfs(i + 1)) {  // 桶内和不超过目标和，且后续元素也能放下
                    return true;  // 该方案可行，向上传递成功
                }
                cur[j] -= nums[i];  // 撤销放置，回溯尝试下一个桶
            }
            return false;  // 所有桶都试过仍不成，说明此前的选择走不通
        };
        sort(nums.begin(), nums.end(), greater<int>());  // 从大到小排序：先放大元素能更快触发剪枝
        return dfs(0);  // 从第 0 个元素开始尝试填桶
    }
};
