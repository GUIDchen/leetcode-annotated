// 题目：278. 第一个错误的版本（First Bad Version）
// 思路：坏版本具有单调性，答案左侧全是好版本、右侧全是坏版本，因此二分查找最小的坏版本号。
// 时间复杂度：O(log n)，区间每次折半；空间复杂度：O(1)，只用了常数个变量。
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int firstBadVersion(int n) {  // n：版本总数；返回第一个坏版本的版本号
        int l = 1, r = n;  // 二分区间 [l, r]，初始覆盖 1..n
        while (l < r) {  // 区间还没收缩成单点，继续二分
            int mid = l + (r - l) / 2;  // 取中点；写成 l + (r - l) / 2 可避免 l + r 溢出
            if (isBadVersion(mid)) {  // mid 已是坏版本，答案一定落在 [l, mid]
                r = mid;  // 收缩右界，把 mid 保留为候选答案
            } else {  // 否则 mid 是正常版本，答案在 mid 之后
                l = mid + 1;  // 左界右移，排除 mid 及其左侧
            }
        }
        return l;  // 区间收敛成一点，该点就是第一个坏版本
    }
};
