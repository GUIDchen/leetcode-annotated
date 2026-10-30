// 题目：1228. 等差数列中缺失的数字（Missing Number In Arithmetic Progression）
// 思路：补齐后的等差数列共有 n+1 项，其和可由 (首项 + 末项) × 项数 / 2 直接算出，再减去数组实际和，差值就是缺失的数字。
// 时间复杂度：O(n)，accumulate 扫一遍数组；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int missingNumber(vector<int>& arr) {  // arr：少了恰好一个元素的等差数列，返回缺失的那个数
        int n = arr.size();  // n：现存元素个数；补齐缺失值后完整数列长度应为 n+1
        int x = (arr[0] + arr[n - 1]) * (n + 1) / 2;  // 按等差数列求和公式算完整数列（n+1 项）总和：首项 arr[0] 与末项 arr[n-1] 已知
        int y = accumulate(arr.begin(), arr.end(), 0);  // 算数组里实际存在的元素之和
        return x - y;  // 两者之差就是被挖掉的那个数
    }  // 方法结束
};  // 类定义结束