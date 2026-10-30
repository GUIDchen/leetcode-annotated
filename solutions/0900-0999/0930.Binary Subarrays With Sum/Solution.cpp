// 题目：930. 和相同的二元子数组（Binary Subarrays With Sum）
// 思路：前缀和 + 计数表。以当前下标结尾、和为 goal 的子数组个数，等于前缀和 s-goal 在此前出现的次数。
// 时间复杂度：O(n)，只需一趟遍历；空间复杂度：O(n)，计数表长度与前缀和的取值范围相同。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numSubarraysWithSum(vector<int>& nums, int goal) {  // nums 只含 0/1；goal 是目标和，返回和恰好为 goal 的子数组个数
        int cnt[nums.size() + 1];  // cnt[s]：前缀和 s 之前出现过的次数，下标范围 0..n
        memset(cnt, 0, sizeof cnt);  // 全部清零，n 个元素最多产生 n+1 种前缀和
        cnt[0] = 1;  // 空前缀的前缀和是 0，视作已经出现过 1 次
        int ans = 0, s = 0;  // ans 累加答案；s 是当前前缀和
        for (int& v : nums) {  // 顺序遍历数组
            s += v;  // 累加得到当前位置的前缀和
            if (s - goal >= 0) {  // 只有非负的前缀和才在 cnt 的有效下标范围内
                ans += cnt[s - goal];  // 此前出现过多少次前缀和 s-goal，就有多少个以当前下标结尾的合法子数组
            }
            ++cnt[s];  // 把当前前缀和计入次数，供后面的元素查询
        }
        return ans;  // 返回满足条件的子数组总数
    }
};