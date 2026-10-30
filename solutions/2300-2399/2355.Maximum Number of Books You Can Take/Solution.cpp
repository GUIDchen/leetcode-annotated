// 题目：2355. 你能拿走的最大图书数量（Maximum Number of Books You Can Take 🔒）
// 思路：把约束 books[j] - j ≤ books[i] - i 变形后，用单调栈求每个 i 左边最近的 nums 更小值位置作边界，边界内按等差数列求和，再用 dp 得到以 i 为最高层的最优解。
// 时间复杂度：O(n)，每个下标进出栈各一次；空间复杂度：O(n)，nums、left、dp 与栈。
using ll = long long;  // 给 long long 起短别名，后面算前缀和时省字

class Solution {  // LeetCode 约定的题解类
public:  // 算法入口对外可见
    long long maximumBooks(vector<int>& books) {  // books 是每层书架的书数，返回最多能拿走的书数（可能超 int）
        int n = books.size();  // 书架层数
        vector<int> nums(n);  // 变形数组：nums[i] = books[i] - i
        for (int i = 0; i < n; ++i) nums[i] = books[i] - i;  // 一次性算出变形数组，比较 nums 的大小等价于比较原约束
        vector<int> left(n, -1);  // left[i] 记录 i 左边最近的「nums 严格更小」的位置，初值 -1 表示没有
        stack<int> stk;  // 单调栈，存下标，对应 nums 值自底向上单调递增
        for (int i = 0; i < n; ++i) {  // 从左到右扫描，为每个位置求左边界
            while (!stk.empty() && nums[stk.top()] >= nums[i]) stk.pop();  // 弹出所有 nums 值 ≥ 当前值的下标，剩下的栈顶就是严格更小值
            if (!stk.empty()) left[i] = stk.top();  // 栈非空时，栈顶即左边最近的更小值下标
            stk.push(i);  // 当前下标入栈，作为后面元素的候选左边界
        }  // 本次求左边界结束
        vector<ll> dp(n);  // dp[i] 表示以第 i 层为最高层（即第 i 层拿 books[i] 本）时的最大取书数
        dp[0] = books[0];  // 只有第 0 层时，最多拿走 books[0] 本
        ll ans = 0;  // 记录全局最大值
        for (int i = 0; i < n; ++i) {  // 逐层递推，计算以 i 结尾的最优解
            int v = books[i];  // 第 i 层（最高层）拿走的书数
            int j = left[i];  // 左边界下标
            int cnt = min(v, i - j);  // 递减序列最多延伸 cnt 层：受本层书数与到左边界距离共同限制
            int u = v - cnt + 1;  // 递减到的最低那一层拿走的书数
            ll s = 1ll * (u + v) * cnt / 2;  // 等差数列求和：从 u 到 v 共 cnt 项
            dp[i] = s + (j == -1 ? 0 : dp[j]);  // 加上左边界以外的前缀最优解；j == -1 表示已延伸到开头，前缀为 0
            ans = max(ans, dp[i]);  // 用当前方案更新全局答案
        }  // 本层递推结束
        return ans;  // 返回最多能拿走的书数
    }  // 方法结束
};  // 类定义结束