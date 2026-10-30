// 题目：1852. 每个子数组的数字种类数（Distinct Numbers in Each Subarray）
// 思路：固定长度 k 的滑动窗口，用哈希表维护窗口内各数字的出现次数，表的大小就是不同数字的个数。
// 时间复杂度：O(n)，每个元素进出窗口各一次，均摊 O(1)；空间复杂度：O(k)，哈希表最多存 k 个不同数字。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> distinctNumbers(vector<int>& nums, int k) {  // nums：输入数组；k：子数组长度
        unordered_map<int, int> cnt;  // 哈希表：数字 -> 它在当前窗口内出现的次数
        for (int i = 0; i < k; ++i) {  // 先把第一个窗口（下标 0..k-1）填进哈希表
            ++cnt[nums[i]];  // 对应数字的计数加一
        }  // 结束 for
        int n = nums.size();  // 数组长度
        vector<int> ans;  // 存放每个窗口的不同数字个数
        ans.push_back(cnt.size());  // 第一个窗口的答案就是哈希表的大小
        for (int i = k; i < n; ++i) {  // 窗口右端从 k 开始右移，每次进入一个新元素、移出一个旧元素
            ++cnt[nums[i]];  // 新元素进入窗口，计数加一
            if (--cnt[nums[i - k]] == 0) {  // 旧元素离开窗口：先减计数，减到 0 说明它在窗口里彻底消失了
                cnt.erase(nums[i - k]);  // 计数归零的键必须删掉，否则 size() 会把 0 次的数字也算进种类数
            }  // 结束 if
            ans.push_back(cnt.size());  // 记录当前窗口的种类数
        }  // 结束 for
        return ans;  // 返回所有窗口的答案
    }  // 结束 distinctNumbers
};  // 结束 Solution 类