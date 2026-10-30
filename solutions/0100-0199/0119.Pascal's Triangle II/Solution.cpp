// 题目：119. 杨辉三角 II（Pascal's Triangle II）
// 思路：只用一个一维数组滚动更新，第 i 行从右往左做 f[j] += f[j-1]，倒序保证 f[j-1] 还是上一行的旧值。
// 时间复杂度：O(rowIndex^2)，逐行累加；空间复杂度：O(rowIndex)，只需要目标行那么长的一维数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getRow(int rowIndex) {  // rowIndex 是 0 基的行号，返回该行的所有元素
        vector<int> f(rowIndex + 1, 1);  // 一维数组滚动保存当前行，长度 rowIndex+1，初值全 1（每行首尾恒为 1）
        for (int i = 2; i < rowIndex + 1; ++i) {  // 从第 2 行开始逐行向上更新；第 0、1 行本来就全是 1
            for (int j = i - 1; j; --j) {  // 从右往左更新，j 只到 1：f[0] 恒为 1 且不能被覆盖
                f[j] += f[j - 1];  // 当前位置 = 自己（旧的左上方相邻值）+ 前一位；倒序保证 f[j-1] 仍属于上一行
            }
        }
        return f;  // 此时 f 就是第 rowIndex 行
    }
};  // 类定义结束