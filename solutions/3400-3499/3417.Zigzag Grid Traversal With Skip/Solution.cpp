// 3417. 跳过交替单元格的之字形遍历 / Zigzag Grid Traversal With Skip
// 核心思路：逐行遍历，奇数行先反转即得之字形顺序；用布尔开关 ok 每隔一格收集一次元素
// 复杂度：时间 O(m·n)（每格访问一次），空间 O(1) 额外空间（不计返回数组）
class Solution {  // 定义题解类
public:  // 公有方法区
    vector<int> zigzagTraversal(vector<vector<int>>& grid) {  // 之字形遍历网格，返回跳过交替单元格后的序列
        vector<int> ans;  // 存放结果的一维数组
        bool ok = true;  // 开关：true 表示当前元素需要收集
        for (int i = 0; i < grid.size(); ++i) {  // 枚举行下标 i
            if (i % 2 != 0) {  // 奇数行需要反向遍历，才能形成之字形
                ranges::reverse(grid[i]);  // 原地反转当前行，使其按之字形顺序排列
            }  // if 语句结束
            for (int x : grid[i]) {  // 按顺序遍历当前行的每个元素
                if (ok) {  // 若开关为真则收集该元素
                    ans.push_back(x);  // 把元素压入结果数组
                }  // if 语句结束
                ok = !ok;  // 开关取反，实现“收集一个、跳过一个”
            }  // 内层循环结束
        }  // 外层循环结束
        return ans;  // 返回跳过交替单元格后的遍历结果
    }  // 方法结束
};  // 类定义结束
