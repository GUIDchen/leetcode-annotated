// 题目：502. IPO（IPO）
// 思路：用按启动资本排序的小根堆把「现在买得起」的项目逐个解锁到大根堆里，每轮贪心取利润最大的那个，最多取 k 轮。
// 时间复杂度：O(n log n + k log n)，建堆与每轮取堆顶；空间复杂度：O(n)，两个堆最多共 n 个元素。
using pii = pair<int, int>;  // 便于书写的类型别名：pii 等价于 pair<int, int>

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {  // k 是最多可选的项目数，w 是初始资本；profits/capital 分别是利润与启动资本
        priority_queue<pii, vector<pii>, greater<pii>> q1;  // 小根堆：按启动资本从小到大排序，队首是当前最「便宜」的项目
        int n = profits.size();  // 项目总数
        for (int i = 0; i < n; ++i) {  // 把所有项目按 (启动资本, 利润) 压入小根堆
            q1.push({capital[i], profits[i]});  // 先比较启动资本，资本相同时再比较利润
        }  // 建堆循环结束
        priority_queue<int> q2;  // 大根堆：暂存当前买得起的项目的利润，队首是最大利润
        while (k--) {  // 最多挑选 k 个项目（k-- 用完即止）
            while (!q1.empty() && q1.top().first <= w) {  // 把启动资本不超过当前资本的项目全部解锁
                q2.push(q1.top().second);  // 利润放进大根堆，等这一轮挑选
                q1.pop();  // 从待选池中移除已经解锁的项目
            }  // 解锁循环结束
            if (q2.empty()) {  // 一个项目都买不起，资本不会再增长
                break;  // 提前结束选项目
            }  // 判断分支结束
            w += q2.top();  // 贪心：选当前买得起且利润最大的项目，资本随之增加
            q2.pop();  // 该项目已经用过，弹出
        }  // 选项目循环结束
        return w;  // 返回最终能获得的最大资本
    }  // 方法体结束
};  // 类定义结束