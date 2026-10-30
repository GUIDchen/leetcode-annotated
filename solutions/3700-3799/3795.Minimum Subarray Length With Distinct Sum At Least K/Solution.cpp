// 3795. 不同元素和至少为 K 的最短子数组长度 / Minimum Subarray Length With Distinct Sum At Least K
// 核心思路：滑动窗口维护窗口内不同元素之和，右端点扩张、和达到 k 时收缩左端点并更新最短长度。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // 定义 LeetCode 题解类
public:  // 公开接口
    int minLength(vector<int>& nums, int k) {  // 返回不同元素和至少为 k 的最短子数组长度
        int n = nums.size();  // 数组长度
        int ans = n + 1;  // 最短长度，先设为不可能的值
        unordered_map<int, int> cnt;  // 窗口内每个元素的出现次数
        int l = 0;  // 窗口左端点
        long long s = 0;  // 窗口内不同元素之和
        for (int r = 0; r < n; ++r) {  // 右端点向右扩展
            int x = nums[r];  // 当前进入窗口的元素
            if (++cnt[x] == 1) {  // 该元素在窗口内首次出现
                s += x;  // 把它的值计入不同元素之和
            }  // 结束首次出现判断
            while (s >= k) {  // 和已满足要求，尝试收缩窗口
                ans = min(ans, r - l + 1);  // 用当前窗口长度更新最短长度
                int y = nums[l];  // 即将移出窗口的左端点元素
                if (--cnt[y] == 0) {  // 该元素在窗口内的出现次数减为 0
                    s -= y;  // 从不同元素之和中扣除它的值
                }  // 结束消失判断
                ++l;  // 左端点右移
            }  // 结束收缩
        }  // 结束窗口遍历
        return ans > n ? -1 : ans;  // 没有满足条件的子数组则返回 -1
    }  // 结束函数
};  // 结束类
