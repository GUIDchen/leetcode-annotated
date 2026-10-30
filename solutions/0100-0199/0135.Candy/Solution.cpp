// 题目：135. 分发糖果（Candy）
// 思路：贪心做两遍。先从左往右保证“比左邻分高就多一颗”，再从右往左保证“比右邻分高就多一颗”，最后每个位置取两个方向的较大值。
// 时间复杂度：O(n)，三次线性扫描；空间复杂度：O(n)，两个辅助数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int candy(vector<int>& ratings) {  // 返回满足相邻约束所需的最少糖果总数
        int n = ratings.size();  // n 是孩子数量
        vector<int> left(n, 1);  // left[i]：只考虑左邻居约束时，第 i 个孩子至少要几颗糖
        vector<int> right(n, 1);  // right[i]：只考虑右邻居约束时，第 i 个孩子至少要几颗糖
        for (int i = 1; i < n; ++i) {  // 从左往右扫描，处理“我比左邻分高”的情况
            if (ratings[i] > ratings[i - 1]) {  // 分数比左邻高，糖果必须比左邻多
                left[i] = left[i - 1] + 1;  // 在左邻基础上多给一颗
            }
        }
        for (int i = n - 2; ~i; --i) {  // 从右往左扫描（~i 即 i >= 0），处理“我比右邻分高”的情况
            if (ratings[i] > ratings[i + 1]) {  // 分数比右邻高，糖果必须比右邻多
                right[i] = right[i + 1] + 1;  // 在右邻基础上多给一颗
            }
        }
        int ans = 0;  // 累计最少糖果总数
        for (int i = 0; i < n; ++i) {  // 逐个孩子结算
            ans += max(left[i], right[i]);  // 两个方向的约束都要满足，所以取较大值
        }
        return ans;  // 返回总糖果数
    }
};