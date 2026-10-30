// 题目：1658. 将 x 减到 0 的最小操作数（Minimum Operations to Reduce X to Zero）
// 思路：把「删两端」等价转换为「保留中间一段连续子数组」，其和应为 sum - x；用哈希表存前缀和最早下标求最长窗口。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(n)，哈希表最多存 n 个前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums, int x) {  // nums：输入数组；x：要让被删除元素之和恰好等于的目标值
        int s = accumulate(nums.begin(), nums.end(), 0) - x;  // 总和减 x 得到「中间保留段」应有的和 s：删两端等价于留中间一段
        unordered_map<int, int> vis = {{0, -1}};  // 前缀和 → 最早下标；哨兵 {0, -1} 表示空前缀和
        int mx = -1, t = 0;  // mx 记录保留段的最长长度，t 是滚动前缀和
        int n = nums.size();  // 数组长度，后面多次用到
        for (int i = 0; i < n; ++i) {  // 枚举保留段的右端点
            t += nums[i];  // 累加前缀和
            if (!vis.contains(t)) {  // 每个前缀和只记第一次出现的位置，位置越靠左、窗口越长
                vis[t] = i;  // 记下前缀和 t 的最早下标
            }  // if 块结束
            if (vis.contains(t - s)) {  // 若前缀和 t - s 出现过，说明存在和为 s 的连续子数组
                mx = max(mx, i - vis[t - s]);  // 用窗口长度 i - vis[t - s] 更新最长保留段
            }  // 内层 if 结束
        }  // for 循环结束
        return mx == -1 ? -1 : n - mx;  // mx 为 -1 表示无解；否则总长减去保留段长就是从两端删除的次数
    }  // 方法结束
};  // 类定义结束