// 题目：1300. 转变数组后最接近目标值的数组和（Sum of Mutated Array Closest to Target）
// 思路：排序后枚举所有候选 value（0..max），借助前缀和与 upper_bound 在 O(log n) 内算出该 value 下的数组和。
// 时间复杂度：O(n log n + max*log n)，max 为数组最大值；空间复杂度：O(n)，前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findBestValue(vector<int>& arr, int target) {  // arr：输入数组；target：目标值
        sort(arr.begin(), arr.end());  // 升序排序，便于前缀和与二分
        int n = arr.size();  // 数组长度
        int s[n + 1];  // 前缀和数组，s[i] 表示前 i 个元素之和
        s[0] = 0;  // 空前缀和为 0
        int mx = 0;  // 数组最大值，决定 value 的枚举上界
        for (int i = 0; i < n; ++i) {  // 递推求前缀和
            s[i + 1] = s[i] + arr[i];  // 前 i+1 个元素之和
            mx = max(mx, arr[i]);  // 顺便更新最大值
        }
        int ans = 0, diff = 1 << 30;  // ans：当前最优 value；diff：当前最小绝对差
        for (int value = 0; value <= mx; ++value) {  // 枚举 0 到最大值之间的所有候选
            int i = upper_bound(arr.begin(), arr.end(), value) - arr.begin();  // 第一个大于 value 的下标，前 i 个不需要被截断
            int d = abs(s[i] + (n - i) * value - target);  // 前 i 个保留原值，后 n-i 个统一变成 value
            if (diff > d) {  // 严格大于，保证并列时保留更小的 value
                diff = d;  // 更新最小绝对差
                ans = value;  // 记录更优的 value
            }
        }
        return ans;  // 返回使数组和最接近目标值的 value
    }
};