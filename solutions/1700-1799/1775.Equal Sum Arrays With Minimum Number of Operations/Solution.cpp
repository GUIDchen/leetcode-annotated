// 题目：1775. 通过最少操作次数使数组的和相等（Equal Sum Arrays With Minimum Number of Operations）
// 思路：交换两个数组使 s1 < s2，收集每个元素的最大可改变量（小的一侧 6-v、大的一侧 v-1）并降序排序，贪心先做收益最大的操作直到差值补齐。
// 时间复杂度：O((n+m) log (n+m))，排序开销；空间复杂度：O(n+m) 存放改变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums1, vector<int>& nums2) {  // nums1/nums2：两个元素取值都在 1..6 的数组
        int s1 = accumulate(nums1.begin(), nums1.end(), 0);  // 数组 1 的元素和
        int s2 = accumulate(nums2.begin(), nums2.end(), 0);  // 数组 2 的元素和
        if (s1 == s2) return 0;  // 已经相等，一次操作都不需要
        if (s1 > s2) return minOperations(nums2, nums1);  // 保证 s1 < s2：交换参数复用同一套逻辑
        int d = s2 - s1;  // 需要弥补的差值
        int arr[nums1.size() + nums2.size()];  // 把每个元素能贡献的最大改变量收集到数组里
        int k = 0;  // arr 的写入下标
        for (int& v : nums1) arr[k++] = 6 - v;  // 较小那侧的元素最多能加到 6，贡献 6 - v
        for (int& v : nums2) arr[k++] = v - 1;  // 较大那侧的元素最多能减到 1，贡献 v - 1
        sort(arr, arr + k, greater<>());  // 按贡献从大到小排序，贪心优先用收益最大的操作
        for (int i = 0; i < k; ++i) {  // 依次使用贡献最大的操作
            d -= arr[i];  // 用当前操作缩小差值
            if (d <= 0) return i + 1;  // 差值补齐，返回已使用的操作数
        }
        return -1;  // 所有元素都用上仍无法让两侧相等
    }
};  // 类定义结束