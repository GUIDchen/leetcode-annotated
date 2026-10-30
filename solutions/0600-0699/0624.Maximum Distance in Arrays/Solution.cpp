// 题目：624. 数组列表中的最大距离（Maximum Distance in Arrays）
// 思路：每组内部有序，扫描时用「历史全局最小值/最大值」与当前组的另一端组合，边更新边取最大距离。
// 时间复杂度：O(m)，m 为数组组数；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDistance(vector<vector<int>>& arrays) {  // arrays 是若干组升序数组，要求取自不同组的两个元素的最大差值绝对值
        int ans = 0;  // 记录目前为止的最大距离，初始为 0
        int mi = arrays[0][0], mx = arrays[0][arrays[0].size() - 1];  // 前若干组里出现过的最小值与最大值（每组内部升序，首元素最小、末元素最大）
        for (int i = 1; i < arrays.size(); ++i) {  // 从第二组开始遍历，边更新历史最值边计算距离
            auto& arr = arrays[i];  // 用引用取当前组，避免整体拷贝
            int a = abs(arr[0] - mx), b = abs(arr[arr.size() - 1] - mi);  // 两种跨组候选：本组最小 vs 历史最大；本组最大 vs 历史最小
            ans = max({ans, a, b});  // 三个候选值取最大，刷新答案
            mi = min(mi, arr[0]);  // 把本组最小值并入历史最小
            mx = max(mx, arr[arr.size() - 1]);  // 把本组最大值并入历史最大
        }
        return ans;  // 返回最终的最大距离
    }
};