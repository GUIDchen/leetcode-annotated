// 题目：2200. 找出数组中的所有 K 近邻下标（Find All K-Distant Indices in an Array）
// 思路：对每个下标 i，再枚举下标 j，只要存在 |i-j| <= k 且 nums[j] == key 的 j，i 就是 K 近邻下标。
// 时间复杂度：O(n^2)，最坏情况每个 i 都要扫一遍 j；空间复杂度：O(1)，除答案数组外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {  // nums：输入数组；key：目标值；k：距离上限
        int n = nums.size();  // 数组长度，下面两重循环都用到
        vector<int> ans;  // 收集所有满足条件的下标
        for (int i = 0; i < n; ++i) {  // 枚举候选下标 i
            for (int j = 0; j < n; ++j) {  // 为 i 找一个附近的下标 j
                if (abs(i - j) <= k && nums[j] == key) {  // 距离不超过 k 且 nums[j] 等于 key，则 i 是 K 近邻下标
                    ans.push_back(i);  // 记录下标 i
                    break;  // 已经满足条件，不必再为这个 i 继续找 j
                }  // 结束 if
            }  // 结束内层 for
        }  // 结束外层 for
        return ans;  // 返回按升序收集到的下标
    }  // 结束方法
};  // 结束 Solution 类