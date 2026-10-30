// 题目：2439. 最小化数组中的最大值（Minimize Maximum of Array）
// 思路：二分答案 mx，从右往左贪心，把 nums[i] 超过 mx 的部分向左传递，最后看 nums[0] 加上全部溢出量是否不超过 mx。
// 时间复杂度：O(n log max(nums))，二分 O(log max) 轮、每轮 O(n)；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimizeArrayValue(vector<int>& nums) {  // nums：非负整数数组，元素的值允许向左挪动
        int left = 0, right = *max_element(nums.begin(), nums.end());  // 二分区间：答案至少为 0，至多为数组当前最大值
        auto check = [&](int mx) {  // 判定函数：能否把数组调整成所有元素都不超过 mx
            long d = 0;  // d 记录从右侧溢出、需要继续向左传递的数值总量
            for (int i = nums.size() - 1; i; --i) {  // 从最后一个元素倒着处理到下标 1（下标 0 留给最后判断）
                d = max(0l, d + nums[i] - mx);  // 当前元素加上此前的溢出量，超出 mx 的部分继续左传，不足则清零
            }  // 倒序循环结束
            return nums[0] + d <= mx;  // 首位元素接住全部溢出量后仍不超过 mx，说明 mx 可行
        };  // 判定 lambda 定义结束
        while (left < right) {  // 二分查找最小的可行 mx
            int mid = (left + right) >> 1;  // 取中点（右移一位等价于除以 2）
            if (check(mid))  // 若 mid 可行
                right = mid;  // 保留 mid 作为上界，尝试更小的答案
            else  // 若 mid 不可行
                left = mid + 1;  // 答案必然大于 mid
        }  // 二分循环结束
        return left;  // 二分收敛时 left == right，就是最小化的最大值
    }  // minimizeArrayValue 方法结束
};  // 类定义结束