// 题目：1176. 健身计划评估（Diet Plan Performance）
// 思路：先用前缀和预处理热量，再用长度固定为 k 的滑动窗口 O(1) 求每段总和，按阈值累加得分。
// 时间复杂度：O(n)，一次前缀和 + 一次滑窗；空间复杂度：O(n)，前缀和数组 s 占 n+1 个位置。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int dietPlanPerformance(vector<int>& calories, int k, int lower, int upper) {  // calories：每日摄入热量；k：连续 k 天；lower/upper：评分阈值
        int n = calories.size();  // 天数 n，供前缀和与滑窗共同使用
        int s[n + 1];  // 前缀和数组，长度 n+1 便于让 s[i] 表示前 i 天之和
        s[0] = 0;  // 前 0 天总和为 0，作为前缀和的起点
        for (int i = 0; i < n; ++i) {  // 从第 1 天推到第 n 天，线性构造前缀和
            s[i + 1] = s[i] + calories[i];  // s[i+1] = 前 i 天和 + 第 i 天热量（calories 下标从 0 开始）
        }  // 前缀和构造完毕
        int ans = 0;  // ans 记录总得分，题目允许扣成负数，所以用 int
        for (int i = 0; i < n - k + 1; ++i) {  // 枚举所有长度恰好为 k 的窗口，起点 i 最大取 n-k
            int t = s[i + k] - s[i];  // 窗口和 = s[i+k] - s[i]，用前缀和相减避免内层再累加
            if (t < lower) {  // 该窗口热量低于下界：每出现一次扣 1 分
                --ans;  // 扣分
            } else if (t > upper) {  // 该窗口热量高于上界：每出现一次加 1 分
                ++ans;  // 加分
            }  // 落在 [lower, upper] 区间内则不加不减
        }  // 所有窗口评估完毕
        return ans;  // 返回累计得分
    }  // 方法体结束
};  // 题解类结束