// 题目：1705. 吃苹果的最大数目（Maximum Number of Eaten Apples）
// 思路：用小根堆按“腐烂日期”存放每天长出的苹果，每天先丢掉已过期的，再吃掉最早过期的一颗；过了产果期也继续吃完堆里剩下的。
// 时间复杂度：O(n log n)，每个批次最多进堆出堆各一次；空间复杂度：O(n)，堆里最多存 n 个批次。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int eatenApples(vector<int>& apples, vector<int>& days) {  // apples[i]：第 i 天长出的苹果数；days[i]：保质天数
        using pii = pair<int, int>;  // 简写：pair<腐烂日期, 数量>
        priority_queue<pii, vector<pii>, greater<pii>> q;  // 小根堆，堆顶是腐烂日期最早的那批苹果
        int n = days.size();  // 产果期的总天数
        int ans = 0, i = 0;  // ans：已吃掉的苹果数；i：当前天数
        while (i < n || !q.empty()) {  // 产果期没结束，或者堆里还有苹果可以吃，就继续
            if (i < n && apples[i]) {  // 今天是产果日且确实长出了苹果
                q.emplace(i + days[i] - 1, apples[i]);  // 这批苹果的第 i + days[i] - 1 天是最后可食用的日子
            }
            while (!q.empty() && q.top().first < i) {  // 把已经过了最后可食用的批次全部丢弃
                q.pop();  // 过期苹果不能吃，直接出堆
            }
            if (!q.empty()) {  // 还有新鲜苹果就吃一颗
                auto [t, v] = q.top();  // 取出最紧急（最早过期）的那批：t 是到期日，v 是数量
                q.pop();  // 先出堆，处理完再按剩余数量决定是否放回
                --v;  // 吃掉一颗，数量减一
                ++ans;  // 今天有收获，答案加一
                if (v && t > i) {  // 这批还有剩余，而且明天它仍未过期
                    q.emplace(t, v);  // 把剩余部分放回堆里等明天再吃
                }
            }
            ++i;  // 进入下一天
        }
        return ans;  // 返回最多能吃掉的苹果数
    }
};
