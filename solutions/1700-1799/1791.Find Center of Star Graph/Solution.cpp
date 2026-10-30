// 题目：1791. 找出星型图的中心节点（Find Center of Star Graph）
// 思路：星型图的中心点与其余所有点相连，因此它一定同时出现在前两条边中；只需比较这两条边共有的端点。
// 时间复杂度：O(1)，只取两条边做常数次比较；空间复杂度：O(1)，不额外开数组。
class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {  // 主函数：返回星型图的中心节点编号
        int a = edges[0][0], b = edges[0][1];  // 第一条边的两个端点
        int c = edges[1][0], d = edges[1][1];  // 第二条边的两个端点
        return a == c || a == d ? a : b;  // if 表达式：a 出现在第二条边里就说明 a 是中心，否则中心只能是 b
    }
};  // 题解类定义结束