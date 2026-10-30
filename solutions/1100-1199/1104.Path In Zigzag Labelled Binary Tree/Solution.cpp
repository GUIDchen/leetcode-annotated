// 题目：1104. 二叉树寻路（Path In ZigZag Labelled Binary Tree）
// 思路：先求出 label 所在层最左端的顺序标号，再用「之字形标号先镜像回顺序标号、再除以 2」逐层反推父节点，最后反转成根到叶。
// 时间复杂度：O(log label)，层数与路径长度都是对数级；空间复杂度：O(log label)，保存路径。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> pathInZigZagTree(int label) {  // label 是之字形标号，返回从根到它的路径
        int x = 1, i = 1;  // x 记录当前层最左端的顺序标号，i 记录层号（根为第 1 层）
        while ((x << 1) <= label) {  // 下一层起点 x * 2 仍不超过 label，说明 label 在更深的层
            x <<= 1;  // 进入下一层
            ++i;  // 层号加一
        }  // while 结束
        vector<int> ans;  // 倒序收集路径，从 label 往根走
        for (; i > 0; --i) {  // 按层从下往上处理，i 同时就是当前层号
            ans.push_back(label);  // 把当前层的标号放入答案
            label = ((1 << (i - 1)) + (1 << i) - 1 - label) >> 1;  // 先把之字形标号镜像回顺序标号，再除以 2 得到父节点标号
        }  // for 结束
        reverse(ans.begin(), ans.end());  // 之前是从叶子到根的顺序，反转成根到叶子
        return ans;  // 返回路径
    }  // 方法结束
};  // 类定义结束