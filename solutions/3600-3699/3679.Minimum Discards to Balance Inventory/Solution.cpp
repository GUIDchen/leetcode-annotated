// 3679. Minimum Discards to Balance Inventory（3679. 使库存平衡的最少丢弃次数）
// 核心思路：用长度 w 的滑动窗口统计每种商品“已保留”的次数，本轮到达前该商品已达上限 m 就丢弃，否则标记保留并计数。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // 题解类
public:  // 公有接口，供判题器调用
    int minArrivalsToDiscard(vector<int>& arrivals, int w, int m) {  // 返回最少需要丢弃的商品数量
        unordered_map<int, int> cnt;  // cnt[x] 记录当前窗口内商品 x 被保留的次数
        int n = arrivals.size();  // 到达序列长度
        vector<int> marked(n, 0);  // marked[i] 表示第 i 件商品是否被保留（1 保留，0 丢弃）
        int ans = 0;  // 记录被丢弃的商品数量
        for (int i = 0; i < n; i++) {  // 按到达顺序逐件处理
            int x = arrivals[i];  // 当前到达的商品种类
            if (i >= w) {  // 窗口左端滑出时，撤销那件商品对计数的贡献
                cnt[arrivals[i - w]] -= marked[i - w];  // 只有被保留的商品才需要从计数中扣除
            }
            if (cnt[x] >= m) {  // 窗口内该商品已达到上限 m
                ans++;  // 只能丢弃当前这件
            } else {  // 否则保留当前这件
                marked[i] = 1;  // 打上“保留”标记，便于滑出窗口时撤销
                cnt[x] += 1;  // 该商品在窗口内的保留数加一
            }
        }
        return ans;  // 返回最少丢弃次数
    }
};
