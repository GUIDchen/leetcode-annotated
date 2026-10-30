// 题目：3171. 找到按位或最接近 K 的子数组（Find Subarray With Bitwise OR Closest to K）
// 思路：固定右端点时，子数组的按位或随着左端点右移只会变小（单调不增），因此可以用滑动窗口：窗口或 s 大于 k 时不断右移左端点尝试逼近，并用按位计数 cnt 在 O(位宽) 内撤销被移出元素的贡献。
// 时间复杂度：O(n log A)，A 是数组中最大值，最多 31 位；空间复杂度：O(log A)，cnt 数组长度等于位宽。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumDifference(vector<int>& nums, int k) {  // nums 是非负整数数组，k 是目标值，返回任意子数组按位或与 k 的差值绝对值的最小值
        int mx = *max_element(nums.begin(), nums.end());  // 数组最大值，用来确定需要关心多少二进制位（更高位全是 0，不必统计）
        int m = 32 - __builtin_clz(mx);  // __builtin_clz 统计前导零个数，32 减去它就是 mx 的有效二进制位数
        int n = nums.size();  // 数组长度
        int ans = INT_MAX;  // 答案初始化为最大整数，后面不断取 min 缩小
        vector<int> cnt(m);  // cnt[h] 记录窗口内第 h 位为 1 的元素个数，用于判断某位在移出元素后是否清零
        for (int i = 0, j = 0, s = 0; j < n; ++j) {  // i 是窗口左端点，j 是窗口右端点，s 是窗口 [i..j] 内所有元素的按位或
            s |= nums[j];  // 把新元素并入窗口，或运算只会让 1 变多，不会变少
            ans = min(ans, abs(s - k));  // 用当前窗口的或值与 k 的差距更新答案
            for (int h = 0; h < m; ++h) {  // 逐位统计新元素对窗口的贡献
                if (nums[j] >> h & 1) {  // 只有第 h 位为 1 才需要计数
                    ++cnt[h];  // 该位计数加一
                }
            }
            while (i < j && s > k) {  // 或值大于 k 时右移左端点能让或值变小，借此向 k 靠近
                for (int h = 0; h < m; ++h) {  // 逐位撤销左端点 nums[i] 的贡献
                    if (nums[i] >> h & 1 && --cnt[h] == 0) {  // 该位原本为 1，减一后计数为 0 说明窗口内已没有数在该位为 1
                        s ^= 1 << h;  // 用异或把这一位从 s 中清掉
                    }
                }
                ans = min(ans, abs(s - k));  // 收缩一次后再次尝试更新答案
                ++i;  // 左端点右移，窗口缩小
            }
        }
        return ans;  // 返回所有子数组或值与 k 的最小差值
    }
};