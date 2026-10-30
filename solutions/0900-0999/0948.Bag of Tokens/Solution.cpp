// 题目：948. 令牌放置（Bag of Tokens）
// 思路：先排序；能量够就用最小面值的令牌正面朝上换分数，能量不够但有分数就反面朝上卖出最大面值的令牌换能量，直到两端相遇。
// 时间复杂度：O(n log n)，瓶颈在排序，之后双指针一趟 O(n)；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int bagOfTokensScore(vector<int>& tokens, int power) {  // tokens：每个令牌的面值；power：初始能量
        sort(tokens.begin(), tokens.end());  // 升序排序，让最小面值在左端、最大面值在右端
        int ans = 0, score = 0;  // ans 记录历史最高分，score 是当前分数
        for (int i = 0, j = tokens.size() - 1; i <= j;) {  // i 从左往右吃掉小令牌，j 从右往左卖掉大令牌，区间为空即结束
            if (power >= tokens[i]) {  // 能量足够，优先买下最便宜的令牌换 1 分
                power -= tokens[i++];  // 花掉该令牌的面值，同时左指针右移（i++ 是后缀自增）
                ans = max(ans, ++score);  // 分数先加一，再刷新历史最高分
            } else if (score > 0) {  // 能量不够买，但手里有分数，就卖最贵的令牌换能量
                power += tokens[j--];  // 拿到最大面值的令牌（j-- 是后缀自减）
                --score;  // 卖出一个令牌要付出 1 分
            } else {  // 既买不起也没分可卖，无法继续操作
                break;  // 只能提前结束循环
            }
        }  // 返回能拿到的最高分数
        return ans;
    }
};