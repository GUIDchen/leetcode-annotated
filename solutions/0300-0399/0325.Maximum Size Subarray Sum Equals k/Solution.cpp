// 题目：325. 和等于 k 的最长子数组长度（Maximum Size Subarray Sum Equals k）
// 思路：用前缀和把子数组和转成两个前缀和之差，哈希表记录每个前缀和最早出现的下标，从而一次遍历求最长长度。
// 时间复杂度：O(n)，每个元素只处理一次；空间复杂度：O(n)，哈希表最多存 n+1 个前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSubArrayLen(vector<int>& nums, int k) {  // nums：整数数组；k：目标和；返回和等于 k 的最长子数组长度
        unordered_map<long long, int> d{{0, -1}};  // 哈希表「前缀和 → 最早出现的下标」，前缀和 0 的下标记作 -1（空前缀）
        int ans = 0;  // 记录最长长度，初始 0 表示还没找到合法子数组
        long long s = 0;  // 滚动前缀和，用 long long 防止累加溢出
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右扫描数组
            s += nums[i];  // 累加当前元素，得到 s = nums[0..i] 的和
            if (d.count(s - k)) {  // 若存在前缀和 s-k，说明两者之间的那段区间和正好是 k
                ans = max(ans, i - d[s - k]);  // 用区间长度 i - d[s-k] 去更新最大值
            }  // 分支结束
            if (!d.count(s)) {  // 只记录前缀和第一次出现的位置，下标越早越有利于取更长的区间
                d[s] = i;  // 首次出现，记下当前下标
            }  // 分支结束
        }  // 扫描结束
        return ans;  // 返回最长长度，找不到时为 0
    }  // 方法结束
};  // 类定义结束