// 题目：2393. 严格递增的子数组个数（Count Strictly Increasing Subarrays）
// 思路：cnt 表示以当前元素结尾的严格递增子数组个数，递增则 cnt+1，否则重置为 1，逐个累加。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用两个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countSubarrays(vector<int>& nums) {  // nums 是待统计数组；答案可能超过 int 范围，故用 long long
        long long ans = 1, cnt = 1;  // ans 统计子数组总数；cnt 表示以当前元素结尾的严格递增子数组个数
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始扫描（第一个元素自身单独构成一个子数组）
            if (nums[i - 1] < nums[i]) {  // 比前一个大，递增段可以继续延长
                ++cnt;  // 以 i 结尾的递增子数组个数等于前一个的个数再加 1
            } else {  // 否则递增段在此中断
                cnt = 1;  // 只能单独构成一个长度为 1 的子数组
            }  // if/else 结束
            ans += cnt;  // 累加以 i 结尾的全部严格递增子数组
        }  // 遍历结束
        return ans;  // 返回总数
    }  // 方法结束
};  // 题解类结束
