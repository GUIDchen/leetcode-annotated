// 题目：1200. 最小绝对差（Minimum Absolute Difference）
// 思路：排序后最小绝对差只会出现在相邻元素之间；先求相邻差的最小值，再收集所有达到该值的相邻对。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，除返回结果外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {  // arr 是输入数组，返回所有「绝对差等于最小绝对差」且按升序排列的数对
        sort(arr.begin(), arr.end());  // 升序排序：排序后最小绝对差一定出现在相邻元素之间
        int mi = 1 << 30;  // mi 记录相邻差的最小值，1 << 30 当作无穷大
        int n = arr.size();  // n 是数组长度
        for (int i = 0; i < n - 1; ++i) {  // 枚举所有相邻对 (i, i+1)，i 最大取到 n-2
            mi = min(mi, arr[i + 1] - arr[i]);  // 用当前相邻差更新最小值
        }
        vector<vector<int>> ans;  // ans 收集所有达到最小绝对差的数对
        for (int i = 0; i < n - 1; ++i) {  // 再扫一遍所有相邻对
            if (arr[i + 1] - arr[i] == mi) {  // 这一对的差正好等于最小绝对差
                ans.push_back({arr[i], arr[i + 1]});  // 把这一对（本身已升序）放进答案
            }
        }
        return ans;  // 返回所有达到最小绝对差的数对
    }
};