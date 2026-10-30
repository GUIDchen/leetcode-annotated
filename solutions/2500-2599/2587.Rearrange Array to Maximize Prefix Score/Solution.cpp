// 题目：2587. 重排数组以得到最大前缀分数（Rearrange Array to Maximize Prefix Score）
// 思路：前缀和要尽量大，应把大正数排在前面，因此降序排序后逐个累加；一旦前缀和 <= 0，后续只会更小，直接返回已统计的个数。
// 时间复杂度：O(n log n)，排序开销；空间复杂度：O(log n)，排序所需的递归栈（原地排序）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxScore(vector<int>& nums) {  // nums 为可任意重排的数组；返回正前缀和的最大个数
        sort(nums.rbegin(), nums.rend());  // 降序排序，让大的正数排在前面以最大化前缀和
        long long s = 0;  // 当前前缀和，用 long long 防止累加溢出 int
        int n = nums.size();  // 数组长度
        for (int i = 0; i < n; ++i) {  // 从头开始累加前缀和
            s += nums[i];  // 把当前元素并入前缀和
            if (s <= 0) {  // 前缀和非正，之后的元素更小，前缀和不可能再变正
                return i;  // 前面 i 个前缀都是正的，所以得分是 i
            }
        }
        return n;  // 所有前缀都为正，得分为数组长度
    }
};