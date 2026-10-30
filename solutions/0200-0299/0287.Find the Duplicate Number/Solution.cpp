// 题目：287. 寻找重复数（Find the Duplicate Number）—— 长度为 n+1、取值在 [1, n] 的数组里只有一个数重复，找出它。
// 核心思路：对答案值域二分。统计数组中小于等于 mid 的元素个数 cnt，若 cnt > mid，重复数必落在 [l, mid] 一侧。
// 时间复杂度：O(n log n)，每次二分都要扫一遍数组；空间复杂度：O(1)，不修改数组、只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findDuplicate(vector<int>& nums) {  // nums：长度 n+1、元素取值在 [1, n] 的数组（按要求不修改它）
        int l = 0, r = nums.size() - 1;  // 二分答案的取值区间 [l, r]，答案一定落在 [1, n] 内
        while (l < r) {  // 区间收缩到一个数时，它就是重复数
            int mid = (l + r) >> 1;  // 取中点；右移一位等价于除 2，且不会有加法溢出的隐患
            int cnt = 0;  // 统计 nums 中小于等于 mid 的元素个数
            for (int& v : nums) {  // 遍历数组的每个元素，用引用避免拷贝
                cnt += v <= mid;  // 布尔结果自动转成 0/1 累加：v <= mid 就计一次
            }
            if (cnt > mid) {  // 抽屉原理：<= mid 的数比 mid 个还多，说明 [1, mid] 里一定藏着重复数
                r = mid;  // 把右边界收到 mid（mid 本身也可能是答案，不能丢）
            } else {  // 左半区没有超额，重复数一定在 [mid+1, r]
                l = mid + 1;  // 左边界右移到 mid + 1
            }
        }
        return l;  // 区间收敛后唯一剩下的值就是重复数
    }
};