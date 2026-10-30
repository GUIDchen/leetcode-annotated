// 题目：2951. 找出峰值（Find the Peaks）
// 思路：峰值必须严格大于左右邻居，且只可能出现在下标 1..n-2，逐一下标检查并把满足条件的下标收集起来。
// 时间复杂度：O(n)，线性扫描一遍；空间复杂度：O(1)，除答案数组外只用常数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findPeaks(vector<int>& mountain) {  // mountain：山脉数组；返回所有峰值的下标
        vector<int> ans;  // 收集峰值下标的答案数组
        for (int i = 1; i < mountain.size() - 1; ++i) {  // 首尾元素没有两个邻居，所以从 1 遍历到 n-2
            if (mountain[i - 1] < mountain[i] && mountain[i + 1] < mountain[i]) {  // 同时严格大于左右相邻元素才算是峰值
                ans.push_back(i);  // 记录该峰值下标
            }  // if 分支结束
        }  // for 循环结束
        return ans;  // 返回全部峰值下标
    }  // 方法结束
};  // 类定义结束