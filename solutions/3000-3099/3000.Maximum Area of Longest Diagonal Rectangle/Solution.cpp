// 题目：3000. 对角线最长的矩形的面积（Maximum Area of Longest Diagonal Rectangle）
// 思路：对角线长度的平方就是 l² + w²，一次遍历找最大对角线；对角线等长时取面积更大的那个矩形。
// 时间复杂度：O(n)，只需遍历一遍矩形数组；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {  // dimensions：每项形如 {长, 宽}；返回对角线最长的矩形中面积的最大值
        int ans = 0, mx = 0;  // ans：答案面积；mx：目前出现过的最长对角线的平方
        for (auto& d : dimensions) {  // 逐个枚举每个矩形
            int l = d[0], w = d[1];  // 取出这个矩形的长 l 和宽 w
            int t = l * l + w * w;  // 对角线长度的平方；用平方比较可以避免开根号带来的精度问题
            if (mx < t) {  // 发现了一条更长的对角线
                mx = t;  // 更新最长对角线的平方
                ans = l * w;  // 答案改为这个矩形的面积
            } else if (mx == t) {  // 对角线一样长，此时要比面积大小
                ans = max(ans, l * w);  // 保留两者中更大的面积
            }
        }
        return ans;  // 返回最终求得的面积
    }
};