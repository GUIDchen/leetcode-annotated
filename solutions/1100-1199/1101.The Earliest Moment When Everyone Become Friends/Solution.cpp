// 题目：1101. 彼此熟识的最早时间（The Earliest Moment When Everyone Become Friends）
// 思路：把朋友关系按时间升序处理，用并查集合并两人；当连通分量个数降到 1 时，当前日志的时间就是答案。
// 时间复杂度：O(m log m + m α(n))，m 条日志，瓶颈是排序；空间复杂度：O(n)，并查集数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int earliestAcq(vector<vector<int>>& logs, int n) {  // logs 每项为 {时间, 人x, 人y}；n 是总人数
        sort(logs.begin(), logs.end());  // 按时间升序排序，保证第一个全员连通的时刻就是「最早」的（vector 字典序比较先比首元素）
        vector<int> p(n);  // 并查集父节点数组，下标即人的编号
        iota(p.begin(), p.end(), 0);  // iota 把 p 初始化为 0,1,...,n-1，每人各自成一个集合
        function<int(int)> find = [&](int x) {  // 带路径压缩的 find lambda
            return p[x] == x ? x : p[x] = find(p[x]);  // 递归找根，顺手把 p[x] 直接指向根（路径压缩）
        };  // lambda 定义结束
        for (auto& log : logs) {  // 按时间从早到晚处理每条朋友关系
            int x = find(log[1]);  // x 是 log[1] 所在集合的根
            int y = find(log[2]);  // y 是 log[2] 所在集合的根
            if (x != y) {  // 根不同才说明两人还不在同一集合，需要合并
                p[x] = y;  // 把一个根挂到另一个根下，完成合并
                --n;  // 连通分量个数减一（n 在这里被复用为分量计数）
            }  // if 结束
            if (n == 1) {  // 只剩一个连通分量，说明所有人都已互相认识
                return log[0];  // 当前这条日志的时间就是最早时刻
            }  // if 结束
        }  // for 结束
        return -1;  // 所有日志处理完仍未全员连通，返回 -1
    }  // 方法结束
};  // 类定义结束