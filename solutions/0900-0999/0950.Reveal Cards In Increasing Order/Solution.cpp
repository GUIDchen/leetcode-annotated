// 题目：950. 按递增顺序显示卡牌（Reveal Cards In Increasing Order）
// 思路：逆推。把牌按降序依次处理：每次先把队尾元素搬到队首（取消上一轮「把顶部牌放到底部」的影响），再把当前牌放到队首，最后队列即答案。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，双端队列存 n 张牌。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> deckRevealedIncreasing(vector<int>& deck) {  // deck：给定的牌面值数组
        sort(deck.rbegin(), deck.rend());  // 逆序排序：先放大牌，再逐张把更小的牌插到队首
        deque<int> q;  // 双端队列，队首是最终先被翻开的牌
        for (int v : deck) {  // 从大到小依次处理每张牌
            if (!q.empty()) {  // 队列非空时，需要先撤销上一轮「把队首移到队尾」的影响
                q.push_front(q.back());  // 取队尾元素塞到队首，相当于反方向的模拟
                q.pop_back();  // 原来队尾的副本已经搬到队首，这里把它真正删除
            }
            q.push_front(v);  // 当前这张牌放到队首，它是目前为止最小的牌
        }
        return vector<int>(q.begin(), q.end());  // 把双端队列转成 vector 返回最终牌堆顺序
    }
};