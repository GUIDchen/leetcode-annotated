// 题目：1534. 统计好三元组（Count Good Triplets）
// 思路：直接按 i<j<k 三重枚举所有下标组合，逐组检查三对元素的差值是否分别不超过 a、b、c。
// 时间复杂度：O(n³)，三层循环枚举全部三元组；空间复杂度：O(1)，只用常量个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {  // arr：输入数组；a、b、c：三对元素差值各自的上限
        int n = arr.size();  // 数组长度，用作三层循环的边界
        int ans = 0;  // 好三元组的计数器，初值为 0
        for (int i = 0; i < n; ++i) {  // 枚举第一个下标 i
            for (int j = i + 1; j < n; ++j) {  // 第二个下标从 i+1 开始，保证下标严格递增、不重复枚举
                for (int k = j + 1; k < n; ++k) {  // 第三个下标从 j+1 开始，保证 i<j<k
                    // 同时检查三对差值：|arr[i]-arr[j]|<=a、|arr[j]-arr[k]|<=b、|arr[i]-arr[k]|<=c
                    ans += abs(arr[i] - arr[j]) <= a && abs(arr[j] - arr[k]) <= b && abs(arr[i] - arr[k]) <= c;  // 条件全部成立时布尔值为 true（即 1），直接累加进答案
                }  // 最内层 k 循环结束
            }  // 第二层 j 循环结束
        }  // 第一层 i 循环结束
        return ans;  // 返回满足条件的三元组个数
    }  // 方法结束
};  // 题解类结束