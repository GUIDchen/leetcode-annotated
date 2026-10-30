// 题目：649. Dota2 参议院（Dota2 Senate）
// 思路：用两个队列分别保存 Radiant 与 Dire 议员的生效下标；每轮双方各出队一人，下标小的一方先行动并禁言对手，胜者以「下标 + n」重新入队进入下一轮。
// 时间复杂度：O(n)，每个议员最多出队、入队各一次；空间复杂度：O(n)，两个队列合计最多存 n 个下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string predictPartyVictory(string senate) {  // senate 是议员队列（R 为 Radiant，D 为 Dire），返回最终获胜方
        int n = senate.size();  // 议员总数，用「下标 + n」表示该议员在下一轮的位置
        queue<int> qr;  // 存放 Radiant 议员的生效下标
        queue<int> qd;  // 存放 Dire 议员的生效下标
        for (int i = 0; i < n; ++i) {  // 按原顺序把议员下标分装进两个队列
            if (senate[i] == 'R') {  // 当前是 Radiant 议员
                qr.push(i);  // 记录它的下标
            } else {  // 否则是 Dire 议员
                qd.push(i);  // 记录它的下标
            }
        }
        while (!qr.empty() && !qd.empty()) {  // 双方都还有议员时继续对抗
            int r = qr.front();  // 队首 Radiant 议员本轮的下标
            int d = qd.front();  // 队首 Dire 议员本轮的下标
            qr.pop();  // 先弹出，稍后按胜负决定是否重新入队
            qd.pop();  // 同上
            if (r < d) {  // 下标更小者先行动，可以禁言对手
                qr.push(r + n);  // Radiant 获胜，加上 n 排到下一轮继续参与
            } else {  // 否则 Dire 先行动
                qd.push(d + n);  // Dire 获胜，加上 n 排到下一轮继续参与
            }
        }
        return qr.empty() ? "Dire" : "Radiant";  // Radiant 队列空说明 Dire 获胜，否则 Radiant 获胜
    }
};