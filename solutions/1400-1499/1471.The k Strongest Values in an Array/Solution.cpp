// 题目：1471. 数组中的 k 个最强值（The k Strongest Values in an Array）
// 核心思路：先排序取得中位数 m（下标 (n-1)/2），再按「与 m 的距离降序、距离相同时值更大者优先」重排，取前 k 个。
// 时间复杂度：O(n log n)，两次排序；空间复杂度：O(k)，存放答案（两次排序都是原地进行）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getStrongest(vector<int>& arr, int k) {  // arr 是输入数组，k 是要取出的最强值个数
        sort(arr.begin(), arr.end());  // 先升序排序，才能直接按下标取到中位数
        int m = arr[(arr.size() - 1) >> 1];  // 题目定义的中位数：下标 (n-1)/2 处的元素（右移一位等价于除以 2 向下取整）
        sort(arr.begin(), arr.end(), [&](int a, int b) {  // 用自定义比较器重排，捕获中位数 m
            int x = abs(a - m), y = abs(b - m);  // x、y 分别是两个元素与中位数的距离
            return x == y ? a > b : x > y;  // 距离大者在前；距离相同则值大者在前
        });  // 排序完成，arr 已按强度从强到弱排列
        vector<int> ans(arr.begin(), arr.begin() + k);  // 取前 k 个即为答案
        return ans;  // 返回结果
    }  // 方法结束
};  // 类定义结束