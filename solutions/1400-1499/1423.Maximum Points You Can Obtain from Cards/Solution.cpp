// 题目：1423. 可获得的最大点数（Maximum Points You Can Obtain from Cards）
// 核心思路：每次只能从两端取，先取最右侧 k 张作为初始方案，再逐次用左端一张替换右端一张，滑出最大点数。
// 时间复杂度：O(k)，初始求和与 k 次替换都是线性；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxScore(vector<int>& cardPoints, int k) {  // cardPoints：牌面点数；k：必须恰好取走的张数
        int n = cardPoints.size();  // 牌的总数
        int s = accumulate(cardPoints.end() - k, cardPoints.end(), 0);  // 先假设全从右端取：末 k 张之和
        int ans = s;  // 用这个方案作为初始最优解
        for (int i = 0; i < k; ++i) {  // 逐步把一张牌从右端换成左端
            s += cardPoints[i] - cardPoints[n - k + i];  // 加上新取到的左端第 i 张，减去被放弃的第 n-k+i 张
            ans = max(ans, s);  // 更新最大点数
        }  // k 次替换结束
        return ans;  // 返回所有取法中的最大点数
    }  // 方法结束
};  // 题解类定义结束