// 题目：1128. 等价多米诺骨牌对的数量（Number of Equivalent Domino Pairs）
// 思路：等价骨牌的判定与顺序无关，因此把每张牌规范化为「小数字在前」的两位编号 a*10+b，用计数数组统计每种编号已出现的次数，每来一张新牌就能与之前所有同编号的牌配对。
// 时间复杂度：O(n)，一次遍历；空间复杂度 O(1)，计数数组大小固定为 100。
class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {  // dominoes：骨牌列表；返回等价骨牌对的数量
        int cnt[100]{};  // cnt：规范化编号的计数，编号范围 11~99，开 100 足够
        int ans = 0;  // ans：已统计到的等价骨牌对数
        for (auto& e : dominoes) {  // 逐张处理骨牌
            int x = e[0] < e[1] ? e[0] * 10 + e[1] : e[1] * 10 + e[0];  // 统一成「小数字在前」的编号，等价骨牌得到同一编号
            ans += cnt[x]++;  // 当前牌可与之前所有同编号的牌配对，故先累加再自增
        }  // 循环结束
        return ans;  // 返回等价骨牌对总数
    }  // 方法结束
};  // 类定义结束