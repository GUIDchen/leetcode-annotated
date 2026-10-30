// 题目：2076. 处理含限制条件的好友请求（Process Restricted Friend Requests）
// 思路：用并查集维护「朋友连通块」，对每个请求先判断两集合能否合并——若某条禁友对恰好横跨这两个集合则拒绝，否则同意并合并。
// 时间复杂度：O((n + |restrictions|) · |requests| · α(n))；空间复杂度：O(n)，用于并查集父数组。
class Solution {  // 题解类：所有题解方法都写在这里
public:  // 方法对外可见（LeetCode 约定）
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {  // n 是人数，restrictions 是禁友对，requests 是按顺序到来的好友请求
        vector<int> p(n);  // 并查集父数组：p[i] 表示 i 的父节点
        iota(p.begin(), p.end(), 0);  // 初始化 p[i] = i，让每个人各自成为一个集合
        function<int(int)> find = [&](int x) {  // 带路径压缩的查找函数（递归），返回 x 所在集合的代表元
            if (p[x] != x) {  // 若 x 不是根节点
                p[x] = find(p[x]);  // 递归找到根，并把 x 直接挂到根上（路径压缩）
            }  // if 结束
            return p[x];  // 返回根节点
        };  // find 定义结束
        vector<bool> ans;  // 按顺序记录每个请求的处理结果
        for (auto& req : requests) {  // 依次处理每个好友请求
            int u = req[0], v = req[1];  // 取出请求中的两个人 u、v
            int pu = find(u), pv = find(v);  // 分别求两人当前所在集合的代表元
            if (pu == pv) {  // 已在同一集合，直接同意
                ans.push_back(true);  // 记录结果为 true
            } else {  // 两集合不同，需要检查合并后是否违反限制
                bool ok = true;  // 先假定可以合并
                for (auto& r : restrictions) {  // 逐条检查所有禁友对
                    int px = find(r[0]), py = find(r[1]);  // 求禁友对两人所在集合的代表元
                    if ((pu == px && pv == py) || (pu == py && pv == px)) {  // 禁友对恰好分属即将合并的两个集合，说明合并会冲突
                        ok = false;  // 标记为不合法
                        break;  // 立即跳出检查
                    }  // if 结束
                }  // 禁友对检查循环结束
                ans.push_back(ok);  // 记录本次请求的判定结果
                if (ok) {  // 只有在没有冲突时才真正合并
                    p[pu] = pv;  // 把一个集合的根挂到另一个根下
                }  // if 结束
            }  // else 块结束
        }  // 请求循环结束
        return ans;  // 返回所有请求的处理结果
    }  // 方法结束
};  // 类定义结束