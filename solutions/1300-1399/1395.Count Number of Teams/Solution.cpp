// 题目：1395. 统计作战单位数（Count Number of Teams）
// 思路：枚举中间的那个人，分别统计左侧更弱/更强、右侧更强/更弱的人数，再用乘法原理累加严格递增与严格递减的三元组个数。
// 时间复杂度：O(n^2)，每个中间点各扫一遍左右两侧；空间复杂度：O(1)，只用到常数个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numTeams(vector<int>& rating) {  // rating：每个人的战力值，题目保证互不相同
        int n = rating.size();  // 总人数
        int ans = 0;  // 合法作战单位（下标三元组）的总数
        for (int i = 0; i < n; ++i) {  // 枚举中间那个人 i
            int l = 0, r = 0;  // l：左侧比 rating[i] 小的人数；r：右侧比 rating[i] 大的人数
            for (int j = 0; j < i; ++j) {  // 扫描 i 左侧的所有人
                if (rating[j] < rating[i]) {  // 左侧这个人比中间的人弱
                    ++l;  // 左侧更弱的人数加一
                }  // if 结束
            }  // 左侧扫描结束
            for (int j = i + 1; j < n; ++j) {  // 扫描 i 右侧的所有人
                if (rating[j] > rating[i]) {  // 右侧这个人比中间的人强
                    ++r;  // 右侧更强的人数加一
                }  // if 结束
            }  // 右侧扫描结束
            ans += l * r;  // 递增三元组：左侧更弱 × 右侧更强
            ans += (i - l) * (n - i - 1 - r);  // 递减三元组：(左侧更强) × (右侧更弱)
        }  // 中间点枚举结束
        return ans;  // 返回合法三元组总数
    }
};