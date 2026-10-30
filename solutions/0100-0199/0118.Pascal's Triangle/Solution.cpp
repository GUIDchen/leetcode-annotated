// 题目：118. 杨辉三角（Pascal's Triangle）
// 思路：逐层递推，每行首尾固定是 1，中间每个元素等于上一行相邻两元素之和。
// 时间复杂度：O(numRows^2)，一共要填约 numRows^2/2 个格子；空间复杂度：O(numRows^2)，返回值本身就要存下整个三角。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> generate(int numRows) {  // numRows 是要生成的行数，返回杨辉三角的前 numRows 行
        vector<vector<int>> f;  // f 保存所有行，最后整体返回
        f.push_back(vector<int>(1, 1));  // 第一行固定是 [1]
        for (int i = 0; i < numRows - 1; ++i) {  // 再生成 numRows - 1 行；i 表示当前最后一行的下标，也就是新行的上一层
            vector<int> g;  // g 是正在构造的新一行
            g.push_back(1);  // 新行第一个元素恒为 1
            for (int j = 1; j < f[i].size(); ++j) {  // 中间部分：遍历上一行除首元素外的每个位置
                g.push_back(f[i][j - 1] + f[i][j]);  // 相邻两数之和，正是杨辉三角的递推关系
            }
            g.push_back(1);  // 新行最后一个元素也恒为 1
            f.push_back(g);  // 把构造好的新行加入结果
        }
        return f;  // 返回前 numRows 行
    }
};  // 类定义结束