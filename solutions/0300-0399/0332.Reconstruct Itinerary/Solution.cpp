// 题目：332. 重新安排行程（Reconstruct Itinerary）
// 思路：Hierholzer 求欧拉路径；票按目的地逆序排序后建图，深搜时不断弹出字典序最小的目的地，回溯时记录节点，最后整体反转。
// 时间复杂度：O(E log E)，主要是给 E 张票排序；空间复杂度：O(E)，邻接表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> findItinerary(vector<vector<string>>& tickets) {  // tickets：每张票是 [出发地, 目的地]，返回从 "JFK" 出发、字典序最小的完整行程
        sort(tickets.rbegin(), tickets.rend());  // 逆序排序后目的地最小的票落在 vector 末尾，正好配合 back()/pop_back() 取最小
        unordered_map<string, vector<string>> g;  // 邻接表：机场 -> 它出发的所有目的地
        for (const auto& ticket : tickets) {  // 遍历所有机票建图
            g[ticket[0]].push_back(ticket[1]);  // 把目的地压入出发地的邻接表
        }  // 建图循环结束
        vector<string> ans;  // 保存欧拉路径（回溯时按逆序记录）
        auto dfs = [&](this auto&& dfs, string& f) -> void {  // C++23 的「显式对象参数」写法，让 lambda 能递归调用自己；f 是当前所在机场
            while (!g[f].empty()) {  // 只要 f 还有没用完的机票就继续往下走
                string t = g[f].back();  // 取出字典序最小的目的地（逆序排序后它在末尾）
                g[f].pop_back();  // 立刻删掉这张票，避免重复使用
                dfs(t);  // 深度优先走到下一个机场
            }  // while 结束：f 出发的票全部用完了
            ans.emplace_back(f);  // 没有出边时才记录 f，回溯得到的正是欧拉路径的逆序
        };  // lambda 定义结束
        string f = "JFK";  // 起点固定为 "JFK"
        dfs(f);  // 从起点开始找欧拉路径
        reverse(ans.begin(), ans.end());  // 记录下来的是逆序，整体反转得到正确顺序
        return ans;  // 返回完整行程
    }  // 方法结束
};  // 类结束
