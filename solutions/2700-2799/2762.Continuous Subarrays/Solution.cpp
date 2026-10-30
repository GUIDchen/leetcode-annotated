// 题目：2762. 不间断子数组（Continuous Subarrays）
// 思路：滑动窗口配合有序多重集，窗口内最大值与最小值之差不超过 2 才合法；右移右端点后不断从左边吐出元素，并用窗口长度累加以 j 结尾的合法子数组个数。
// 时间复杂度：O(n log n)，每个元素进出有序集合各一次；空间复杂度：O(n)，有序集合最多保存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long continuousSubarrays(vector<int>& nums) {  // nums 是输入数组，返回所有最大值与最小值之差不超过 2 的连续子数组个数
        long long ans = 0;  // ans 用 long long 累加，因为子数组总数可达 O(n^2)
        int i = 0, n = nums.size();  // i 是滑动窗口左边界，n 是数组长度
        multiset<int> s;  // multiset 有序保存窗口内所有元素（允许重复），方便 O(log n) 取最大值和最小值
        for (int j = 0; j < n; ++j) {  // 枚举窗口右端点 j，把窗口一步步向右扩张
            s.insert(nums[j]);  // 新元素进入窗口
            while (*s.rbegin() - *s.begin() > 2) {  // 有序集合的首尾就是窗口的最小值与最大值，极差超过 2 说明窗口不合法
                s.erase(s.find(nums[i++]));  // 从窗口左侧不断移出元素直到极差回到 <= 2；i++ 让左边界同步右移，用 find 定位单个元素再 erase，避免把相同值一起删掉
            }  // 窗口收缩完毕，此时 [i, j] 以及它的所有后缀都满足条件
            ans += j - i + 1;  // 以 j 结尾的合法子数组共有 j - i + 1 个，累加进答案
        }  // 所有右端点都处理完了
        return ans;  // 返回不间断子数组的总个数
    }  // 方法结束
};  // 类定义结束