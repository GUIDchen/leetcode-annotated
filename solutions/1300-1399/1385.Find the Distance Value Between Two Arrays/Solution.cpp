// 题目：1385. 两个数组间的距离值（Find the Distance Value Between Two Arrays）
// 思路：把 arr2 排序，对每个 x 二分查找第一个不小于 x-d 的位置，判断它是否已经超过 x+d。
// 时间复杂度：O((n+m) log m)，排序加 n 次二分；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {  // d 是允许的距离阈值
        ranges::sort(arr2);  // C++20 ranges 版本排序，为二分查找做准备
        int ans = 0;  // 统计满足条件的 arr1 元素个数
        for (int x : arr1) {  // 逐个检查 arr1 中的元素
            auto it = ranges::lower_bound(arr2, x - d);  // 找到第一个 >= x-d 的元素位置
            if (it == arr2.end() || *it > x + d) {  // 没有这样的元素，或它已经超出 x+d 的范围
                ++ans;  // 说明 arr2 中不存在与 x 距离不超过 d 的元素，计数加一
            }  // 判断结束
        }  // 遍历结束
        return ans;  // 返回满足条件的元素个数
    }  // findTheDistanceValue 结束
};  // Solution 类结束
