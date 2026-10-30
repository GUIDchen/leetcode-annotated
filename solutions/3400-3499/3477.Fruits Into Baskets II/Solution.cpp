// 3477. 水果成篮 II（Fruits Into Baskets II）
// 核心思路：按顺序枚举每个水果，在从前往后第一个容量足够且未被占用的篮子里放下它，统计放不下的水果数。
// 复杂度：时间 O(n^2)，空间 O(n)
class Solution {  // 解题类
public:  // 公有成员
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {  // 返回无法放入任何篮子的水果数量
        int n = fruits.size();  // 水果数量（同时也是篮子数量）
        vector<bool> vis(n);  // 标记每个篮子是否已经被占用
        int ans = n;  // 先假设所有水果都放不下，答案初始化为 n
        for (int x : fruits) {  // 按给定顺序逐个处理水果
            for (int i = 0; i < n; ++i) {  // 从左到右扫描篮子，找第一个可用的
                if (baskets[i] >= x && !vis[i]) {  // 容量足够且该篮子尚未被占用
                    vis[i] = true;  // 占用这个篮子
                    --ans;  // 该水果成功放置，放不下的数量减一
                    break;  // 每个水果只能用一个篮子，立即跳出内层循环
                }  // 结束放置判定
            }  // 结束篮子扫描
        }  // 结束水果遍历
        return ans;  // 返回最终放不下的水果数
    }  // 结束方法
};  // 结束类定义