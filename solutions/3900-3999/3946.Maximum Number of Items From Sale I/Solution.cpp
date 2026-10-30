// 题目：3946. 购买最多物品数目 I（Maximum Number of Items From Sale I）
// 思路：先算出买每个商品能白得多少件（factor 是它倍数的都算），做 0-1 背包求花 j 元的最大物品数；剩余预算按最低单价反复购买。
// 复杂度：时间 O(n^2 + n * budget)，空间 O(budget)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumSaleItems(vector<vector<int>>& items, int budget) {  // items[i] = [factor, price]；budget 是总预算
        vector<int> f(budget + 1, 0);  // 0-1 背包：f[j] 表示花掉 j 元预算最多能换到的物品数
        int mn = INT_MAX;  // mn 记录所有商品中的最低单价，供剩余预算使用

        for (const auto& item : items) {  // 逐个商品考虑「买下它」
            int factor = item[0];  // 该商品的 factor 值，决定能一并获得哪些物品
            int price = item[1];  // 该商品的价格

            mn = min(mn, price);  // 更新最低单价

            int cnt = 0;  // cnt 统计买下该商品后一次性可得的物品数（含它自己）
            for (const auto& jItem : items) {  // 遍历全部商品，看谁的 factor 能被当前 factor 整除
                if (jItem[0] % factor == 0) {  // 对方的 factor 是当前 factor 的倍数即可一并获得
                    cnt++;  // 物品数加一
                }
            }

            for (int j = budget; j >= price; --j) {  // 逆序枚举预算，保证该商品最多被选一次
                f[j] = max(f[j], f[j - price] + cnt);  // 不买 vs 买下，取物品数更大的方案
            }
        }

        int ans = 0;  // ans 记录最终答案
        for (int i = 0; i <= budget; ++i) {  // 枚举已经花掉的预算 i
            ans = max(ans, f[i] + (budget - i) / mn);  // 剩余 budget - i 元按最低单价继续买，取最大值
        }

        return ans;  // 返回最多能买到的物品数
    }
};