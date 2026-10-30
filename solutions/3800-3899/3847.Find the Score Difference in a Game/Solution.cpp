// 3847. 计算比赛分数差 / Find the Score Difference in a Game（中等）
// 核心思路：维护当前得分归属方，遇到奇数得分或每满 6 轮就换发球，按归属累加得分得到分差。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 解题类：LeetCode 判题器约定的类名
public:  // 公有接口
    int scoreDifference(vector<int>& nums) {  // 返回比赛结束时的分数差（A 的得分减 B 的得分）
        int ans = 0;  // ans 累计分数差，A 得分为正、B 得分为负
        int k = 1;  // k 表示当前得分归属：1 为 A，-1 为 B
        for (int i = 0; i < nums.size(); ++i) {  // 依次处理每一轮得分
            int x = nums[i];  // 本轮得分值
            if (x & 1) {  // 本轮得分为奇数时立刻换发球权
                k = -k;  // 得分归属切换
            }  // 奇数判定结束
            if (i % 6 == 5) {  // 每满 6 轮（索引 5、11、…）也换发球权
                k = -k;  // 得分归属切换
            }  // 换发球判定结束
            ans += k * x;  // 把本轮得分按归属累加
        }  // 遍历结束
        return ans;  // 返回最终分数差
    }  // scoreDifference 方法结束
};  // 解题类定义结束
