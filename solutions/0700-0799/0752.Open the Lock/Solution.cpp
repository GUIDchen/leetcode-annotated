// 题目：752. 打开转盘锁（Open the Lock）——中等
// 思路：从 "0000" 出发做 BFS，把死锁串预先放进集合当已访问；每层扩展拨动一位得到的 8 个状态，首次命中 target 的层数就是最少步数。
// 时间复杂度：O(10^4 * 8)，状态数上限约一万、每个状态 8 条边；空间复杂度：O(10^4)，队列与集合最多保存一万个状态。
class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    int openLock(vector<string>& deadends, string target) {  // deadends 是死锁串，target 是目标串
        unordered_set<string> s(deadends.begin(), deadends.end());  // 哈希集合同时充当「死锁表」与「已访问表」，判重是 O(1)
        if (s.count("0000")) return -1;  // 起点本身就是死锁，永远无法出发
        if (target == "0000") return 0;  // 目标就是起点，0 步即可到达
        queue<string> q{{"0000"}};  // BFS 队列，起始只放入起点
        s.insert("0000");  // 把起点登记为已访问，避免后续重复入队
        int ans = 0;  // 记录的层数，也就是已走的步数
        while (!q.empty()) {  // 队列非空说明还有状态可以向外扩展
            ++ans;  // 进入新的一层，步数加一
            for (int n = q.size(); n > 0; --n) {  // 先固定本层状态个数，保证只扩展这一层
                string p = q.front();  // 取出当前状态
                q.pop();  // 当前状态出队
                for (string t : next(p)) {  // 枚举拨动任意一位得到的 8 个邻居状态
                    if (target == t) return ans;  // 首次遇到目标，BFS 保证这是最少步数
                    if (!s.count(t)) {  // 邻居既不是死锁，也没有被访问过
                        q.push(t);  // 入队，等待下一层继续扩展
                        s.insert(t);  // 立刻登记，防止同一层内重复入队
                    }
                }
            }
        }
        return -1;  // 队列耗尽仍未到达目标，说明被死锁彻底隔断
    }

    vector<string> next(string& t) {  // 辅助函数：把 t 的某一位上下拨动一位，返回全部邻居
        vector<string> res;  // 收集邻居状态
        for (int i = 0; i < 4; ++i) {  // 依次拨动四个拨轮
            char c = t[i];  // 暂存原字符，便于最后还原
            t[i] = c == '0' ? '9' : (char) (c - 1);  // 向下拨：0 回绕成 9，其余字符减一
            res.push_back(t);  // 记录向下拨后的状态
            t[i] = c == '9' ? '0' : (char) (c + 1);  // 向上拨：9 回绕成 0，其余字符加一
            res.push_back(t);  // 记录向上拨后的状态
            t[i] = c;  // 还原这一位，继续处理下一位
        }
        return res;  // 返回全部 8 个邻居状态
    }
};