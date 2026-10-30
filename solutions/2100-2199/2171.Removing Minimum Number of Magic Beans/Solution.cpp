// 题目：2171. 拿出最少数目的魔法豆（Removing Minimum Number of Magic Beans）
// 思路：排序后枚举「最终统一留成的豆子数」为 beans[i]，比它小的袋子被整体拿走、比它大的袋子被削到它，取所有方案中的最小值。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(1)，只用了常数个额外变量（排序为原地）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumRemoval(vector<int>& beans) {  // beans：每袋豆子的数量；返回拿出的最少豆子数
        sort(beans.begin(), beans.end());  // 升序排序，使 beans[i] 成为非递减的候选「统一值」，方便按下标批量计算代价
        long long s = accumulate(beans.begin(), beans.end(), 0ll);  // 先求总和；初值 0ll 让累加类型为 long long，避免溢出
        long long ans = s;  // 答案初值取「把所有豆子都拿走」，这是一个一定可行的方案
        int n = beans.size();  // 袋子个数
        for (int i = 0; i < n; ++i) {  // 枚举下标 i：把最终统一保留的数量定为 beans[i]（取到 i = n-1 时相当于只留 n 袋里最少的那批）
            ans = min(ans, s - 1ll * beans[i] * (n - i));  // 统一留成 beans[i] 时：前 i 袋不足该值只能整体拿走，后 n-i 袋各被削到该值；被拿走的豆子合计恰好是 s - beans[i]*(n-i)，用 1ll 防止乘法溢出
        }  // 循环结束
        return ans;  // 返回最小代价
    }  // 方法结束
};  // 类定义结束，源文件到此为止