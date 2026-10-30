// 题目：969. 煎饼排序（Pancake Sorting）
// 思路：从末尾往前逐位归位，每轮先把未归位的最大值翻到最前面，再整体翻转一次把它送到目标下标。
// 时间复杂度：O(n^2)，每轮扫描找最大值 O(n)；空间复杂度：O(1)，只用了常数个额外变量（不计输出）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> pancakeSort(vector<int>& arr) {  // arr 是待排序数组，返回每次翻转的长度（1-based，且不超过数组长度）
        int n = arr.size();  // n 为数组长度
        vector<int> ans;  // 记录每次翻转的长度序列
        for (int i = n - 1; i > 0; --i) {  // 从末尾往前逐位归位，本轮要归位的目标值是 i+1
            int j = i;  // j 从下标 i 开始向前查找目标值 i+1 的位置
            for (; j > 0 && arr[j] != i + 1; --j)  // 向前扫描，直到找到目标值或到达下标 0
                ;  // 循环体为空，扫描条件都写在循环头里
            if (j == i) continue;  // 目标值已经在目标位置，本轮无需翻转
            if (j > 0) {  // 若目标值不在首位，先把它翻到最前面
                ans.push_back(j + 1);  // 记录这次翻转的长度 j+1
                reverse(arr.begin(), arr.begin() + j + 1);  // 翻转前 j+1 个元素，把目标值送到开头
            }  // 目标值不在首位判断结束
            ans.push_back(i + 1);  // 记录把目标值翻到正确位置所用的翻转长度 i+1
            reverse(arr.begin(), arr.begin() + i + 1);  // 整体翻转前 i+1 个元素，目标值落到下标 i
        }  // 本轮结束
        return ans;  // 返回所有翻转操作
    }  // 方法结束
};  // 题解类结束