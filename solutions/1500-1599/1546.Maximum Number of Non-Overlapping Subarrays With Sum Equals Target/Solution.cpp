// 题目：1546. 和为目标值且不重叠的非空子数组的最大数目（Maximum Number of Non-Overlapping Subarrays With Sum Equals Target）
// 思路：贪心，从当前起点向后累加前缀和，一旦发现 s - target 出现过就立即截下一段并跳出，越早截断留给后面的空间越大。
// 时间复杂度：O(n)，每个下标只被内层循环推进一次；空间复杂度：O(n)，哈希集合存前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxNonOverlapping(vector<int>& nums, int target) {  // nums：输入数组；target：目标子数组和
        int ans = 0, n = nums.size();  // ans 记录能截出的子数组个数，n 是数组长度
        for (int i = 0; i < n; ++i) {  // 外层循环：i 始终指向当前尚未使用的起始下标
            unordered_set<int> vis{{0}};  // 每一段单独开一个集合保存出现过的前缀和，预先放入 0 表示空前缀
            int s = 0;  // s 是从 i 开始这一段内的局部前缀和
            while (i < n) {  // 内层循环：从 i 向后累加，找一段和为 target 的子数组
                s += nums[i];  // 累加当前元素
                if (vis.count(s - target)) {  // s - target 出现过，说明中间那一段的和正好等于 target
                    ++ans;  // 找到一个合法子数组，答案加 1
                    break;  // 立刻结束本段，下一段从 i+1 开始，从而保证各段互不重叠
                }
                ++i;  // 这一段还没凑出 target，继续右移
                vis.insert(s);  // 记下这个前缀和，供后面的位置判断
            }
        }
        return ans;  // 返回最多能截出的子数组数目
    }
};