// 题目：2280. 表示一个折线图的最少线段数（Minimum Lines to Represent a Line Chart）
// 思路：先按日期排序，再用叉积比较相邻两段的斜率是否相同，斜率变化就需要新的一条线段，整数运算避免浮点误差。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(1)，不计排序自身开销。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int minimumLines(vector<vector<int>>& stockPrices) {  // stockPrices[i] = [第 i 天, 当天股价]
        sort(stockPrices.begin(), stockPrices.end());  // 按日期（第一维）升序排序，保证相邻两点在时间上连续
        int dx = 0, dy = 1;  // 上一段的横纵增量；初值 (0, 1) 让第一段必然被计入线段数
        int ans = 0;  // 需要的线段总数
        for (int i = 1; i < stockPrices.size(); ++i) {  // 从第二个点开始，枚举每一段（i-1 → i）
            int x = stockPrices[i - 1][0], y = stockPrices[i - 1][1];  // 前一个点的日期与股价
            int x1 = stockPrices[i][0], y1 = stockPrices[i][1];  // 当前点的日期与股价
            int dx1 = x1 - x, dy1 = y1 - y;  // 当前段的横纵增量
            if ((long long) dy * dx1 != (long long) dx * dy1) ++ans;  // 叉积不相等说明斜率改变，需要新的一条线段；转 long long 防止乘法溢出
            dx = dx1;  // 更新「上一段」的横增量，供下一轮比较
            dy = dy1;  // 更新「上一段」的纵增量，供下一轮比较
        }
        return ans;  // 返回最少线段数
    }
};