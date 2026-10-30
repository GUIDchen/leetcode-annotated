// 题目：581. 最短无序连续子数组（Shortest Unsorted Continuous Subarray）
// 核心思路：复制一份并排序；左右两端与排序结果对齐的位置一定不需要重排，中间夹住的区间就是最短需排序子数组。
// 时间复杂度：O(n log n)，排序是瓶颈；空间复杂度：O(n)，需要一个等长副本。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findUnsortedSubarray(vector<int>& nums) {  // nums 是输入的整数数组
        vector<int> arr = nums;  // 复制一份原数组，避免排序破坏输入
        sort(arr.begin(), arr.end());  // 对副本排序，得到「完全升序」的目标形态
        int l = 0, r = arr.size() - 1;  // l 从左端、r 从右端相向扫描
        while (l <= r && arr[l] == nums[l]) {  // 左端元素已经落在正确位置
            l++;  // 左边界右移，跳过这段有序前缀
        }  // 左扫描结束
        while (l <= r && arr[r] == nums[r]) {  // 右端元素已经落在正确位置
            r--;  // 右边界左移，跳过这段有序后缀
        }  // 右扫描结束
        return r - l + 1;  // 闭区间 [l, r] 的长度即最短无序子数组长度；若已整体有序则 l > r，长度自然为 0
    }  // findUnsortedSubarray 结束
};  // 类定义结束（源文件末尾无换行，此处保持原样）