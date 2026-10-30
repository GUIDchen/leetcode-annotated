// 3430. Maximum and Minimum Sums of at Most Size K Subarrays / 3430. 最多 K 个元素的子数组的最值之和
// 核心思路：滑动窗口 + 两套单调栈，用份额（shares）维护窗口内所有子数组的最大值之和与最小值之和。
// 复杂度：时间 O(n)，空间 O(n)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 判题器调用的公有方法
    long long minMaxSubarraySum(vector<int>& nums, int k) {  // 返回所有长度不超过 k 的子数组中最大值之和与最小值之和的总和
        long long totalMaxMinSum = 0;  // 累计所有子数组的最大值与最小值总和
        long long windowMaxSum = 0, windowMinSum = 0;  // 当前窗口内所有子数组的最大值之和与最小值之和

        // Format: {idx, num, shares}. Use long long to prevent overflow.
        deque<tuple<int, int, long long>> maxStack, minStack;  // 最大栈与最小栈：元素为 (下标, 数值, 该数值作为最值的子数组个数)

        for (int endIdx = 0; endIdx < nums.size(); endIdx++) {  // 枚举窗口右端点 endIdx
            int startIdx = max(0, endIdx - k + 1);  // 当前窗口左端点下界，保证窗口长度不超过 k

            // Window start idx slides by 1: must update stacks' info.
            if (startIdx > 0) {  // 窗口左端点右移一位，需要同步修正两个栈的栈首份额与和值
                get<2>(maxStack.front())--; // Decrement stack's front num shares.  栈首数值的份额减一，表示少了一个以它为最值的子数组
                windowMaxSum -= get<1>(maxStack.front());  // 该次贡献消失，最大值之和减去栈首数值

                // Front num out of window.
                if (get<0>(maxStack.front()) < startIdx)  // 最大栈栈首下标已经滑出窗口
                    maxStack.pop_front();  // 弹出最大栈栈首，保证栈内下标有效

                get<2>(minStack.front())--; // Decrement stack's front num shares.  最小栈栈首份额同样减一
                windowMinSum -= get<1>(minStack.front());  // 最小值之和减去栈首数值

                // Front num out of window.
                if (get<0>(minStack.front()) < startIdx)  // 最小栈栈首下标已经滑出窗口
                    minStack.pop_front();  // 弹出最小栈栈首
            }

            long long num = nums[endIdx];  // 当前并入窗口的元素

            long long maxShares = 1; // Base case.  新元素自身至少覆盖一个子数组
            windowMaxSum += num;  // 先把它自己作为一个子数组的最大值计入

            while (!maxStack.empty() && get<1>(maxStack.back()) <= num) {  // 维护最大值栈的单调递减性：栈尾数值不大于当前值就合并
                int prevNum = get<1>(maxStack.back());  // 取出栈尾数值
                long long prevShares = get<2>(maxStack.back());  // 取出栈尾数值的份额
                maxStack.pop_back();  // 弹出栈尾，其份额转移给当前值

                maxShares += prevShares; // Max shares transition.  被合并的份额累加到当前数值上

                // Reflect transition in max sum.
                windowMaxSum += (num - prevNum) * prevShares;  // 最值从 prevNum 换成 num，最大值之和增加 (num - prevNum) * prevShares
            }

            maxStack.push_back({endIdx, num, maxShares});  // 把当前数值按合并后的份额压入最大值栈

            long long minShares = 1; // Base case.  新元素自身至少覆盖一个子数组
            windowMinSum += num;  // 先把它自己作为一个子数组的最小值计入

            while (!minStack.empty() && get<1>(minStack.back()) >= num) {  // 维护最小值栈的单调递增性：栈尾数值不小于当前值就合并
                int prevNum = get<1>(minStack.back());  // 取出栈尾数值
                long long prevShares = get<2>(minStack.back());  // 取出栈尾数值的份额
                minStack.pop_back();  // 弹出栈尾，其份额转移给当前值

                minShares += prevShares; // Min shares transition.  被合并的份额累加到当前数值上

                // Reflect transition in min sum.
                windowMinSum += (num - prevNum) * prevShares;  // 最小值从 prevNum 换成 num，最小值之和增加 (num - prevNum) * prevShares
            }

            minStack.push_back({endIdx, num, minShares});  // 把当前数值按合并后的份额压入最小值栈

            totalMaxMinSum += windowMaxSum + windowMinSum;  // 右端点固定时，窗口内所有合法子数组的最值之和累加进答案
        }  // 窗口右端点后移，进入下一轮

        return totalMaxMinSum;  // 返回所有长度不超过 k 的子数组的最值总和
    }  // 方法结束
};  // 类定义结束