// 题目：852. 山脉数组的峰顶索引（Peak Index in a Mountain Array）
// 思路：在 [1, n-2] 上二分：若 arr[mid] > arr[mid+1] 说明峰顶在 mid 或其左侧，否则在 mid 右侧。
// 时间复杂度：O(log n)；空间复杂度：O(1)，只用常数个变量。
class Solution {  // 题解类
public:
    int peakIndexInMountainArray(vector<int>& arr) {  // arr 是山脉数组：先严格递增再严格递减
        int left = 1, right = arr.size() - 2;  // 峰顶不可能在两端，把候选区间缩小到 [1, n-2]
        while (left < right) {  // 二分直到区间只剩一个位置
            int mid = (left + right) >> 1;  // 取中点，>> 1 等价于整除 2
            if (arr[mid] > arr[mid + 1])  // 处于下降段，峰顶在 mid 或其左侧
                right = mid;  // 保留 mid，把右边界左移
            else  // 处于上升段，峰顶严格在 mid 右侧
                left = mid + 1;  // 把左边界右移到 mid+1
        }  // 二分结束
        return left;  // 收敛位置就是峰顶下标
    }  // 方法结束
};  // 题解类结束