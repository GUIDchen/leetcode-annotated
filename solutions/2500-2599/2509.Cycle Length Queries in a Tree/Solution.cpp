// 题目：2509. 查询树中环的长度（Cycle Length Queries in a Tree）
// 思路：完全二叉树中节点 x 的父节点是 x/2，加一条边 (a,b) 形成的环长 = a、b 到最近公共祖先的边数之和再加 1；让编号大的先不断上跳直到两者相等。
// 时间复杂度：O(q log n)，q 为查询条数；空间复杂度：O(1)，除答案数组外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries) {  // n：完全二叉树的节点数；queries：待查询的节点对
        vector<int> ans;  // 按查询顺序保存每个环的长度
        for (auto& q : queries) {  // 逐条处理查询
            int a = q[0], b = q[1];  // a、b 是本次新加边连接的两个节点编号
            int t = 1;  // 环长初值为 1：新加的那条边本身算作一条边
            while (a != b) {  // 两个节点尚未走到最近公共祖先时继续上跳
                if (a > b) {  // 编号较大的节点一定更深，先让它上跳
                    a >>= 1;  // 编号除以 2 即父节点编号（完全二叉树的性质）
                } else {  // 否则让 b 上跳
                    b >>= 1;  // b 的父节点编号为 b / 2
                }
                ++t;  // 每上跳一条边，环就多一条边
            }
            ans.emplace_back(t);  // 此时 a == b 即最近公共祖先，t 就是该环的边数
        }
        return ans;  // 返回所有查询对应的环长
    }
};