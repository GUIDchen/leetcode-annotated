// 3457. 吃披萨 / Eat Pizzas!
// 核心思路：排序后让奇数天（第 1、3、5... 天）各占一份最大的披萨作为当天最大值，剩下的偶数天再从后往前隔一个取一份次大值。
// 复杂度：时间复杂度 O(n log n)，空间复杂度 O(log n)（排序所需栈空间）。
class Solution {  // 题解类
public:  // 公有接口
    long long maxWeight(vector<int>& pizzas) {  // 求所有天吃掉的披萨重量之和的最大值
        int n = pizzas.size();  // 披萨总个数
        int days = pizzas.size() / 4;  // 每天吃 4 个，所以天数为总数除以 4
        ranges::sort(pizzas);  // 升序排序，便于从最大的开始分配
        int odd = (days + 1) / 2;  // 奇数编号的天数（第 1、3、5... 天）
        int even = days - odd;  // 偶数编号的天数
        long long ans = accumulate(pizzas.begin() + n - odd, pizzas.end(), 0LL);  // 奇数天直接各取最大的一个，和为末尾 odd 个
        for (int i = n - odd - 2; even; --even) {  // 偶数天从剩余最大的第 2 大开始，每次隔一个取一个
            ans += pizzas[i];  // 累加该天能吃到的最大值
            i -= 2;  // 因为每天要吃掉 4 个，等价于每次向前跳过 2 个
        }  // 结束偶数天分配
        return ans;  // 返回最大总重量
    }  // 结束 maxWeight
};  // 结束题解类
