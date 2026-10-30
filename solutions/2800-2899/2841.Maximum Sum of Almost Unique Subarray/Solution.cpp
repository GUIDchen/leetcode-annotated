// 题目：2841. 几乎唯一子数组的最大和（Maximum Sum of Almost Unique Subarray）
// 思路：定长滑动窗口。用哈希表维护窗口内元素频次，当不同元素个数不少于 m 时用窗口和更新答案，窗口每次右移一格。
// 时间复杂度：O(n)，每个元素至多进出窗口一次；空间复杂度：O(k)，哈希表最多保存窗口内 k 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxSum(vector<int>& nums, int m, int k) {  // nums 是数组，m 是不同元素个数下限，k 是子数组长度
        unordered_map<int, int> cnt;  // 记录当前窗口内每个元素的出现次数
        long long s = 0;  // 当前窗口内所有元素之和
        int n = nums.size();  // 数组长度
        for (int i = 0; i < k; ++i) {  // 先构造第一个长度为 k 的窗口
            cnt[nums[i]]++;  // 元素进入窗口，计数加 1
            s += nums[i];  // 累加窗口和
        }
        long long ans = cnt.size() >= m ? s : 0;  // 第一个窗口达标就先作为候选答案，否则保持 0
        for (int i = k; i < n; ++i) {  // 窗口右移：新进 nums[i]，移出 nums[i - k]
            cnt[nums[i]]++;  // 新元素加入窗口
            if (--cnt[nums[i - k]] == 0) {  // 移出的元素计数减 1，减到 0 说明窗口内已经没有它
                cnt.erase(nums[i - k]);  // 删除这个键，使 cnt.size() 恰好等于不同元素个数
            }
            s += nums[i] - nums[i - k];  // 用进出的差值更新窗口和，避免重新求和
            if (cnt.size() >= m) {  // 不同元素个数达到下限，窗口合法
                ans = max(ans, s);  // 尝试用更大的窗口和更新答案
            }
        }
        return ans;  // 返回最大窗口和；没有合法子数组时仍为 0
    }
};